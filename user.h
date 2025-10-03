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
    
//Encoder
#define PIN_SCK         PORTAbits.RA4
#define TRIS_SCK        TRISAbits.TRISA4

#define PIN_DT          PORTAbits.RA3
#define TRIS_DT         TRISAbits.TRISA3

//Leds
#define TRIS_LED1       TRISEbits.TRISE2
#define PIN_LED1        PORTEbits.RE2

#define TRIS_LED2       TRISEbits.TRISE1
#define PIN_LED2        PORTEbits.RE1

#define TRIS_LED3       TRISEbits.TRISE0
#define PIN_LED3        PORTEbits.RE0

#define TRIS_TEC1       TRISBbits.TRISB0
#define PIN_TEC1        PORTBbits.RB0

#define TRIS_TEC2       TRISBbits.TRISB1
#define PIN_TEC2        PORTBbits.RB1

#define TRIS_TEC3       TRISBbits.TRISB2
#define PIN_TEC3        PORTBbits.RB2

#define TRIS_TEC4       TRISBbits.TRISB3
#define PIN_TEC4        PORTBbits.RB3

//Alias de los Leds
#define	TRIS_LED_R      TRIS_LED1 
#define	PIN_LED_R       PIN_LED1

#define	TRIS_LED_AM     TRIS_LED2
#define	PIN_LED_AM      PIN_LED2

#define	TRIS_LED_V      TRIS_LED3
#define PIN_LED_V       PIN_LED3

//Buzzer
#define TRIS_BUZZER     TRISCbits.TRISC0
#define PIN_BUZZER      PORTCbits.RC0

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/
//extern char datoUser; //Ejemplo

/*==================[declaraciones de funciones externas]====================*/
/* TODO: Los prototipos de User level (ej. InitApp) van aquí */
void appInit(void);                                 /* Inicializa las I/O y los periféricos */

/*==================[fin del archivo]========================================*/
#endif// USER_H
