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
#include "tick.h"
#include "encoder.h"
#include "adc.h"
#include "TFT_ILI9486_LL.h"
#include "GLCD_Draw.h"
#include "GLCD_Text.h"

/*==================[definiciones de datos internos]=========================*/
extern void ejemplo(void);
unsigned char numAdvertencia = 0;

/*==================[definiciones de datos externos]=========================*/
/*==================[declaraciones de funciones internas]====================*/

//Codigo principal
void main(void) {
    uint8_t numMuestra = 1;
    unsigned long peso;
    uint16_t tiempoDeMuestra = 0, nivBateria;
    tick_t tMEDICION, tLED;
    appInit();                  //Inicializo las entradas y salidas
    PIN_BUZZER = 0;
    PIN_LED = 0;
    
    adcRead_mV(VDD_CALC);
    DrawTemplate(BLACK, WHITE);
    tLED = tickRead();          //Inicio el tiempo de heartbeat
    while(1) {
        
        //Comprobamos constantemente los estados del ENCODER 
        ActualizarENCODER();
        ActualizarTEC_ENCODER();
        
        //Comprobamos el nivel de batería
        nivBateria = adcRead_mV(AIN4);
        nivBateria = (nivBateria * 100) / 600;
        if(tickRead() - tMEDICION > 250) {
            peso = HX711Read();
            ILI9486_DrawNumber(200, 50, 500, BLACK, WHITE, 8);
            
            if(nivBateria > 50) {
                ILI9486_DrawNumber(33, 310, nivBateria, GREEN, WHITE, 6);
            }
            else if(nivBateria > 20) {
                ILI9486_DrawNumber(33, 310, nivBateria, YELLOW, WHITE, 6);
            }
            else {
                ILI9486_DrawNumber(33, 325, nivBateria, RED, WHITE, 6);                
            }
            printf("Peso: %lu\nMuestra: %d\n\n", peso, numMuestra);
            tMEDICION = tickRead();
        }
        
        //Led de Heartbeat
        if (tickRead()-tLED > 100){
            PIN_LED = !PIN_LED;
            tLED = tickRead();
        }
    }   //Fin del main()
}
/*==================[definiciones de funciones internas]=====================*/



/******************************************************************************/