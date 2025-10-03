/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de user
 * 
 * Aquí se definen macros, tipos de datos y se declaran las funciones y datos 
 * externos de user
 */
#ifndef USER_H
#define USER_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
/* User Level #define Macros                                                 */
/* TODO: Los parámetros de user.c pueden ponerse aquí */
    
//HX711
#define PIN_SCK         PORTAbits.RA0
#define TRIS_SCK        TRISAbits.TRISA0

#define PIN_DT          PORTAbits.RA1
#define TRIS_DT         TRISAbits.TRISA1

//Leds
#define TRIS_LED       TRISCbits.TRISC2
#define PIN_LED        PORTCbits.RC2

//Buzzer
#define TRIS_BUZZER     TRISCbits.TRISC0
#define PIN_BUZZER      PORTCbits.RC0

//Encoder
#define TRIS_ENCA   TRISAbits.TRISA2
#define PIN_ENCA	PORTAbits.RA2

#define TRIS_ENCB	TRISAbits.TRISA3
#define PIN_ENCB	PORTAbits.RA3

#define TRIS_ENC_SW	TRISBbits.TRISB5
#define PIN_ENC_SW	PORTBbits.RB5
/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo

/*==================[declaraciones de funciones externas]====================*/
/* TODO: Los prototipos de User level (ej. InitApp) van aquí */
void appInit(void);                                 /* Inicializa las I/O y los periféricos */

/*==================[fin del archivo]========================================*/
#endif// USER_H
