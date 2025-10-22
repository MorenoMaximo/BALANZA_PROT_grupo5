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
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

#include "system.h"     /* Funciones/Parametros System, como conf de osc/perif */
#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "encoder.h"
#include "tick.h"    /* Funciones/Parametros del Teclado */

/*==================[definiciones y macros]==================================*/
// Nuevo tipo de datos enumerado llamado estadoENC_t
typedef enum{
        A1B1, 
        A1B0, 
        A0B0, 
        A0B1
} estadoENC_t;

// Nuevo tipo de datos enumerado llamado estadoTEC_ENC_t
typedef enum{
        SUELTO, 
        BAJANDO, 
        PRESIONADO, 
        SUBIENDO, 
        MANTENIDO
} estadoTEC_ENC_t;

/*==================[definiciones de datos internos]=========================*/


/*==================[definiciones de funciones internas]=====================*/
void ActualizarTEC_ENCODER(void) {
    static estadoTEC_ENC_t estadoActualTEC_ENC = SUELTO;    // Declara variable de estados static para que mantenga su valor y establece estado inicial
    tick_t tTEC_ENC;
    
    switch(estadoActualTEC_ENC) {
        case SUELTO:
            if(PIN_TEC_ENC == 0) {          // Chequear condiciones de transición de estado
                estadoActualTEC_ENC = BAJANDO;  // Cambiar a otro estado
                tTEC_ENC = tickRead();      // También inicia temporizacion
            } 
            break;
        case BAJANDO:
            if(PIN_TEC_ENC == 1) {
                estadoActualTEC_ENC = SUELTO;
            }
            else if((tickRead() - tTEC_ENC) > 40) {
                estadoActualTEC_ENC = PRESIONADO;
            }
            break;
        case PRESIONADO:
            if(PIN_TEC_ENC == 1) {
                estadoActualTEC_ENC = SUBIENDO;
                tTEC_ENC = tickRead();
            }
            break;
        case SUBIENDO:
            if(PIN_TEC_ENC == 0) {
                estadoActualTEC_ENC = PRESIONADO;
            }
            else if((tickRead() - tTEC_ENC) > 40) {
                estadoActualTEC_ENC = SUELTO;
                empezarMedicion = 1;
            }
            break;
        default:
            //Si algo modificó la variable estadoActualTEC_ENC 
            // a un estado no válido llevo la MEF a un 
            // lugar seguro, por ejemplo, la reinicio:
            estadoActualTEC_ENC = SUELTO;
    }
}

void ActualizarENCODER(void) {
    static estadoENC_t  estadoActualENCODER = A1B1;     // Declara variable de estados static para que mantenga su valor y establece estado inicial
    
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
            estadoActualENCODER = A1B1;
    }
}
/*==================[fin del archivo]========================================*/