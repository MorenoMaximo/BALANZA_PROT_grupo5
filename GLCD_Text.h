#ifndef GLCD_TEXT_H_
#define GLCD_TEXT_H_

#include "Controlador.h"
#include "GLCD_Draw.h"


void ILI9486_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg_color) ;

void ILI9486_DrawText(uint16_t x, uint16_t y, const char *text, uint16_t color, uint16_t bg_color) ;


#endif /* GLCD_TEXT_H_ */
