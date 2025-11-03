/*
  SE IMPLEMENTAN LAS FUCNIONES BASICAS PARA DIBUJAR EN LA PANTALLA

*/

#include "GLCD_Text.h"
#include <stdint.h>
#include <string.h>
/*
// Datos de la fuente 5x7 para "grupo5" (G, R, U, P, O, 5)
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
*/
// TABLA COMPLETA DE CARACTERES ASCII 5x7 
// ESTE METODO NO ES BUENO PORQUE OCUPA MUCHA MEMORIA DECODIGO
// SE PUEDE ELIMINAR 2 BYTE POR CARACTER!!!!
const uint8_t ascii_table[96][7] = {    // ME PARECE QUE VA A SER MUY CHICO 
    {ASCII_ESPACIO},        // 32: espacio
    {ASCII_EXCLAMACION},    // 33: !
    {ASCII_COMILLAS},       // 34: "
    {ASCII_NUMERAL},        // 35: #
    {ASCII_DOLAR},          // 36: $
    {ASCII_PORCIENTO},      // 37: %
    {ASCII_AMPERSAND},      // 38: &
    {ASCII_APOSTROFE},      // 39: '
    {ASCII_PARENTESIS_IZQ}, // 40: (
    {ASCII_PARENTESIS_DER}, // 41: )
    {ASCII_ASTERISCO},      // 42: *
    {ASCII_MAS},            // 43: +
    {ASCII_COMA},           // 44: ,
    {ASCII_MENOS},          // 45: -
    {ASCII_PUNTO},          // 46: .
    {ASCII_SLASH},          // 47: /
    {ASCII_0},              // 48: 0
    {ASCII_1},              // 49: 1
    {ASCII_2},              // 50: 2
    {ASCII_3},              // 51: 3
    {ASCII_4},              // 52: 4
    {ASCII_5},              // 53: 5
    {ASCII_6},              // 54: 6
    {ASCII_7},              // 55: 7
    {ASCII_8},              // 56: 8
    {ASCII_9},              // 57: 9
    {ASCII_DOS_PUNTOS},     // 58: :
    {ASCII_PUNTO_COMA},     // 59: ;
    {ASCII_MENOR_QUE},      // 60: <
    {ASCII_IGUAL},          // 61: =
    {ASCII_MAYOR_QUE},      // 62: >
    {ASCII_INTERROGACION},  // 63: ?
    {ASCII_ARROBA},         // 64: @
    {ASCII_A},              // 65: A
    {ASCII_B},              // 66: B
    {ASCII_C},              // 67: C
    {ASCII_D},              // 68: D
    {ASCII_E},              // 69: E
    {ASCII_F},              // 70: F
    {ASCII_G},              // 71: G
    {ASCII_H},              // 72: H
    {ASCII_I},              // 73: I
    {ASCII_J},              // 74: J
    {ASCII_K},              // 75: K
    {ASCII_L},              // 76: L
    {ASCII_M},              // 77: M
    {ASCII_N},              // 78: N
    {ASCII_O},              // 79: O
    {ASCII_P},              // 80: P
    {ASCII_Q},              // 81: Q
    {ASCII_R},              // 82: R
    {ASCII_S},              // 83: S
    {ASCII_T},              // 84: T
    {ASCII_U},              // 85: U
    {ASCII_V},              // 86: V
    {ASCII_W},              // 87: W
    {ASCII_X},              // 88: X
    {ASCII_Y},              // 89: Y
    {ASCII_Z},              // 90: Z
    {ASCII_CORCHETE_IZQ},   // 91: [
    {ASCII_BACKSLASH},      // 92: backslash
    {ASCII_CORCHETE_DER},   // 93: ]
    {ASCII_CIRCUNFLEJO},    // 94: ^
    {ASCII_GUION_BAJO},     // 95: _
    {ASCII_COMILLA_SIMPLE}, // 96: `
    {ASCII_a},              // 97: a
    {ASCII_b},              // 98: b
    {ASCII_c},              // 99: c
    {ASCII_d},              // 100: d
    {ASCII_e},              // 101: e
    {ASCII_f},              // 102: f
    {ASCII_g},              // 103: g
    {ASCII_h},              // 104: h
    {ASCII_i},              // 105: i
    {ASCII_j},              // 106: j
    {ASCII_k},              // 107: k
    {ASCII_l},              // 108: l
    {ASCII_m},              // 109: m
    {ASCII_n},              // 110: n
    {ASCII_o},              // 111: o
    {ASCII_p},              // 112: p
    {ASCII_q},              // 113: q
    {ASCII_r},              // 114: r
    {ASCII_s},              // 115: s
    {ASCII_t},              // 116: t
    {ASCII_u},              // 117: u
    {ASCII_v},              // 118: v
    {ASCII_w},              // 119: w
    {ASCII_x},              // 120: x
    {ASCII_y},              // 121: y
    {ASCII_z},              // 122: z
    {ASCII_LLAVE_IZQ},      // 123: {
    {ASCII_BARRA_VERTICAL}, // 124: |
    {ASCII_LLAVE_DER},      // 125: }
    {ASCII_VINIETA}         // 126: ~
};

// FunciÃ³n para dibujar un carÃ¡cter
void ILI9486_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg_color, uint8_t scale) {
    FontChar *font_char = NULL;
    uint8_t char_index = 0;
    uint8_t font_data;
    
    // Límite de la escala
    if(scale > 11) {
        scale = 5;
    }
    
   // Validar coordenadas
    if(x >= GET_LCD_WIDTH() || y >= GET_LCD_HEIGHT() ) return;
    // Mapear caracter al índice de la tabla 
    // Convertir caracter a índice de tabla (32-126)
    if(c < 32 || c > 126) {
        char_index = 0; // Caracter no válido, usar espacio
    } else {
        char_index = c - 32;
    }
    //TODO:  VERIFICAR FILAS Y COLUMNAS!!!!!
    
    ILI9486_SetRotation(2);
    LCDENABLE(TRUE);
    
    // seteo una sola vez la ventana apra todo el caracter
    ILI9486_SetWindow(x, y, x + (ASCII_FONT_WIDTH - 1) + scale, y + (ASCII_FONT_HEIGHT - 1) + scale);
    for(uint8_t col = 0; col < 5; col++) {
        font_data = ascii_table[char_index][col];
        for(uint8_t row = 0; row < 7; row++) {
            uint16_t color_to_draw = (font_data & (1 << (6 - row))) ? color : bg_color;
            // Verificar si el bit está activo en los datos de la fuente
            //if(font_char->data[row] & (1 << (7 - col))) {
            //if(ascii_table[char_index][row] & (1 << (4 - col))) {
            // dibujar bloque escalado
            for (uint8_t dy = 0; dy < scale; dy++) {
                for (uint8_t dx = 0; dx < scale; dx++) {
                    ILI9486_DrawPixel(x + row * scale + dx, y + col * scale + dy, color_to_draw);
                    //ILI9486_DrawPixelC(x + col * scale + dx, y + row * scale + dy, color_to_draw);
                }
            }

        }
    }
    LCDENABLE(FALSE);
}
    
// Función para escribir texto 
void ILI9486_DrawText(uint16_t x, uint16_t y, const char *text, uint16_t color, uint16_t bg_color, uint8_t scale) {
    uint16_t current_y = y;
    uint16_t Pos=0;         // tambien corrige el problema del const
    
    // Límite de la escala
    if(scale > 11) {
        scale = 5;
    }
    
    // Recorre el texto carácter por carácter
    while(*(text + Pos) != 0) {
        // Dibuja el carácter actual
        ILI9486_DrawChar(x, current_y, *(text+Pos), color, bg_color, scale);
        
        // Avanza el cursor horizontalmente:
        //  -> ancho del carácter escalado
        //  -> +2 píxeles de margen entre caracteres
        current_y += (ASCII_FONT_WIDTH * scale) + 2;
        //Versión vieja de Gabi
        //(Pos*(ASCII_FONT_HEIGHT+2));
        
        // Avanza al siguiente carácter
        Pos++;
        
        // Si se sale del ancho de pantalla, termina
        if(x + (ASCII_FONT_WIDTH * scale) > GET_LCD_WIDTH()) return;
    }
}



//EJEMPLO: IMPRIMIR UN NUMERO ENTERO (EQUIVALENTE A ITOA)
void ILI9486_DrawNumber(uint16_t x, uint16_t y, int16_t number, uint16_t color, uint16_t bg_color, uint8_t scale) {
    char buffer[12];
    uint8_t i = 0;
    int32_t temp = number;
    
    // Límite de la escala
    if(scale > 11) {
        scale = 5;
    }
    
    // Manejar números negativos
    if(number < 0) {
        buffer[i++] = '-';
        temp = -number;
    }
    
    // Convertir número a string
    do {
        buffer[i++] = '0' + (temp % 10);
        temp /= 10;
    } while(temp > 0);
    
    buffer[i] = '\0';
    
    // Invertir la parte numérica
    uint8_t start = (number < 0) ? 1 : 0;
    uint8_t end = i - 1;
    while(start < end) {
        char temp_char = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp_char;
        start++;
        end--;
    }
    
    ILI9486_DrawText(x, y, buffer, color, bg_color, scale);
}