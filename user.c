/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de user
 * 
 * AquÃ­ se encuentra la implementaciÃ³n de users, los defines, macros, 
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
 * @brief	Inicializa Ports, PerifÃ©ricos e Interrupciones
 * @return	Nada
 */
void appInit(void) {
    /* TODO: Inicializar Ports/PerifÃ©ricos/Interrupciones */

    /* Configura funciones analógicas y dirección de los Ports de I/O */
    //Configura las entradas y salidas como digitales
    ANSEL  = 0;
    ANSELH = 0;
    
    // Activo SOLO AN4 (RA5) como analógico para el ADC
    ANS4 = 1;
    
    // Apagar comparadores (muy importante)
    C1ON = 0; 
    C2ON = 0;


    //Pines Genericos
    TRIS_LED    = 0;   
    TRIS_BUZZER = 0;

    //Configuracion del HX711
    TRIS_DT     = 1;
    TRIS_SCK    = 0;
    PIN_SCK = 0;
    
    //Configuracion del Encoder
    TRIS_ENCA   = 1;
    TRIS_ENCB   = 1;
    TRIS_TEC_ENC = 1;
    
    //Configuraciones externas
    uartInit();         //Configuración de la UART
    tickInit();         //Configuración de TICK
    adcInit();
    ILI9486_Init();     //Configuración del driver de la PANTALLA
    
    __delay_ms(100);    //Espera que se estabilice la fuente
    
    /* TODO: Habilita Interrupciones si es necesario*/
    TMR0IE = 1;     //Habilita interrupcion para tick
    //PEIE = 1;       
    GIE = 1;        //General Interrupt Enable

}

/*==================[fin del archivo]========================================*/