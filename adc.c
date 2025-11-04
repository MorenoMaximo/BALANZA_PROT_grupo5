/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene las definiciones de ADC
 * 
 * Aquí se encuentra la implementación de ADC, los defines, macros, 
 * datos internos y externos, declaraciones y definiciones de funciones
 * internas y definiciones de funciones externas.
 */

/*==================[inlcusiones]============================================*/
#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/
#include "system.h"
#include "adc.h"        /* Funciones/Parametros ADC */

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/
/**
 * @brief	Inicializa el ADC
 * @return	Nada
 */
void adcInit(void) {
    FVREN   = 1;      //Referencia de tensión fija habilitada
    ADFM    = 1;      //Resultado ajustado a derecha
    
    VCFG1   = 0;      //Vref- = VSS
    VCFG0   = 0;      //Vref+ = VDD
    
    ADCS1   = 1;      //Clock del AD seleccionado
    ADCS0   = 1;      //en clock interno RC
    
    ADON    = 1;      //Enable AD
}

/**
 * @brief	Realiza una conversión AD
 * @param[in]   analogInput Selecciona la entrada analógica deseada
 * @return  resultado de la conversión
 */
uint16_t adcRead(adcMap_t analogInput){
    ADCON0bits.CHS = analogInput;
    __delay_us(50);
    
    //Iniciamos la coversion
    GO = 1;
    while(GO == 1) {};
    
    return ((uint16_t)ADRESH << 8 | ADRESL);
}
/**
 * @brief	Realiza una conversión AD en mV
 * @param[in]   analogInput Selecciona la entrada analógica deseada
 * @note    Si recibe como parámetro 255 ( o la etiqueta `VDD_CALC` ) determina la tensión de alimentación VDD o tensión de referencia actual 
 * @return  resultado de la conversión en mV
 * @note    Antes de poder medir cualquier canal se debe medir por lo menos una vez la tensión de alimentación o referencia
 */
uint16_t adcRead_mV(adcMap_t analogInput){
    static uint16_t nAdcRef = 0;
    
    if(analogInput == VDD_CALC) {
        nAdcRef = adcRead(AIN_FIXREF);
        return ((1023UL*600U) / nAdcRef);
    }
    else {
        return ((600UL*adcRead(analogInput)) / nAdcRef);
    }
}
/*==================[fin del archivo]========================================*/
