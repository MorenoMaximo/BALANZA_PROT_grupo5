/*
  SE IMPLEMENTAN LAS FUCNIONES BASICAS PARA DIBUJAR EN LA PANTALLA

*/

#include "GLCD_Text.h"
#include <stdint.h>
#include <string.h>

// Datos de la fuente para "grupo5" (G, R, U, P, O, 5)
const uint8_t font_G[] = {
    0x1E, 0x21, 0x40, 0x40, 0x4E, 0x41, 0x21, 0x1E
};

const uint8_t font_R[] = {
    0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x41
};

const uint8_t font_U[] = {
    0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1C
};

const uint8_t font_P[] = {
    0x7C, 0x42, 0x42, 0x42, 0x7C, 0x40, 0x40, 0x40
};

const uint8_t font_O[] = {
    0x1C, 0x22, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1C
};

const uint8_t font_5[] = {
    0x3E, 0x20, 0x20, 0x3C, 0x02, 0x02, 0x22, 0x1C
};

// Tabla de caracteres disponibles
FontChar font_table[] = {
    {5, 7, font_G}, // G
    {5, 7, font_R}, // R
    {5, 7, font_U}, // U
    {5, 7, font_P}, // P
    {5, 7, font_O}, // O
    {5, 7, font_5}  // 5
};

// Función para dibujar un carácter
void ILI9486_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg_color) {
    FontChar *font_char = NULL;
    uint8_t char_index = 0;
    
    // Mapear carácter al índice de la tabla (Metodo FEOO!!!!!!)
    switch(c) {
        case 'G': case 'g': char_index = 0; break;
        case 'R': case 'r': char_index = 1; break;
        case 'U': case 'u': char_index = 2; break;
        case 'P': case 'p': char_index = 3; break;
        case 'O': case 'o': char_index = 4; break;
        case '5': char_index = 5; break;
        default: return; // Carácter no soportado
    }
    
    font_char = &font_table[char_index];
    
    // Dibujar el carácter píxel por píxel
    for(uint8_t row = 0; row < font_char->height; row++) {
        for(uint8_t col = 0; col < font_char->width; col++) {
            // Verificar si el bit está activo en los datos de la fuente
            if(font_char->data[row] & (1 << (7 - col))) {
                ILI9486_DrawPixel(x + col, y + row, color);
            } else if(bg_color != 0xFFFF) { // 0xFFFF = transparente
                ILI9486_DrawPixel(x + col, y + row, bg_color);
            }
        }
    }
}

// Función para escribir texto
void ILI9486_DrawText(uint16_t x, uint16_t y, const char *text, uint16_t color, uint16_t bg_color) {
    uint16_t current_x = x;
    
    while(*text) {
        ILI9486_DrawChar(current_x, y, *text, color, bg_color);
        current_x += 6; // Ancho del carácter + 1 píxel de espacio
        text++;
    }
}