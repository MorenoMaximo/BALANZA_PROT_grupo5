# Balanza Medidora de Suero para PIC16F887
Para trabajar con el compilador XC8(v2.40) con MPLABX IDE v6.20

## Versión Actual: 0.2 :floppy_disk:

## Módulos disponibles :computer: 
Nombre|Descripcion
------|-----------
`uart`|Permite el manejo del Puerto Serie
`hx711`|Funcionamiento del accionar del conversor AD, sumado a algunas funciones

## Datos del grupo :busts_in_silhouette:
Campo|Detalle
-----|-------
Alumnos|Máximo Moreno, Mauricio Solis, 
       |Valentino Falcinelli, Joaquín Ruiz Aranda y Leandro Rojas
Curso|6ºElectrónica
Año|2025

# Notas de Versionado :clipboard:
***Recuerda*** **adición o cambio**(en negro :black_large_square:), **cambio temporal**(en azul :blue_square:) y **eliminación**(en rojo :red_square:)

v0.1 	- Prototipo de prueba de Balanza
- :black_large_square: Prueba las funcionalidades de la celda de carga con el HX711
- :black_large_square: Pines asignados al programador

v0.2    - Agregamos el ENCODER
- :black_large_square: Agrega la MEF del encoder, juntos a sus pines correspondientes
- :black_large_square: Pines asignados a la plaqueta definitiva
- :blue_square: Temporalmente dejamos comentado el código de de la celda de carga
- :red_square: Sacamos los pines de las teclas y leds que no corresponden a la plaqueta final ya que no existen
