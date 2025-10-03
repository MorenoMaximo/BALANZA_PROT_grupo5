/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/
/** @file
 * @brief	Contiene macros y definiciones de user
 * 
 * Aquí se configura la funcion del conversor A/D HX711
 */
#ifndef HX711_H
#define HX711_H

/*==================[declaraciones de constantes]=============================*/
#define START_UP_DELAY  100
#define CHECKSUM_MASK   0x800000
#define CANT_PROMEDIO   10

/*==================[declaraciones de funciones externas]====================*/
unsigned long HX711Read(void);      //Lectura del HX711
unsigned long TaraSet(void);        //Ajuste de la Tara
unsigned long HX711Promedio(void);  //Lectura con promedio
unsigned long LecturaPeso(void);    //Tomar una muestra del HX711
/*==================[fin del archivo]========================================*/
#endif// HX711_H