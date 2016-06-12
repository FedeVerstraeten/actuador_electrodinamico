# README #

Repositorio dedicado al proyecto de Laboratorio de Microprocesadores.

## Links Importantes ##

* Google Drive
https://drive.google.com/folderview?id=0B8r41_q91dvmSWJHaV9veFA4RlU&usp=sharing

* Overleaf Informe
https://www.overleaf.com/4727217zqyjxb

* Overleaf Poster
https://www.overleaf.com/5136789npntdk

* Repositorio Includes ATMEL
https://github.com/DarkSector/AVR/tree/master/asm/include

## Links e Info de Interés ##

* Proyecto Espectrofotocolorímetro (para ver cómo manejan el display)
https://github.com/cristiandouce/ProyectoEFC

* Compilar código C y Assembly con la consola
http://goo.gl/7QhFGv

* Comandos para compilar código en Assembler
```
#!bash
avra <nombre.s> -o <nombre.hex>
avrdude -c usbtiny -p m328p -U flash:w:<nombre.hex>
```
Nota: es necesario instalar el programa *avra* e incluir las definiciones para el microcontrolador atmega328p usando la directiva *include* ya que *avra* no tiene la opción *mmcu* como si la tiene *avr-gcc*.

* Comandos para compilar código en C
```
#!bash
avr-gcc -mmcu=atmega328p <nombre.c> -o <nombre.elf>
avr-objcopy -j .text -j .data -O ihex <nombre.elf> <nombre.hex>
avrdude -c usbtiny -p m328p -U flash:w:<nombre.hex>
```
# Utilización de 28 pines integrado Atmega328P

Elemento      | Cant. pines
------------- | -------------
VCC           | 1
GND           | 2
Parlante (DAC)| 8
Display       | 7(11)
Pulsadores    | 3
Matlab (Tx+Rx)| 2
Fotodiodo(ADC)| 1 ?
Corte señal - Int.Externa | 1
Cristal       | 2
Total         | 27 utilizados

# Microcontrolador de 40 pines (4 puertos de 8bits + pines Tx/Rx y XTAL por separado)

* ATmega164P/V-ATmega324P/V-ATmega644P/V
http://www.atmel.com/images/atmel-8011-8-bit-avr-microcontroller-atmega164p-324p-644p_summary.pdf