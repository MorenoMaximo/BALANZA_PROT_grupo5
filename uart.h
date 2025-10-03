/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de la Uart
 * 
 * Aquí se definen macros, tipos de datos y se declaran las funciones y datos 
 * externos de uart
 */
#ifndef UART_H
#define UART_H
/*==================[inclusiones]============================================*/
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

/*==================[macros]=================================================*/
//Pines de la UART
#define	TRIS_PICTX      TRISCbits.TRISC6
#define	PIN_PICTX       PORTCbits.RC6
#define	TRIS_PICRX      TRISCbits.TRISC7
#define	PIN_PICRX       PORTCbits.RC7
//Definición del Baudrate
#define	UART_BAUDRATE        9600

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/
void uartInit(void);    /* Inicializa la UART */
void putch(char data);  /* Pone un byte en stdout */
char getch(void);       /* Toma un byte en stdin  */
char getche(void);      /* Toma un byte en stdin con eco */
void uartWriteByte( uint8_t value );      /* Envia un byte en forma boqueante */
__bit uartReadByte( uint8_t* receivedByte );/* Toma un byte de la UART */
/*==================[fin del archivo]========================================*/
#endif// UART_H
