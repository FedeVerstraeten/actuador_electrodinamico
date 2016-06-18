;******************************************************************
; Materia......: Laboratorio de Microprocesadores.
; Curso........: Campigglio - Stola
; Fecha inicio.: 14/03/2016
; Fecha entrega: 20/06/2016
; Autores......:
;		 Ezequiel Martín Zarza
;		 Santiago Roman
;		 Federico Verstraeten
;
; Contacto.....:
;		 ezequielm.zarza@gmail.com
;		 santiago_roman@outlook.com
;		 federico.verstraeten@gmail.com
;
;******************************************************************
;       MATLAB
;******************************************************************
; Rutinas utilizadas para definir cómo se realiza la comunicación
; con matlab a la hora de ir pasando muestras de una función.
;******************************************************************

;******************************************************************
; CONSTANTES
;******************************************************************

        .equ    DAC_PIN         =       0 ; Pin del DAC_PORT correspondiente a la entrada
        .equ    DAC_DDR         =       DDRA
        .equ    DAC_PORT        =       PORTA

;******************************************************************
; intensity_init: Inicializa el ADC.
;******************************************************************

intensity_init:
        ldi     tmp, (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)
        out     ADCSR, tmp
        ; ADEN  es ADC enable
        ; ADPSx es prescaler
        ; ADSC  es empezar conversion

        ldi     tmp, (1<<REFS0) ; Referencia = AVCC (=VCC)
        out     ADMUX, tmp
        ; REFS1:REFS0 - reference voltage (segun micro)
        ; MUX2:MUX0   - DAC_PIN select
        ret


;******************************************************************
; intensity_loop: Rutina que va leyendo indefinidamente el
; valor analógico de tensión que se encuentra en el pin ADC_PIN
; y lo tranforma en un valor digital. Luego se muestra el valor
; medido en el display.
;******************************************************************
intensity_start:
        SetLCDClearAtHome
        ldi 	zh, high(strIntnstyMed << 1)
	ldi 	zl, low(strIntnstyMed << 1)
        rcall   lcd_putstring


intensity_loop:
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms
        rcall   wait5ms

        SecondLine

        ldi     tmp, 0b00000000 ; Seteo los pines del puerto
        out     DAC_DDR, tmp       ; A como entrada

        ; Leer ADC
        ldi     tmp, (1<<REFS0) | DAC_PIN ; Seteo channel
        out     ADMUX, tmp
        sbi     ADCSRA, ADSC              ; Empiezo conversion

wait_for_conv_finished:
        sbic    ADCSRA, ADSC  ; El bit ADSC se pone en bajo luego de terminar la conversion
        rjmp    wait_for_conv_finished

        ; Cargamos la parte baja y alta del valor medido
        in      rBin1L, ADCL
        in      rBin1H, ADCH

        ; Posicionamos Z en la variable buffer
	ldi     Zh, high(buffer)
	ldi 	Zl, low(buffer)
        ; Convertimos el valor medido que se encuentra
        ; en las variables rBin1L y rBin1H en 5
        ; caracteres ASCII, los cuales se guardan
        ; en el puntero Z
	rcall	Bin2ToAsc

        ; Volvemos al inicio de Z
	ldi     Zh, high(buffer)
	ldi 	Zl, low(buffer)
        ; tmp3 es el indice
	ldi     tmp3, 5
        ; Vamos almacenando caracter a caracter en arg
	ld	arg, Z+
lcd_send_ascii:
        LcdPutChar
	ld	arg, Z+
	dec     tmp3
	cpi     tmp3, 0
	brne    lcd_send_ascii

        rjmp    intensity_loop
