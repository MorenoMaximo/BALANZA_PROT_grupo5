/*
 * TFT_ILI9325_320x000_LL.c
 *
 *  Created on: //2025
 *      Author: gabriel
 */

#include "TFT_ILI9486_LL.h"



// Configuración del PIC
/*
#pragma config FOSC = INTOSCIO  // Oscilador interno
#pragma config WDTE = OFF       // Watchdog deshabilitado
#pragma config PWRTE = OFF      // Power-up Timer deshabilitado
#pragma config MCLRE = ON       // MCLR habilitado
#pragma config CP = OFF         // Protección de código deshabilitada
#pragma config CPD = OFF        // Protección de datos deshabilitada
#pragma config BOREN = ON       // Brown-out Reset habilitado
#pragma config IESO = ON        // Internal/External Switchover
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor
*/
// Función de delay simple
void Delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 1000; j++) {
            NOP();
        }
    }
}



// Inicialización de puertos
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
    
    //??? Usan la de su placa
    // Configurar oscilador interno a 8MHz
    //OSCCON = 0x70;  // IRCF = 111 (8MHz), INTOSC
}



//---------------- fuciones basicas para escribir -------------

// Reset del display
void ILI9486_Reset(void) { 
    LCD_RESET_LOW();
    Delay_ms(100);      // Esperar 100ms
    LCD_RESET_HIGH();
    Delay_ms(120);      // Esperar 120ms después del reset
}

// Escribir comando
void ILI9486_WriteCommand(uint8_t cmd) {
    LCD_RS_LOW();       // Modo comando
    LCD_CS_LOW();       // Seleccionar chip
    
    DATA_BUS = cmd;     // Escribir comando en el bus
    
    LCD_WR_LOW();       // Preparar escritura
    NOP(); NOP();       // Pequeño delay para estabilidad
    LCD_WR_HIGH();      // Flanco de subida - captura dato
    
    LCD_CS_HIGH();      // Deseleccionar chip
}

// Escribir dato
void ILI9486_WriteData(uint8_t data) {
    LCD_RS_HIGH();      // Modo dato
    LCD_CS_LOW();       // Seleccionar chip
    
    DATA_BUS = data;    // Escribir dato en el bus
    
    LCD_WR_LOW();       // Preparar escritura
    NOP(); NOP();       // Pequeño delay para estabilidad
    LCD_WR_HIGH();      // Flanco de subida - captura dato
    
    LCD_CS_HIGH();      // Deseleccionar chip
}



// Secuencia de inicialización del display
void ILI9486_Init(void) {
    // Configurar pines de control
    LCD_CS_HIGH();
    LCD_RS_HIGH();
    LCD_WR_HIGH();
    LCD_RD_HIGH();      // Siempre en alto si no se usa lectura
    
    // Reset del display
    ILI9486_Reset();
    
    // Secuencia de inicialización
    ILI9486_WriteCommand(0x11); // Sleep Out
    Delay_ms(120);
    
    ILI9486_WriteCommand(0x21); // Display Inversion On
    
    ILI9486_WriteCommand(0x3A); // Interface Pixel Format
    ILI9486_WriteData(0x55);    // 16 bits por pixel (RGB 5-6-5)
    
    ILI9486_WriteCommand(0x36); // Memory Access Control
    ILI9486_WriteData(0x48);    // Configuración de orientación
    
    ILI9486_WriteCommand(0x29); // Display On
    Delay_ms(50);
}

// Configurar área de dibujo

void ILI9486_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    // Set Column Address
    ILI9486_WriteCommand(0x2A);
    ILI9486_WriteData(x1 >> 8);
    ILI9486_WriteData(x1 & 0xFF);
    ILI9486_WriteData(x2 >> 8);
    ILI9486_WriteData(x2 & 0xFF);
    
    // Set Page Address
    ILI9486_WriteCommand(0x2B);
    ILI9486_WriteData(y1 >> 8);
    ILI9486_WriteData(y1 & 0xFF);
    ILI9486_WriteData(y2 >> 8);
    ILI9486_WriteData(y2 & 0xFF);
    
    // Memory Write
    ILI9486_WriteCommand(0x2C);
}

//deberia estar en LL
// Escribir un pixel en color RGB565
void ILI9486_WritePixel(uint16_t color) {
    ILI9486_WriteData(color >> 8);    // Byte alto
    ILI9486_WriteData(color & 0xFF);  // Byte bajo
}



// Dibujar un píxel individual
void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if(x >= 320 || y >= 480) return;
    
    ILI9486_SetWindow(x, y, x, y);
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
void ILI9486_ClearScreen(uint16_t color) {
//    ILI9486_WriteBlock(0, 0, 319, 479, color);
    ILI9486_SetWindow(0, 0, 319, 479);
    
    for(uint32_t i = 0; i < 320 * 480; i++) {
        ILI9486_WritePixel(color);
    }

}




//---------------------------------


// Comienzo de funciones configuracion y utilidad del display
void Address_set(Ctr_GDisplay* HndTft, unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
// TODO cambian para el display de los chicos
  LCD_WR_REG( HndTft, 0x0020 ); LCD_WR_DATA8( HndTft, x1>>8, x1 );    // Set the X coordinate position
  LCD_WR_REG( HndTft, 0x0021 ); LCD_WR_DATA8( HndTft, y1>>8, y1 );    // Set the Y coordinate position
  LCD_WR_REG( HndTft, 0x0050 ); LCD_WR_DATA8( HndTft, x1>>8, x1 );    //Start X
  LCD_WR_REG( HndTft, 0x0052 ); LCD_WR_DATA8( HndTft, y1>>8, y1 );    //Start Y
  LCD_WR_REG( HndTft, 0x0051 ); LCD_WR_DATA8( HndTft, x2>>8, x2 );    //End X
  LCD_WR_REG( HndTft, 0x0053 ); LCD_WR_DATA8( HndTft, y2>>8, y2 );    //End Y
  LCD_WR_REG( HndTft, 0x0022 );
}

//Dotted
//POINT_COLOR:The color of this point
void LCD_DrawPoint(Ctr_GDisplay* HndTft, uint16_t x,uint16_t y, uint16_t PointColor)
{
  Address_set( HndTft, x, y, x, y );//Setting the cursor position
  LCD_WR_DATA( HndTft, PointColor );
}

/*
 * Dibujar Linea
 *    Se encarga de dibujar todos los puntos que pertenecen a la linea deseada.
 *    Se implementa el algoritmo de Bresenham
 *
 * Argumentos:
 *   uint16_t x1, uint16_t y1: Par de coordenadas cartesianas (x;y) de comienzo de la linea.
 *   uint16_t x2, uint16_t y2: Par de coordenadas cartesianas (x;y) de final de la linea.
 *   uint16_t Color :              Color de los puntos que pertenecen a la linea.
 * */

void LCD_DrawLine(Ctr_GDisplay* HndTft, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Color)
{
  uint16_t  t;
  int   xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx, incy, uRow, uCol;

  delta_x = x2-x1; //Calculate the coordinates of the incremental
  delta_y = y2-y1;
  uRow = x1;
  uCol = y1;

  if( delta_x > 0 )             incx = 1;  //Set single-step directions
  else if( delta_x == 0 )   incx = 0;  //Vertical line
  else {
    incx =- 1;
    delta_x =- delta_x;
  }

  if( delta_y > 0 )             incy = 1;
  else if( delta_y == 0 )   incy = 0;//Level
  else{
    incy =- 1;
    delta_y =- delta_y;
  }

  if( delta_x > delta_y )  distance = delta_x; //Select the basic incremental axis
  else distance = delta_y;

  for( t=0; t <= distance+1; t++ )    // Dibujo el punto de la linea
  {
      LCD_DrawPoint( HndTft, uRow, uCol, Color );  //Dotted
      xerr+=delta_x ;
      yerr+=delta_y ;
      if( xerr > distance )
      {
          xerr -= distance;
          uRow += incx;
      }
      if( yerr > distance )
      {
          yerr -= distance;
          uCol += incy;
      }
  }
}

