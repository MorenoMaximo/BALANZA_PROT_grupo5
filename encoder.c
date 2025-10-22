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
estadoENC_t  estadoActualENCODER;       // Variable de estado (global)
estadoTEC_ENC_t estadoActualTEC_ENC;    // Variable de estado (global)
tick_t tTEC_ENC;
tick_t tMEDICION;

/*==================[declaraciones de funciones internas]====================*/
/**
 * @brief	Actualiza MEF para antirrebotes de la tecla del ENCODER 
 * @return	Nada
 * @note    Se debe debe llamar periodicamente al finalizar un giro
 */

void InicializarTEC_ENCODER(void);
void ActualizarTEC_ENCODER(void);

/*==================[fin del archivo]========================================*/