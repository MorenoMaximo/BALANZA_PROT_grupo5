#include "system.h"
#include "TFT_ILI9486_LL.h"
#include "GLCD_Draw.h"
#include "GLCD_Text.h"


/*
Inicializacion del display
*/
#if 0
// 1. Reset del display
void TFT_Reset(void) {
    RESX_LOW();     // Activar reset
    Delay(100);     // Esperar 100ms
    RESX_HIGH();    // Desactivar reset
    Delay(120);     // Esperar 120ms después del reset
}

// 2. Secuencia de inicialización básica
void ILI9486_Init(void) {

    TFT_Reset();
    
    // Sleep Out
    ILI9486_WriteCommand(0x11);
    Delay(120);
    
    // Display Inversion On
    ILI9486_WriteCommand(0x21);
    
    // Interface Pixel Format - 16 bits/pixel (RGB 5-6-5)
    ILI9486_WriteCommand(0x3A);
    ILI9486_WriteData(0x55);    // 16 bits por pixel
    
    // Memory Access Control
    ILI9486_WriteCommand(0x36);
    ILI9486_WriteData(0x48);    // Configuración de orientación
    
    // Display On
    ILI9486_WriteCommand(0x29);
    Delay(50);
}

// 3. Configurar área de dibujo
void SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
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


// Escribir un píxel en color RGB565 (16 bits)
void ILI9486_WritePixel(uint16_t color) {
    // En interfaz de 8 bits, enviar 2 bytes por píxel
    ILI9486_WriteData(color >> 8);    // Byte alto
    ILI9486_WriteData(color & 0xFF);  // Byte bajo
}
#endif

// Escribir imagen completa
void ILI9486_WriteImage(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, 
                        uint16_t *image_data, uint32_t data_size) {
    // Configurar ventana de escritura
    ILI9486_SetWindow(x1, y1, x2, y2);
    
    // Escribir todos los datos de la imagen
    for(uint32_t i = 0; i < data_size; i++) {
        ILI9486_WritePixel(image_data[i]);
    }
}

// Ejemplo de uso para pantalla completa (320x480)
void DrawFullScreenImage(uint16_t *image) {
    ILI9486_WriteImage(0, 0, 319, 479, image, 320*480);
}

// Escribir bloque rectangular más eficiente
void ILI9486_WriteBlock(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, 
                        uint16_t color) {
    uint32_t pixel_count = (x2 - x1 + 1) * (y2 - y1 + 1);
    
    ILI9486_SetWindow(x1, y1, x2, y2);
    
    // Escribir todos los píxeles del mismo color
    for(uint32_t i = 0; i < pixel_count; i++) {
        ILI9486_WritePixel(color);
    }
}


//-----------------------------------


// Demostracion de todas las funciones
void Demo_TodasFunctions(void) {
    // Limpiar pantalla
    ILI9486_ClearScreen(COLOR_BLACK);
    Delay_ms(500);
    
    // 1. Lineas horizontales y verticales
    ILI9486_DrawHLine(50, 50, 200, COLOR_RED);
    ILI9486_DrawVLine(150, 80, 100, COLOR_GREEN);
    Delay_ms(500);
    
    // 2. Lineas diagonales
    ILI9486_DrawLine(50, 200, 250, 250, COLOR_BLUE);
    ILI9486_DrawLine(250, 200, 50, 250, COLOR_YELLOW);
    Delay_ms(500);
    
    // 3. Circulos
//    ILI9486_DrawCircle(100, 150, 25, COLOR_CYAN);
//    ILI9486_DrawCircle(220, 150, 30, COLOR_MAGENTA);
//    Delay_ms(500);
    
    // 4. Texto "grupo5"
    ILI9486_DrawText(100, 300, "grupo5", COLOR_RED, COLOR_GREEN);
    Delay_ms(1000);
    
    // 5. Texto en diferente posicion y color
    ILI9486_DrawText(80, 320, "grupo5", COLOR_YELLOW, COLOR_RED);
    Delay_ms(1000);
    
    // 6. Marco alrededor
    ILI9486_DrawHLine(10, 10, 300, COLOR_WHITE);
    ILI9486_DrawHLine(10, 470, 300, COLOR_WHITE);
    ILI9486_DrawVLine(10, 10, 460, COLOR_WHITE);
    ILI9486_DrawVLine(310, 10, 460, COLOR_WHITE);
}

void ejemplo(void){

     // Inicializar puertos
    Ports_Init();
    
    // Inicializar display
    ILI9486_Init();
    
    // Ejecutar demostracion
    //Demo_TodasFunctions();
    
    ILI9486_ClearScreen(COLOR_BLACK);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_WHITE);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_CYAN);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_YELLOW);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_MAGENTA);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_RED);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_BLUE);
    __delay_ms(1000);
    ILI9486_ClearScreen(COLOR_GREEN);
    __delay_ms(1000);
}
