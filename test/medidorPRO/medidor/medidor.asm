/*
 * medidor.asm
 *
 *  Created: 14/06/2016 02:27:11 p.m.
 *   Author: Eze
 */ 


 ;inicializo ADC

   ldi  r16, (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)
   out  ADCSR, r16
; ADEN  es ADC enable
; ADPSx es prescaler
; ADSC  es empezar conversion

   ldi  r16, (1<<REFS0) ;referencia = AVCC (=VCC)
   out  ADMUX, r16
; REFS1:REFS0 - reference voltage (segun micro)
; MUX2:MUX0   - channel select

;----------------------------------------------------------

mainloop:
.equ channel = 0 // ADC0
ldi r16,0b11110000
out DDRD,r16

;leer adc
   ldi  r16, (1<<REFS0) | channel ; seteo channel
   out  ADMUX, r16
   sbi  ADCSRA, ADSC              ; empiezo conversion

wait_for_conv_finished:
   sbic ADCSRA, ADSC  ;bit ADSC se pone en bajo luego de terminar la conversion       
   rjmp wait_for_conv_finished

   in   r1, ADCL
   in   r2, ADCH

rjmp mainloop