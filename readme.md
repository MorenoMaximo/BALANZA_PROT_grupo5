# Balanza Medidora de Suero para PIC16F887
Para trabajar con el compilador XC8(v2.40) con MPLABX IDE v6.20

## Versi�n Actual: 0.3.2 :floppy_disk:

## M�dulos disponibles :computer: 
Nombre|Descripcion
------|-----------
`uart`|Permite el manejo del Puerto Serie
`hx711`|Funcionamiento del accionar del conversor AD, sumado a algunas funciones
`tick`|Permite utilizar el contador de Tick para temporizaciones

## Datos del grupo :busts_in_silhouette:
Campo|Detalle
-----|-------
Alumnos|M�ximo Moreno, Mauricio Solis,<br>Valentino Falcinelli, Leandro Rojas,<br>Joaqu�n Ruiz Aranda
Curso|6�Electr�nica
A�o|2025

# Notas de Versionado :clipboard:
***Recuerda*** **adici�n o cambio**(en negro :black_large_square:), **cambio temporal**(en azul :blue_square:) y **eliminaci�n**(en rojo :red_square:)

v0.1 	- Prototipo de prueba de Balanza
- :black_large_square: Prueba las funcionalidades de la celda de carga con el HX711
- :black_large_square: Pines asignados al programador

v0.2    - Agregamos el ENCODER
- :black_large_square: Agrega la MEF del encoder, juntos a sus pines correspondientes
- :black_large_square: Pines asignados a la plaqueta definitiva
- :blue_square: Temporalmente dejamos comentado el c�digo de de la celda de carga
- :red_square: Sacamos los pines de las teclas y leds que no corresponden a la plaqueta final ya que no existen

v0.3    - Tecla del ENCODER
- :black_large_square: Agrega la libreria tick.h junto a tick.c para utilizar el Timer0 y contadores con el mismo
- :black_large_square: Agrega otra MEF para el ENCODER, correspondiente a la tecla del mismo

v0.3.1  - Optimizaci�n
- :red_square: Elimina algunos pines innecesarios que hab�an quedado

v0.3.2  - Medici�n del tiempo de muestreo
- :black_large_square: Se finaliz� la M�quina de estados de la tecla, corrigiendo unos errores
- :red_square: Eliminamos el c�digo de calibraci�n ya que qued� obsoleto (aunque puede usarse parte de el mismo a futuro)
- :blue_square: Implementamos un segmento de c�digo que mide el tiempo que demora en hacerse una muestra de la celda de carga a trav�s del HX711