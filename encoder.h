/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones del encoder
 *  
 * Aqui se definen macros, tipos de datos y declaraci?n de funciones y datos 
 * externos de user
 */
#ifndef ENCODER_H
#define ENCODER_H

/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
//PIN A
#define TRIS_ENCA   TRISAbits.TRISA2
#define PIN_ENCA	PORTAbits.RA2

//PIN B
#define TRIS_ENCB	TRISAbits.TRISA3
#define PIN_ENCB	PORTAbits.RA3

//BOTON ó TECLA
#define TRIS_TEC_ENC TRISBbits.TRISB5
#define PIN_TEC_ENC	 PORTBbits.RB5

/*==================[declaraciones de funciones externas]====================*/
//MEF de rotacion del ENCODER
void InicializarENCODER(void);
void ActualizarENCODER(void);

/*==================[fin del archivo]========================================*/
#endif// ENCODER_H