/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones del conversor A/D
 * 
 * Aquí se configura el conversor A/D HX711 para que tome una muestra
 * cada cierto tiempo y la promedie para luego mostrarla en la pantalla
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>
#include <stdio.h>     /* para las definiciones de uint8_t por ej.*/
#include "system.h"
#include "user.h"
#include "hx711.h"
#include "uart.h"

/*==================[definiciones de datos externos]=========================*/
float CALIB_SCALE = 7.06f; // 1000 raw = 1 gram (ajustar después)
/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Toma muestras de la celda de carga
 * @return	Un numero binario
 * @note    Las opciones se modifican en el código, por ejemplo con las 
 * constantes   
 */

static unsigned long TARA;

unsigned long HX711Read() {
    unsigned long data = 0;
    unsigned char i;

    PIN_SCK = 0;
    __delay_ms(START_UP_DELAY);
    //Este bucle espera hasta que le lleguen datos a PIN_DT
    while(PIN_DT);

    //Escribimos el numero en 24 ciclos del CLOCK
    //El clock lo generamos nosotros
    for( i = 0; i < 24; i++) {
        PIN_SCK = 1;
        __delay_us(1);
        data = data << 1;
        PIN_SCK = 0;
        __delay_us(1);
        if(PIN_DT) data++;
    }

    //Hacemos un XOR y devolvemos el dato
    PIN_SCK = 1;
    __delay_us(1);
    data = data ^ CHECKSUM_MASK;
    PIN_SCK = 0;
    data = data >> 7;
    return(data);
}

//Ajuste de la Tara
unsigned long TaraSet() {
    TARA = 0;
    TARA = HX711Promedio();
    //TARA >>= 10;
    return (TARA);
}

//Lectura con promedio
unsigned long HX711Promedio(void) {
    unsigned long prom = 0;
    unsigned char i;
    
    for(i = 0; i < CANT_PROMEDIO; i++) {
        prom += HX711Read();
    }
    prom /= CANT_PROMEDIO;
    return (prom);
    
//    if(prom > TARA) {
//        return prom - TARA;
//    }
//    else {
//        return 0;   //Evita valores negativos (según necesidad)
//    }
}

//Tomar una muestra del HX711
unsigned long LecturaPeso(void) {
    unsigned long muestra;
    
    muestra = HX711Read();
    if(muestra < TARA) {
        return (TARA - muestra);
    }
    else {    
        return (muestra - TARA);
    }
}

float PesoEnGramos(void) {
    unsigned long raw = LecturaPeso(); // Devuelve valor con TARA restada
    
    // Evitar división por 0
    if (CALIB_SCALE == 0.0f) return 0.0f;
    return ((float) raw) / CALIB_SCALE;
}

//void Calibrar(void) {
//    printf("Espere 1 minuto\n");
//    for(uint8_t cont = 0; cont < 60; cont++) {
//        __delay_ms(1000);
//    }
//    unsigned long tare = HX711Promedio();
//    printf("Coloque el peso conocido\n");
//    __delay_ms(2000);
//    unsigned long with = HX711Promedio(); // indica poner peso conocido
//    unsigned long delta = (with > tare) ? (with - tare) : (tare - with);
//    float known_mass_g = 500.0f; // por ejemplo
//    float scale = (float)delta / known_mass_g;  // raw per gram
//    CALIB_SCALE = scale;
//    unsigned long ent = (unsigned long) CALIB_SCALE;
//    unsigned int dec = (unsigned int)((CALIB_SCALE - ent) * 100);
//    printf("CALIB_SCALE = %lu.%02u raw/g\n", ent, dec);
//}
/*==================[fin del archivo]========================================*/