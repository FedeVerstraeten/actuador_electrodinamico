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

* Microcontrolador ATmega164P/V-ATmega324P/V-ATmega644P/V (40 pines: 4 puertos de 8bits + pines Tx/Rx y XTAL por separado)
[Link Datasheet](http://www.atmel.com/images/atmel-8011-8-bit-avr-microcontroller-atmega164p-324p-644p_datasheet.pdf)

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
# Utilización de 28 pines integrado Atmega324P

Elemento      | Cant. pines   | Puerto asignado  |
------------- | ------------- | ---------------- |
VCC           | 1             | VCC              |
GND           | 2             | GND              |
Parlante (DAC)| 8             | PB0 a PB7        |
Display       | 7(11)         | PC0 a PC6        |
Pulsadores    | 3             | PD3, PD4 y PD5   |
Matlab (Tx+Rx)| 2             | PD0 y PD1        |
Fotodiodo(ADC)| 1 ?           | ADC0             |
Corte señal - Int.Externa | 1 | PD2/INT0         |
Cristal       | 2             | XTAL1 y XTAL2    |
Total         | 27 utilizados | -                |
