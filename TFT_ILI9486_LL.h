/*
 * TFT_ILI9486_LL.h
 *
 *   Se implementan las funciones para leer escribir en el display y hacer las operaciones mas basicas.
 *   escribir comando datos posicion en al memoria del display, Dibujar puntos, lineas, circuos y rectangulos.
 *  Created on: 00/00/2025
 *      Author: gabriel
 */

#ifndef TFT_ILI9486_LL_H_
#define TFT_ILI9486_LL_H_

#include"Controlador.h"

#define TRUE 1  
#define FALSE 0

//#define LCDENABLE(a)     (a==TRUE?LcdEnable_Flag=1:LcdEnable_Flag=0)
#define LCDENABLE(a)     ((a==TRUE)?LCD_CS = 0:LCD_CS = 1)
/*
#define LCD_CS_LOW()     (LcdEnable_Flag==0 ?LCD_CS = 0:LCD_CS = LCD_CS) //LCD_CS = 0
#define LCD_CS_HIGH()    (LcdEnable_Flag==0 ?LCD_CS = 1:LCD_CS = LCD_CS) //LCD_CS = 1
*/
#define LCD_CS_LOW()      LCD_CS = 0
#define LCD_CS_HIGH()     LCD_CS = 1

extern uint8_t LcdEnable_Flag;
/*
 * Hardware Setup:
 *  Operating voltage of 3.3V
 *  La interfaz bus de comunicaciones es seleccionada segun los pines IM2 IM1 IM0
 *  8 bits => IM2=0 IM1=1 IM0=1
 *  IO connections between MCU and LCD:
 *  Data Low:
 *    LCD(DB0-DB7) = P0^0-P0^7; (Ignore-No Connect if LCD operated in 8-bit mode which is default)
 *  Data High:
 *    LCD(DB8-DB15) = P2^0-P2^7;
 * portd lcdD0 -> rd0 ... rd7

Pines de Control:
IM2, IM1, IM0 = 0, 1, 1 (para interfaz 8080 de 8 bits)

CSX - Chip Select (activo en bajo)

D/CX - Data/Command Select (L: comando, H: dato)

WRX - Write Strobe (flanco de subida)

RDX - Read Strobe (puede fijarse a HIGH si no se usa lectura)

RESX - Reset (activo en bajo)

DB[7:0] - Bus de datos de 8 bits

Pines de alimentación:
IOVCC = 1.65V - 3.6V (lógica digital)

VCI = 2.5V - 3.6V (analógica)

*/

/*
#define LCD_RD       PORTBbits.RB0	  //	PuertoC-6 pin 8
#define LCD_WR       PORTBbits.RB1	  //	PuertoC-3 pin 7 
#define LCD_RS	     PORTBbits.RB2	  //	PuertoC-4 pin 6 
#define LCD_CS	     PORTBbits.RB3	  //	PuertoC-7 pin 9
#define LCD_RESET    PORTBbits.RB4	  //	PuertoB-6 pin 11 
#define LCD_D0       PORTDbits.RD0	  //	PuertoB-4 pin 13
#define LCD_D1       PORTDbits.RD1	  //	PuertoC-2 pin 14
#define LCD_D2       PORTDbits.RD2    //	PuertoA-4 pin 3     
#define LCD_D3       PORTDbits.RD3    //	PuertoA-3 pin 4     
#define LCD_D4       PORTDbits.RD4	  //	PuertoB-4 pin 13
#define LCD_D5       PORTDbits.RD5	  //	PuertoC-2 pin 14
#define LCD_D6       PORTDbits.RD6    //	PuertoA-4 pin 3     
#define LCD_D7       PORTDbits.RD7    //	PuertoA-3 pin 4     
#define DATA_BUS     PORTD
*/

typedef enum
  {
    ORIENTATION_LANDSCAPE,
    ORIENTATION_PORTRAIT,
    ORIENTATION_PORTRAIT_1,
    ORIENTATION_PORTRAIT_2,
    ORIENTATION_LANDSCAPE_1,
    ORIENTATION_LANDSCAPE_2
} eGLCD_Orientation;
// ****************** //




// Definiciones de pines según tu configuración
#define LCD_RD       PORTBbits.RB0    // PuertoB-0 pin 6
#define LCD_WR       PORTBbits.RB1    // PuertoB-1 pin 7
#define LCD_RS       PORTBbits.RB2    // PuertoB-2 pin 8
#define LCD_CS       PORTBbits.RB3    // PuertoB-3 pin 9
#define LCD_RESET    PORTBbits.RB4    // PuertoB-4 pin 10

// Bus de datos en PORTD completo
#define LCD_D0       PORTDbits.RD0    // PuertoD-0 pin 19
#define LCD_D1       PORTDbits.RD1    // PuertoD-1 pin 20
#define LCD_D2       PORTDbits.RD2    // PuertoD-2 pin 21
#define LCD_D3       PORTDbits.RD3    // PuertoD-3 pin 22
#define LCD_D4       PORTDbits.RD4    // PuertoD-4 pin 27
#define LCD_D5       PORTDbits.RD5    // PuertoD-5 pin 28
#define LCD_D6       PORTDbits.RD6    // PuertoD-6 pin 29
#define LCD_D7       PORTDbits.RD7    // PuertoD-7 pin 30

#define DATA_BUS     PORTD



// Macros para control de pines
//#define LCD_CS_LOW()     LCD_CS = 0
//#define LCD_CS_HIGH()    LCD_CS = 1

#define LCD_RS_LOW()     LCD_RS = 0
#define LCD_RS_HIGH()    LCD_RS = 1
#define LCD_WR_LOW()     LCD_WR = 0
#define LCD_WR_HIGH()    LCD_WR = 1
#define LCD_RD_LOW()     LCD_RD = 0
#define LCD_RD_HIGH()    LCD_RD = 1
#define LCD_RESET_LOW()  LCD_RESET = 0
#define LCD_RESET_HIGH() LCD_RESET = 1

//TODO: IOMplementar ddefine




// Colores en formato RGB565
#define BLACK   0xFFFF
#define WHITE   0x0000
#define CYAN    0xF800
#define MAGENTA 0x07E0
#define YELLOW  0x001F
#define BLUE    0xFFE0
#define RED     0x07FF
#define GREEN   0xF81F

void Ports_Init(void);
void ILI9486_Init(void);
void ILI9486_Reset(void);
void ILI9486_WriteCommand(uint8_t cmd);
void ILI9486_WriteData(uint8_t data) ;

void ILI9486_WritePixel(uint16_t color) ;
void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color) ;
void ILI9486_DrawPixelC(uint16_t x, uint16_t y, uint16_t color);

void ILI9486_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
void ILI9486_SetRotation(uint8_t rotation) ;
void ILI9486_ClearScreen(uint16_t color) ;


#endif /* TFT_ILI9325_320X240_LL_H_ */
