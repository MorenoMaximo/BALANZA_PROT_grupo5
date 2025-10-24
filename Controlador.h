/*
 * Cantrolador.h
 *  Este modulo se definien los parametros de configuracion 
 *  para el controlador del dsiplay que se este usando
 *
 *  Created on: 25/11/2016
 *      Author: gabriel
 */

#ifndef _CONTORLADOR_DISPLAY_H
#define _CONTORLADOR_DISPLAY_H

#include <xc.h>         /* Archivo de Encabezados General XC8 */
#include <stdint.h>     /* para las definiciones de uint8_t por ej.*/


/* Definimos el tamano del display */
//#define DOT_X_ALTO      320
//#define DOT_X_ANCHO  240

#define LCD_W 320
#define LCD_H 480
/* estan para cuando se usa la orientacion que retorne el anchoy el alto segun como se este graficando*/
#define GET_LCD_ALTO()    ( LCD_H)
#define GET_LCD_ANCHO()   ( LCD_W )

// IO connection

// difinimos el tipo  y numero de bits de datos para el buss de datos.
//#define BUSS_SPI
//#define BUSS_16
#undef BUSS_16

/* LCD screen and bitmap image array consants */
#define X_BYTES               30
#define Y_BYTES               64
#define SCRN_LEFT          0
#define SCRN_TOP            0
#define SCRN_RIGHT        239
#define SCRN_BOTTOM   63

/* LCD Global data arrays */
//extern const unsigned char code l_mask_array[8];
//extern unsigned char xdata l_display_array[Y_BYTES][X_BYTES];
// debe estar dentro del manejador del dispositivo.
extern const unsigned char l_mask_array[8];
extern unsigned char l_display_array[Y_BYTES][X_BYTES];

#if 0
#ifdef BUSS_16
	typedef enum {D0=0,	D1,	D2,	D3,	D4,	D5,	D6,	D7, D8,	D9,	D10, D11, D12, D13,	D14, D15, NUMERO_BITS = 16 }
#else
	typedef enum {D0=0,	D1,	D2,	D3,	D4,	D5,	D6,	D7, NUMERO_BITS = 8  }
#endif
	eTFTDATAConfigPINS;


typedef enum{RS, WR, RD, CS, RES, LINEAS_CONTROL= 5} eTFTCONTROLConfigPINS;
/*
* estructura TFT_Config
*	Esta estructura es usada para ordenar la configuracion de pines a utilizar en el control del display.
*/
typedef struct
{
  int PinDataBuss[NUMERO_BITS];
  int PinsControl[LINEAS_CONTROL];
}TFT_Config;

#endif
/*
typedef enum
{
  ORIENTATION_LANDSCAPE,
  ORIENTATION_PORTRAIT,
  ORIENTATION_PORTRAIT_1,
  ORIENTATION_PORTRAIT_2,
  ORIENTATION_LANDSCAPE_1,
  ORIENTATION_LANDSCAPE_2
} eOrientacion;
*/
typedef enum{HORIZONTAL,   //ORIENTATION_LANDSCAPE
             VERTICAL,     //ORIENTATION_PORTRAIT
             VERTICAL_1,   // ORIENTATION_PORTRAIT_1,
             VERTICAL_2,   // ORIENTATION_PORTRAIT_2,
             HORIZONTAL_1, // ORIENTATION_LANDSCAPE_1,
             HORIZONTAL_2  // ORIENTATION_LANDSCAPE_2
}eOrientacion;
/*
 *  Descriptos del dispositivo, en este caso display grafico.
 *
 * */
typedef struct
{
  int Alto;   /* cantidad de puntos fila que lleva el display*/
  int Ancho;/* Cantidad de puntos columna que lleva el display*/
  int FilaActual;
  int columnaActual;
  int Orientacion;
  //ColaCircular buffer;    // Encola los comandos y datos a ser enviados al display solo para un lcd de texto.
//  Buss busDatos;
//  GPIO RS;
//  GPIO EN;
//  BUS busCtr;
//  GPIO busCtr[NUMERO_BITS];

} Ctr_GDisplay;


typedef Ctr_GDisplay* HGlcd;




/*        Definicion de alias para las lineas fisicas
 * no estoy seguro que es mas conveniente ya que la idea era poder manejar difertentes display
 * que se conectaran y desconectaran en tiempo real peor requiere bastante memoria para la gestion y la inicializacion
 * necesita una sincronizacion que no es muy transparente en para RTOS, y ademas ahumenta el OVERHEAD.
 *
 * */
/*   GPIO__2_12 =   GPIO__#puerto_#pin  */
/*
#define CE  GPIO__2_2    // P2.2  7  CE     = P3^0;          port bit for Chip Select
#define CD  GPIO__2_3    // P2.3  8  CD     = P3^1;          port bit for Control/Data Select
#define WR  GPIO__2_0    // P2.0  5  wr     = P3^2;          port bit for the Write Strobe
#define RD  GPIO__2_1    // P2.1  6  RD     = P3^3;          port bit for the Read Strobe
#define RST GPIO__0_11   // P0.11 10  RESET = P3^4;         port bit for Display Reset
#define FS  GPIO__0_10   // P0.10 19  FS= P3^5;          port bit for Font Select

#define D0  GPIO__2_4  // p2.4   11  D0 Agregar primero el menos significativo!
#define D1  GPIO__2_5  // P2.5   12  D1
#define D2  GPIO__2_6  // P2.6   13  D2
#define D3  GPIO__2_7  // P2.7   14  D3
#define D4  GPIO__2_8  // P2.8   15  D4
#define D5  GPIO__2_10 // P2.10  16  D5
#define D6  GPIO__2_11 // P2.11  17  D6
#define D7  GPIO__2_12 // P2.12  18  D7
*/



#endif
