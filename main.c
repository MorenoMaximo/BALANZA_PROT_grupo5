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
typedef enum{A1B1, A1B0, A0B0, A0B1} estadoENC_t;
typedef enum{SUELTO, BAJANDO, PRESIONADO, SUBIENDO, MANTENIDO} estadoTEC_ENC_t;

/*==================[definiciones de datos internos]=========================*/
estadoENC_t  estadoActualENCODER;       // Variable de estado (global)
estadoTEC_ENC_t estadoActualTEC_ENC;    // Variable de estado (global)
tick_t tTEC_ENC;
tick_t tMEDICION;

/*==================[declaraciones de funciones internas]====================*/
//MEF de rotacion del ENCODER
void InicializarENCODER(void);
void ActualizarENCODER(void);

//MEF de Tecla del ENCODER
void InicializarTEC_ENCODER(void);
void ActualizarTEC_ENCODER(void);

//Codigo principal
void main(void) {
    appInit();                  //Inicializo las entradas y salidas
    InicializarENCODER();
    InicializarTEC_ENCODER();
//    uint8_t numMuestra = 0;
//    unsigned long peso;
    
    while(1) {
        ActualizarENCODER();
        InicializarTEC_ENCODER();
        
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
            if(PIN_ENCA == 0) {             // Chequear condiciones de transición de estado
                estadoActualENCODER = A0B1; // Cambiar a otro estado
            }
            else if(PIN_ENCB == 0) {        // Chequear condiciones de transición de estado
                estadoActualENCODER = A1B0; // Cambiar a otro estado
            }
            break;
        case A1B0:
            if(PIN_ENCA == 0) {             // Chequear condiciones de transición de estado
                estadoActualENCODER = A0B0; // Cambiar a otro estado
            }
            else if(PIN_ENCB == 1) {        // Chequear condiciones de transición de estado
                estadoActualENCODER = A1B1; // Cambiar a otro estado
            }
            break;
        case A0B0:
            if(PIN_ENCA == 1) {             // Chequear condiciones de transición de estado
                estadoActualENCODER = A1B0; // Cambiar a otro estado
            }
            else if(PIN_ENCB == 1) {        // Chequear condiciones de transición de estado
                estadoActualENCODER = A0B1; // Cambiar a otro estado
            }
            break;
        case A0B1:
            if(PIN_ENCA == 1) {             // Chequear condiciones de transición de estado
                estadoActualENCODER = A1B1; // Cambiar a otro estado
            }
            else if(PIN_ENCB == 0) {        // Chequear condiciones de transición de estado
                estadoActualENCODER = A0B0; // Cambiar a otro estado
            }
            break;
        default:
            //Si algo modificó la variable estadoActual 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            InicializarENCODER();
    }
}

void InicializarTEC_ENCODER(void) {
    estadoTEC_ENC_t = SUELTO;
    tTEC_ENC = tickRead();
}
void ActualizarTEC_ENCODER(void) {
    switch (estadoTEC_ENC_t) {
        case SUELTO:
            if(PIN_TEC_ENC == 0) {          // Chequear condiciones de transición de estado
                estadoTEC_ENC_t = BAJANDO;  // Cambiar a otro estado
                tTEC_ENC = tickRead();      // También inicia temporizacion
            } 
            break;
        case BAJANDO:
            if(PIN_TEC_ENC == 1) {
                estadoTEC_ENC_t = SUELTO;
            }
            else if((tickRead() - tTEC_ENC) > 40) {
                estadoTEC_ENC_t = PRESIONADO;
            }
            break;
        case PRESIONADO:
            if(PIN_TEC_ENC == 1) {
                estadoTEC_ENC_t = SUBIENDO;
                tTEC_ENC = tickRead();
            }
            break;
        case SUBIENDO:
            if(PIN_TEC_ENC == 0) {
                estadoTEC_ENC_t = PRESIONADO;
            }
            else if((tickRead() - tTEC_ENC) > 40) {
                estadoTEC_ENC_t = SUELTO;
            }
            break;
            break;
    }
}
/******************************************************************************/