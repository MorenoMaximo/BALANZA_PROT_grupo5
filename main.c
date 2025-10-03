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

/*==================[definiciones y macros]==================================*/
// Nuevo tipo de datos enumerado llamado estadoMEF_t
typedef enum{A1B1, A1B0, A0B0, A0B1} estadoMEF_t;

/*==================[definiciones de datos internos]=========================*/
estadoMEF_t  estadoActualENCODER; // Variable de estado (global)

/*==================[declaraciones de funciones internas]====================*/
void InicializarENCODER(void);
void ActualizarENCODER(void);

//Codigo principal
void main(void) {
    appInit();                  //Inicializo las entradas y salidas
    InicializarENCODER();
//    uint8_t numMuestra = 0;
//    unsigned long peso;
//    PIN_LED_R = 0;
//    PIN_LED_AM = 0;
//    PIN_LED_V = 0;
    
    while(1) {
        ActualizarENCODER();
        
//        if(PIN_TEC1 == 0) {         //Setear el peso en 0
//            PIN_LED_R = 1;
//            __delay_ms(20);         //delay de seguridad por el boton
//            
//            peso = TaraSet();
//            __delay_ms(1);
//            PIN_LED_R = 0;
//            
//            while(PIN_TEC1 == 0);
//            __delay_ms(20);         //delay de seguridad por el boton            
//        }
//        
//        if(PIN_TEC2 == 0) {         //Una sola muestra
//            __delay_ms(20);         //delay de seguridad por el boton
//            PIN_LED_AM = 1;
//            
//            peso = LecturaPeso();
//            printf("%lu\n", peso);
//            
//            __delay_ms(1);
//            PIN_LED_AM = 0;
//            
//            while(PIN_TEC2 == 0);
//            __delay_ms(20);         //delay de seguridad por el boton            
//        }
//        
//        if(PIN_TEC3 == 0) {
//            __delay_ms(20);         //delay de seguridad por el boton
//            PIN_LED_V = 1;
//            
//            while(peso != 0 && numMuestra < 100) {
//                peso = LecturaPeso();
//                printf("%lu , %d\n", peso, numMuestra++);
//                __delay_ms(100);
//            }
//            PIN_LED_V = 0;
//            numMuestra = 0;
//            __delay_ms(20);         //delay de seguridad por el boton            
//        }
//        
//        if(PIN_TEC4 == 0) {
//            printf("stop\n");
//        }
    }
}   //Fin del main()

/*==================[definiciones de funciones internas]=====================*/
// Función Inicializa MEF
void InicializarENCODER(void) {
    estadoActualENCODER = A1B1;
}

void ActualizarENCODER(void) {
    switch(estadoActualENCODER) {
        case A1B1:
            if(PIN_ENCA == 0) {
                estadoActualENCODER = A0B1;
            }
            else if(PIN_ENCB == 0) {
                estadoActualENCODER = A1B0;
            }
            break;
        case A1B0:
            if(PIN_ENCA == 0) {
                estadoActualENCODER = A0B0;
            }
            else if(PIN_ENCB == 1) {
                estadoActualENCODER = A1B1;
            }
            break;
        case A0B0:
            if(PIN_ENCA == 1) {
                estadoActualENCODER = A1B0;
            }
            else if(PIN_ENCB == 1) {
                estadoActualENCODER = A0B1;
            }
            break;
        case A0B1:
            if(PIN_ENCA == 1) {
                estadoActualENCODER = A1B1;
            }
            else if(PIN_ENCB == 0) {
                estadoActualENCODER = A0B0;
            }
            break;
        default:
            //Si algo modificó la variable estadoActual 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarENCODER();
    }
}
/******************************************************************************/