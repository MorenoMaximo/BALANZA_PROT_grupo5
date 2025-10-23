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
    
    while(1) {
        
        //Comprobamos constantemente los estados del ENCODER 
        ActualizarENCODER();
        ActualizarTEC_ENCODER();
        
        if(botonEncoder) {
            tMEDICION = tickRead();
            peso = HX711Read();
            tiempoDeMuestra = (tickRead() - tMEDICION);
            printf("Tiempo que tardo: %d\n", tiempoDeMuestra);
            printf("Peso: %lu\nMuestra: %d", peso, numMuestra);
            botonEncoder = 0;
        }
    }
}   //Fin del main()

/*==================[definiciones de funciones internas]=====================*/



/******************************************************************************/