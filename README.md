# README (en serio leeme, no seas pavote) #

Repositorio dedicado al proyecto de Laboratorio de Microprocesadores.

## Links Importantes ##

* Google Drive
https://drive.google.com/folderview?id=0B8r41_q91dvmSWJHaV9veFA4RlU&usp=sharing

* Overleaf
https://www.overleaf.com/4727217zqyjxb

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