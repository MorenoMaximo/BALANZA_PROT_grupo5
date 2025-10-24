/*
 * Nombre del archivo:   main.c
 * Autores: MAXIMO MORENO
 *          VALENTINO FALCINELLI
 *          MAURICIO SOLIS
 *          JOAQUIN RUIZ ARANDA
 *          LEANDRO ROJAS
 *
 * Descripción:
 *       El codigo principal de la balanza:
 *       cada instante de tiempo se registra una fuerza
 *       en una celda de carga, y se convierte en una tension
 *       gracias a un conversor AC/DC, luego se promedia con valores
 *       muestreados cada cierto tiempo y se muestra en una pantalla
 */
/*==================[inlcusiones]============================================*/
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "user.h"
#include "uart.h"
#include "system.h"
#include "hx711.h"
#include "tick.h"
#include "encoder.h"


/*==================[definiciones de datos internos]=========================*/
extern void ejemplo(void);

/*==================[declaraciones de funciones internas]====================*/

//Codigo principal
void main(void) {
    appInit();                  //Inicializo las entradas y salidas
    ActualizarENCODER();        //Inicializamos los MEF encoder
    ActualizarTEC_ENCODER();
    
    uint8_t numMuestra = 1;
    unsigned long peso;
    uint16_t tiempoDeMuestra = 0;
    tick_t tMEDICION;
    
    PIN_BUZZER = 0;
    PIN_LED = 0;
    
    for(uint8_t cont = 0; cont < 100; cont++) {
        PIN_LED = 1;
        __delay_ms(500);
        PIN_LED = 0;
    }
    //ejemplo();
    while(1) {
        
        //Comprobamos constantemente los estados del ENCODER 
        ActualizarENCODER();
        ActualizarTEC_ENCODER();
        
        if(botonEncoder) {
//            tMEDICION = tickRead();
//            peso = HX711Read();
//            tiempoDeMuestra = (tickRead() - tMEDICION);
//            printf("Tiempo que tardo: %d\n", tiempoDeMuestra);
//            printf("Peso: %lu\nMuestra: %d", peso, numMuestra);
            PIN_BUZZER = 1;
            __delay_us(50);
            PIN_BUZZER = 0;
        }
        else {
            PIN_BUZZER = 0;
        }
        
    }
}   //Fin del main()

/*==================[definiciones de funciones internas]=====================*/



/******************************************************************************/