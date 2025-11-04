/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de user
 * 
 * Aquí se encuentra la implementación de users, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas.
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/

#include "user.h"       /* Funciones/Parametros User, como InitApp */
#include "hx711.h"
#include "uart.h"       /* Funciones/Parametros User, como InitApp */
#include "system.h"       /* Funciones/Parametros User, como InitApp */
#include "tick.h"       /* Funciones/Parametros Tick */
#include "adc.h"        /* Funciones/Parametros ADC */
#include "encoder.h"
#include "TFT_ILI9486_LL.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
//char datoUser; //Ejemplo

/*==================[declaraciones de funciones internas]====================*/
//static void funcUser(void); //Ejemplo

/*==================[definiciones de funciones internas]=====================*/
//static void funcUser(void){ //Ejemplo
//}; 

/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Inicializa Ports, Periféricos e Interrupciones
 * @return	Nada
 */
void appInit(void) {
    /* TODO: Inicializar Ports/Periféricos/Interrupciones */

    /* Configura funciones analógicas y dirección de los Ports de I/O */
    ANSEL  = 0;
    ANSELH = 0;
    ANS1 = 1;
    
    //Pines Genericos
    TRIS_LED    = 0;   
    TRIS_BUZZER = 0;

    //Configuracion del HX711
    TRIS_DT     = 1;
    TRIS_SCK    = 0;
    
    //Configuracion del Encoder
    TRIS_ENCA   = 1;
    TRIS_ENCB   = 1;
    TRIS_TEC_ENC = 1;
    
    //Configuraciones externas
    uartInit();         //Configuraci�n de la UART
    tickInit();         //Configuraci�n de TICK
    adcInit();
    ILI9486_Init();     //Configuraci�n del driver de la PANTALLA
    
    __delay_ms(100);    //Espera que se estabilice la fuente
    
    /* TODO: Habilita Interrupciones si es necesario*/
    TMR0IE = 1;     //Habilita interrupcion para tick
    //PEIE = 1;       
    GIE = 1;        //General Interrupt Enable

}

/*==================[fin del archivo]========================================*/