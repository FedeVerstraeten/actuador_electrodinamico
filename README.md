# README #

Repositorio dedicado al proyecto de Laboratorio de Microprocesadores.

## Links Importantes ##

* Google Drive
https://drive.google.com/folderview?id=0B8r41_q91dvmSWJHaV9veFA4RlU&usp=sharing

* Overleaf
https://www.overleaf.com/4727217zqyjxb

## Links e Info de Interés ##

* Compilar código C y Assembly con la consola
http://goo.gl/7QhFGv

* Comandos útiles de Fede para compilar código Assembler

```
#!bash
avr-gcc -mmcu=atmega88 <nombre.c> -o <nombre.elf>
avr-objcopy -j .text -j .data -O ihex <nombre.elf> <nombre.hex>
avrdude -c usbtiny -p m88 -U flash:w:<nombre.hex>
```