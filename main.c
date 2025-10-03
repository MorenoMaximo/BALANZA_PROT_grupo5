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

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "user.h"
#include "uart.h"
#include "system.h"
#include "hx711.h"

//Peso programado por defecto
/*unsigned int numProgramado = 100;
unsigned char strProgramado[4];
unsigned int opMenu;*/

//Codigo principal
void main(void) {
    appInit();                  //Inicializo las entradas y salidas
    
    uint8_t numMuestra = 0;
    unsigned long peso;
    PIN_LED_R = 0;
    PIN_LED_AM = 0;
    PIN_LED_V = 0;
    
    while(1) {
        
        if(PIN_TEC1 == 0) {         //Setear el peso en 0
            PIN_LED_R = 1;
            __delay_ms(20);         //delay de seguridad por el boton
            
            peso = TaraSet();
            __delay_ms(1);
            PIN_LED_R = 0;
            
            while(PIN_TEC1 == 0);
            __delay_ms(20);         //delay de seguridad por el boton            
        }
        
        if(PIN_TEC2 == 0) {         //Una sola muestra
            __delay_ms(20);         //delay de seguridad por el boton
            PIN_LED_AM = 1;
            
            peso = LecturaPeso();
            printf("%lu\n", peso);
            
            __delay_ms(1);
            PIN_LED_AM = 0;
            
            while(PIN_TEC2 == 0);
            __delay_ms(20);         //delay de seguridad por el boton            
        }
        
        if(PIN_TEC3 == 0) {
            __delay_ms(20);         //delay de seguridad por el boton
            PIN_LED_V = 1;
            
            while(peso != 0 && numMuestra < 100) {
                peso = LecturaPeso();
                printf("%lu , %d\n", peso, numMuestra++);
                __delay_ms(100);
            }
            PIN_LED_V = 0;
            numMuestra = 0;
            __delay_ms(20);         //delay de seguridad por el boton            
        }
        
        if(PIN_TEC4 == 0) {
            printf("stop\n");
        }
    }
}   //Fin del main()
/******************************************************************************/