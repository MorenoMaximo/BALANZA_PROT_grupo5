/*
 * TFT_ILI9325_320x000_LL.c
 *
 *  Created on: //2025
 *      Author: gabriel
 */

#include "TFT_ILI9486_LL.h"
#include "system.h"
#include <stdint.h>
#include <xc.h>



// Configuraci贸n del PIC
/*
#pragma config FOSC = INTOSCIO  // Oscilador interno
#pragma config WDTE = OFF       // Watchdog deshabilitado
#pragma config PWRTE = OFF      // Power-up Timer deshabilitado
#pragma config MCLRE = ON       // MCLR habilitado
#pragma config CP = OFF         // Protecci贸n de c贸digo deshabilitada
#pragma config CPD = OFF        // Protecci贸n de datos deshabilitada
#pragma config BOREN = ON       // Brown-out Reset habilitado
#pragma config IESO = ON        // Internal/External Switchover
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor
*/
// Funci贸n de delay simple
uint8_t LcdEnable_Flag = 0;

// Inicializaci贸n de puertos
void Ports_Init(void) {
  //TODO:  Verificar con Maxi
    // PORTB como salida digital (pines de control)
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    
    // PORTD como salida digital (bus de datos)
    TRISD = 0x00;   // Todos los pines de PORTD como salidas
    PORTD = 0x00;   // Inicializar en bajo
    
}



//---------------- fuciones basicas para escribir -------------

// Reset del display
void ILI9486_Reset(void) { 
    LCD_RESET_LOW();
    __delay_ms(100);      // Esperar 100ms
    LCD_RESET_HIGH();
    __delay_ms(120);      // Esperar 120ms despu閟 del reset
}

// Escribir comando
void ILI9486_WriteCommand(uint8_t cmd) {
    LCD_RS_LOW();       // Modo comando
    LCD_CS_LOW();       // Seleccionar chip
    
    DATA_BUS = cmd;     // Escribir comando en el bus
    
    LCD_WR_LOW();       // Preparar escritura
    NOP(); NOP();       // Peque帽o delay para estabilidad
    LCD_WR_HIGH();      // Flanco de subida - captura dato
    
    LCD_CS_HIGH();      // Deseleccionar chip
}

// Escribir dato
void ILI9486_WriteData(uint8_t data) {
    LCD_RS_HIGH();      // Modo dato
    LCD_CS_LOW();       // Seleccionar chip
    
    DATA_BUS = data;    // Escribir dato en el bus
    
    LCD_WR_LOW();       // Preparar escritura
    NOP(); NOP();       // Peque帽o delay para estabilidad
    LCD_WR_HIGH();      // Flanco de subida - captura dato
    
    LCD_CS_HIGH();      // Deseleccionar chip
}



// Secuencia de inicializaci贸n del display
void ILI9486_Init(void) {
    // Configurar pines de control
    Ports_Init();
    LCD_CS_HIGH();
    LCD_RS_HIGH();
    LCD_WR_HIGH();
    LCD_RD_HIGH();      // Siempre en alto si no se usa lectura
    
    // Reset del display
    ILI9486_Reset();

    LCDENABLE(TRUE);
    // Secuencia de inicializaci贸n
    ILI9486_WriteCommand(0x11); // Sleep Out
    __delay_ms(120);
    
    ILI9486_WriteCommand(0x21); // Display Inversion On
    
    ILI9486_WriteCommand(0x3A); // Interface Pixel Format
    ILI9486_WriteData(0x55);    // 16 bits por pixel (RGB 5-6-5)
    
    ILI9486_SetRotation(1);     // Configuraci髇 de orientaci髇
    
    ILI9486_WriteCommand(0x29); // Display On
    __delay_ms(50);
    LCDENABLE(FALSE);

}

// Configurar 谩rea de dibujo

void ILI9486_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {

    LCDENABLE(TRUE);
    // Set Column Address 0x2A 
    ILI9486_WriteCommand(0x2A);     
    ILI9486_WriteData(x1 >> 8);
    ILI9486_WriteData(x1 & 0xFF);
    ILI9486_WriteData(x2 >> 8);
    ILI9486_WriteData(x2 & 0xFF);
    
    // Set Page Address (0x2B)
    ILI9486_WriteCommand(0x2B);     
    ILI9486_WriteData(y1 >> 8);
    ILI9486_WriteData(y1 & 0xFF);
    ILI9486_WriteData(y2 >> 8);
    ILI9486_WriteData(y2 & 0xFF);
    
    // Memory Write (0x2C)
    ILI9486_WriteCommand(0x2C);
    LCDENABLE(FALSE);
}

// Escribir un pixel en color RGB565
void ILI9486_WritePixel(uint16_t color) {
    
    ILI9486_WriteData(color >> 8);    // Byte alto
    ILI9486_WriteData(color & 0xFF);  // Byte bajo
}



// Dibujar un p韝el individual
void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    //if(x >= 320 || y >= 480) return;
    ILI9486_SetWindow(x, y, x, y);
    ILI9486_WritePixel(color);
}

void ILI9486_DrawPixelC(uint16_t x, uint16_t y, uint16_t color)
{
    if(x >= 320 || y >= 480) return;
    //ILI9486_SetWindow(x, y, x, y);
    ILI9486_WritePixel(color);
}


// Rotar pantalla
void ILI9486_SetRotation(uint8_t rotation) {
    ILI9486_WriteCommand(0x36);
    switch(rotation) {
        case 0: ILI9486_WriteData(0x48); break; // Portrait
        case 1: ILI9486_WriteData(0x28); break; // Landscape
        case 2: ILI9486_WriteData(0x88); break; // Portrait invertido
        case 3: ILI9486_WriteData(0xE8); break; // Landscape invertido
    }
}

// Limpiar pantalla
//void ILI9486_ClearScreen(uint16_t color) {
//    LCDENABLE(TRUE);
//    //    ILI9486_WriteBlock(0, 0, 319, 479, color);
//    ILI9486_SetWindow(0, 0, 319, 479);
//    
//    for(uint32_t i = 0; i < 320 * 480; i++) {
//        ILI9486_WritePixel(color);
//    }
//    LCDENABLE(FALSE);
//
//}
void ILI9486_ClearScreen(uint16_t color) {
    ILI9486_SetWindow(0, 0, 479, 319);

    LCD_RS_HIGH();   // modo datos
    LCD_CS_LOW();    // mantener chip seleccionado

    for(uint32_t i = 0; i < 320UL * 480UL; i++) {
        DATA_BUS = color >> 8;
        LCD_WR_LOW(); NOP(); NOP(); LCD_WR_HIGH();

        DATA_BUS = color & 0xFF;
        LCD_WR_LOW(); NOP(); NOP(); LCD_WR_HIGH();
    }

    LCD_CS_HIGH();   // terminar escritura
}
