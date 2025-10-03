# Balanza Medidora de Suero para PIC16F887
Para trabajar con el compilador XC8(v2.40) con MPLABX IDE v6.20

##Versi�n Actual: 0.2
## M�dulos disponibles
Nombre|Descripcion
------|-----------
`uart`|Permite el manejo del Puerto Serie
`hx711`|Funcionamiento del accionar del conversor AD, sumado a algunas funciones

## Datos del grupo
Campo|Detalle
-----|-------
Alumno|M�ximo Moreno
Alumno|Mauricio Solis
Alumno|Valentino Falcinelli
Alumno|Joaqu�n Ruiz Aranda
Alumno|Leandro Rojas
Curso|6�Electr�nica
A�o|2025

# Notas de Versionado
***Recuerda*** **adici�n o cambio**(en negro :black_large_square:), **cambio temporal**(en azul :blue_square:) y **eliminaci�n**(en rojo :red_square:)

v0.1 	- Prototipo de prueba de Balanza
:black_large_square: Prueba las funcionalidades de la celda de carga con el HX711
:black_large_square: Pines asignados al programador

v0.2    - Agregamos el ENCODER
:black_large_square: Agrega la MEF del encoder, juntos a sus pines correspondientes
:black_large_square: Pines asignados a la plaqueta definitiva
:blue_square: Temporalmente dejamos comentado el c�digo de de la celda de carga
:red_square: Sacamos los pines de las teclas y leds que no corresponden a la plaqueta final ya que no existen
