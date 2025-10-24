#include "Controlador.h"
#include "GLCD_Draw.h"

//deberia estar en LL

uint16_t abs(uint16_t a){       
    if (a<0) 
        return (-a);
    
    return a;
}



// Función para dibujar línea horizontal (optimizada)
void ILI9486_DrawHLine(uint16_t x, uint16_t y, uint16_t length, uint16_t color) {
    if(y >= 480) return;
    if(x + length > 320) length = 320 - x;
    
    ILI9486_SetWindow(x, y, x + length - 1, y);
    
    for(uint16_t i = 0; i < length; i++) {
        ILI9486_WritePixel(color);
    }
}

// Función para dibujar línea vertical (optimizada)
void ILI9486_DrawVLine(uint16_t x, uint16_t y, uint16_t length, uint16_t color) {
    if(x >= 320) return;
    if(y + length > 480) length = 480 - y;
    
    ILI9486_SetWindow(x, y, x, y + length - 1);
    
    for(uint16_t i = 0; i < length; i++) {
        ILI9486_WritePixel(color);
    }
}

// Función para dibujar línea recta entre dos puntos (Algoritmo de Bresenham)
void ILI9486_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    int16_t dx = abs(x2 - x1);
    int16_t dy = abs(y2 - y1);
    int16_t sx = (x1 < x2) ? 1 : -1;
    int16_t sy = (y1 < y2) ? 1 : -1;
    int16_t err = dx - dy;
    
    while(1) {
        ILI9486_DrawPixel(x1, y1, color);
        
        if(x1 == x2 && y1 == y2) break;
        
        int16_t e2 = 2 * err;
        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Función para dibujar un círculo (Algoritmo de Bresenham)
void ILI9486_DrawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) {
    int16_t x = radius;
    int16_t y = 0;
    int16_t err = 0;
    
    while(x >= y) {
        ILI9486_DrawPixel(x0 + x, y0 + y, color);
        ILI9486_DrawPixel(x0 + y, y0 + x, color);
        ILI9486_DrawPixel(x0 - y, y0 + x, color);
        ILI9486_DrawPixel(x0 - x, y0 + y, color);
        ILI9486_DrawPixel(x0 - x, y0 - y, color);
        ILI9486_DrawPixel(x0 - y, y0 - x, color);
        ILI9486_DrawPixel(x0 + y, y0 - x, color);
        ILI9486_DrawPixel(x0 + x, y0 - y, color);
        
        if(err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if(err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

// Función para dibujar un círculo relleno
void ILI9486_DrawFilledCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) {
    int16_t x = radius;
    int16_t y = 0;
    int16_t err = 0;
    
    while(x >= y) {
        // Dibujar líneas horizontales para rellenar
        ILI9486_DrawHLine(x0 - x, y0 + y, 2 * x, color);
        ILI9486_DrawHLine(x0 - x, y0 - y, 2 * x, color);
        ILI9486_DrawHLine(x0 - y, y0 + x, 2 * y, color);
        ILI9486_DrawHLine(x0 - y, y0 - x, 2 * y, color);
        
        if(err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if(err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}