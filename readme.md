# Balanza Medidora de Suero para PIC16F887
Para trabajar con el compilador XC8(v2.40) con MPLABX IDE v6.20

## Versión Actual: 0.5.1 :floppy_disk:

## Módulos disponibles :computer: 
Nombre|Descripcion
------|-----------
`uart`|Permite el manejo del Puerto Serie
`hx711`|Funcionamiento del accionar del conversor AD, sumado a algunas funciones
`tick`|Permite utilizar el contador de Tick para temporizaciones
`encoder`|Utilidades del Encoder, su rotación y botón
`TFT_ILI9486`|Libreria de control de la pantalla
`GLCD_Draw`|Funciones de dibujo para líneas, círculos y cuadrados
`GLCD_Text`|Funciones de escritura de letras y números


## Datos del grupo :busts_in_silhouette:
Campo|Detalle
-----|-------
Alumnos|Máximo Moreno, Mauricio Solis,<br>Valentino Falcinelli, Leandro Rojas,<br>Joaquín Ruiz Aranda
Curso|6ºElectrónica
Año|2025

# Notas de Versionado :clipboard:
***Recuerda*** **adición o cambio**(en verde :green_square:), **cambio temporal o incompleto**(en azul :blue_square:) y **eliminación**(en rojo :red_square:)

v0.1 	- Prototipo de prueba de Balanza
- :green_square: Prueba las funcionalidades de la celda de carga con el **HX711**
- :green_square: Pines asignados al programador

v0.2    - Agregamos el ENCODER
- :green_square: Agrega la _MEF_ del **ENCODER**, juntos a sus pines correspondientes
- :green_square: Pines asignados a la plaqueta definitiva
- :blue_square: Temporalmente dejamos comentado el código de de la celda de carga
- :red_square: Sacamos los pines de las teclas y leds que no corresponden a la plaqueta final ya que no existen

v0.3    - Tecla del ENCODER
- :green_square: Agrega la libreria `tick.h` junto a `tick.c` para utilizar el _Timer0_ y contadores con el mismo
- :green_square: Agrega otra _MEF_ para el **ENCODER**, correspondiente a la tecla del mismo

v0.3.1  - Optimización
- :red_square: Elimina algunos pines innecesarios que habían quedado

v0.3.2  - Medición del tiempo de muestreo
- :green_square: Se finalizó la Máquina de estados de la tecla, corrigiendo unos errores
- :red_square: Eliminamos el código de calibración ya que quedó obsoleto (aunque puede usarse parte de el mismo a futuro)
- :blue_square: Implementamos un segmento de código que mide el tiempo que demora en hacerse una muestra de la celda de carga a través del **HX711**

v0.4    - Librería del ENCODER
- :green_square: Se agregaron las librerias `encoder.h` y `encoder.c` con las _MEF_ del **ENCODER** para organizar de manera modular y ordenar el `main.c`

v0.5    - Inclusión de la pantalla (ILI9486)
- :green_square: Se agregaron las librerías `TFT_ILI9486`, `GLCD_Draw` y `GLCD_Text` para la configuración principal de la **PANTALLA**
- :blue_square: Se agregó la función *ejemplo()* para probar todas las funcionalidades de la **PANTALLA**, en versiones futuras se haran correcciones basadas al funcionamiento de esta

v0.5.1  - Correcciones
- :green_square: Se arreglaron los "tags" de los colores
- :green_square: Se corrigió la rotación de la **PANTALLA** y su resolución

v0.6    - Escritura de texto
- :green_square: Se corrigieron las funciones `ILI9486_DrawText`, `ILI9486_DrawChar` y `ILI9486_DrawNumber` con el fin de escribir en la **PANTALLA** correctamente
- :blue_square: Se realizaron exhaustivas pruebas con relación a la escritura en el hardware

v0.7    - Prototipo de diseño final
- :green_square: Corrección de las funciones de escritura para escribir exclusivamente en rotación Landscape (en un futuro se podrá escribir en todas las horientaciones)
- :blue_square: Implementación de la función `DrawTemplate()` para escribir el diseño prematuro del proyecto

v0.7.1  - Diseño prototipo terminado
- :green_square: Se terminó la función `DrawTemplate()`
- :blue_square: Esta versión sirve de backup a fin de empezar a optimizar la escritura del driver **ILI9486 (PANTALLA)**
