#include "Controlador.h"
#include "GLCD_Draw.h"
#include "GLCD_Text.h"

//deberia estar en LL

uint16_t abs(int16_t a){       
    if (a<0) 
        return (-a);
    
    return a;
}



// Funci贸n para dibujar l铆nea horizontal (optimizada)
void ILI9486_DrawHLine(uint16_t x, uint16_t y, uint16_t length, uint16_t color) {
    
    if(y >= 320) return;
    if(x + length > 480) length = 480 - x;
    LCDENABLE(TRUE);
    ILI9486_SetWindow(x, y, x + length - 1, y);
    
    for(uint16_t i = 0; i < length; i++) {
        ILI9486_WritePixel(color);
    }
    LCDENABLE(FALSE);
}

// Funci贸n para dibujar l铆nea vertical (optimizada)
void ILI9486_DrawVLine(uint16_t x, uint16_t y, uint16_t length, uint16_t color) {
    if(x >= 320) return;
    if(y + length > 480) length = 480 - y;
    
    LCDENABLE(TRUE);
    ILI9486_SetWindow(x, y, x, y + length - 1);
    
    for(uint16_t i = 0; i < length; i++) {
        ILI9486_WritePixel(color);
    }
    LCDENABLE(FALSE);
}

// Funci贸n para dibujar l铆nea recta entre dos puntos (Algoritmo de Bresenham)
void ILI9486_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    int16_t dx = abs(x2 - x1);
    int16_t dy = abs(y2 - y1);
    int16_t sx = (x1 < x2) ? 1 : -1;
    int16_t sy = (y1 < y2) ? 1 : -1;
    int16_t err = dx - dy;
    LCDENABLE(TRUE);
    
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
    LCDENABLE(FALSE);
}


// Funci贸n auxiliar para dibujar un p铆xel del octante con verificaci贸n de l铆mites.
// Esto previene pasar coordenadas negativas (que se convertir铆an en uint16_t grandes)
// a la funci贸n DrawPixel, evitando un posible 'cuelgue' del controlador ILI9486.
void DrawOctantPixel(int16_t x_coord, int16_t y_coord, uint16_t color) {
    // Usamos int16_t para la verificaci贸n. Si es negativo, lo ignoramos.
    if (x_coord >= 0 && y_coord >= 0) {
        // Solo llamamos a DrawPixel si las coordenadas son v谩lidas (positivas o cero).
        // La conversi贸n a uint16_t aqu铆 es segura.
        ILI9486_DrawPixel((uint16_t)x_coord, (uint16_t)y_coord, color);
    }
}

// Funci贸n para dibujar un c铆rculo (Algoritmo de Bresenham)
void ILI9486_DrawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) {
    int16_t x = radius;
    int16_t y = 0;
    int16_t err = 0;
    
    LCDENABLE(TRUE);
    
    while(x >= y) {
        // Octante 1 (++)
        DrawOctantPixel(x0 + x, y0 + y, color);
        // Octante 2 (+y, +x)
        DrawOctantPixel(x0 + y, y0 + x, color);
        // Octante 3 (-y, +x)
        DrawOctantPixel(x0 - y, y0 + x, color);
        // Octante 4 (-x, +y)
        DrawOctantPixel(x0 - x, y0 + y, color);
        // Octante 5 (-x, -y)
        DrawOctantPixel(x0 - x, y0 - y, color);
        // Octante 6 (-y, -x)
        DrawOctantPixel(x0 - y, y0 - x, color);
        // Octante 7 (+y, -x)
        DrawOctantPixel(x0 + y, y0 - x, color);
        // Octante 8 (+x, -y)
        DrawOctantPixel(x0 + x, y0 - y, color);
        // L贸gica de Bresenham (Midpoint)
        if(err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        // Usamos else if para evitar doble actualizaci贸n de x y y en el mismo ciclo, 
        // aunque el original funciona, 'else if' es m谩s claro para este algoritmo.
        else { 
            x -= 1;
            err -= 2*x + 1;
        }
    
    
    /*
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
            */
           
    }
    LCDENABLE(FALSE);
}

// Funci贸n para dibujar un c铆rculo relleno
void ILI9486_DrawFilledCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color) {
    int16_t x = radius;
    int16_t y = 0;
    int16_t err = 0;
    LCDENABLE(TRUE);
    
    while(x >= y) {
        // Dibujar l铆neas horizontales para rellenar
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
    LCDENABLE(FALSE);
}

void DrawTemplate(uint16_t color, uint16_t bg_color) {
    //Fondo unicolor
    ILI9486_ClearScreen(bg_color);
    
    //Divisi髇 vertical
    ILI9486_DrawVLine(190, 0, 320, color);
    ILI9486_DrawVLine(191, 0, 320, color);
    ILI9486_DrawVLine(189, 0, 320, color);
    
    //Divisi髇 horizontal
    ILI9486_DrawHLine(0, 105, 191, color);
    ILI9486_DrawHLine(0, 106, 191, color);
    
    ILI9486_DrawHLine(0, 212, 191, color);
    ILI9486_DrawHLine(0, 213, 191, color);
    
    ILI9486_DrawHLine(191, 159, 1000, color);
    ILI9486_DrawHLine(191, 160, 289, color);
    ILI9486_DrawHLine(191, 161, 289, color);
    
/*==================================Texto=====================================*/
    //Area de Peso
    ILI9486_DrawText(290, 10, "PESO", color, bg_color, 3);
    ILI9486_DrawNumber(200, 50, 100, color, bg_color, 10);
    
    //Area de Peso Inicial
    ILI9486_DrawText(300, 300, "PESO INICIAL", color, bg_color, 2);
    ILI9486_DrawNumber(231, 330, 200, color, bg_color, 7);
    
    //Area de Alerta
    ILI9486_DrawText(195, 300, "ALERTA", color, bg_color, 2);
    ILI9486_DrawNumber(127, 330, 300, color, bg_color, 7);
    
    //Area de bater韆
    ILI9486_DrawText(87, 300, "BATERIA", color, bg_color, 2);
    ILI9486_DrawNumber(23, 330, 40, color, bg_color, 7);
    
    //Area de Porcentaje
    ILI9486_DrawText(130, 10, "PORCENTAJE", color, bg_color, 3);
    ILI9486_DrawNumber(20, 50, 50, color, bg_color, 10);
    
}
