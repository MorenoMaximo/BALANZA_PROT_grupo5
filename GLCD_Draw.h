#ifndef GLCD_DRAW_H_
#define GLCD_DRAW_H_

#include"GLCD_Draw.h"
#include"TFT_ILI9486_LL.h"


// Definición de caracteres básicos (5x7 pixels)
typedef struct {
    uint8_t width;
    uint8_t height;
    const uint8_t *data;
} FontChar;


//void ILI9486_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) ;
//void ILI9486_WritePixel(uint16_t color) ;
//void ILI9486_DrawPixel(uint16_t x, uint16_t y, uint16_t color) ;
void ILI9486_DrawHLine(uint16_t x, uint16_t y, uint16_t length, uint16_t color) ;
void ILI9486_DrawVLine(uint16_t x, uint16_t y, uint16_t length, uint16_t color) ;
void ILI9486_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) ;
void ILI9486_DrawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) ;
void ILI9486_DrawFilledCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) ;








#endif /* GLCD_DRAW_H_ */
