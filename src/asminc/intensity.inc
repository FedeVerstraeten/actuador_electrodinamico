;******************************************************************
; Materia......: Laboratorio de Microprocesadores.
; Curso........: Campigglio - Stola
; Fecha inicio.: 14/03/2016
; Fecha entrega: 21/06/2016
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
;       INTENSITY
;******************************************************************
; Rutinas que utilizan el ADC del microcontrolador para realizar
; la medición de intensidad lumínica.
;******************************************************************

;******************************************************************
; CONSTANTES
;******************************************************************

        .equ    ADC_PIN         =       0 ; Pin del ADC_PORT correspondiente a la entrada
        .equ    ADC_DDR         =       DDRA
        .equ    ADC_PORT        =       PORTA

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
        ; MUX2:MUX0   - ADC_PIN select
        ret


;******************************************************************
; intensity_start, intensity_loop: Rutina que va leyendo
; indefinidamente el valor analógico de tensión que se encuentra
; en el pin ADC_PIN y lo tranforma en un valor digital. Luego se
; muestra el valor medido en el display.
;******************************************************************
intensity_start:
        ; Limpiamos la pantalla del display y
        ; mostramos en la primera linea
        ; el string strIntnstyMed
        SetLCDClearAtHome
        ldi 	zh, high(strIntnstyMed << 1)
	ldi 	zl, low(strIntnstyMed << 1)
        rcall   lcd_putstring

        ldi     tmp, 0b00000000                 ; Seteo los pines del puerto
        out     ADC_DDR, tmp                    ; A como entrada
        ; Leer ADC
        ldi     tmp, (1<<REFS0) | ADC_PIN       ; Seteo channel
        out     ADMUX, tmp
        sbi     ADCSRA, ADSC                    ; Empiezo conversion

intensity_loop:
        rcall   delay_200ms

        ; Posicionamos el cursor al principio de la segunda línea
        ; del display, de esa manera se sobreescriben los valores
        ; de la medición anterior
        SecondLine


wait_for_conv_finished:
        ; El bit ADSC se pone en bajo luego de terminar la conversión
        sbic    ADCSRA, ADSC
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
	rcall	bin_to_asc
        ; Volvemos al inicio de Z
	ldi     Zh, high(buffer)
	ldi 	Zl, low(buffer)
        ; Mostramos los caracteres en el display
        rcall   lcd_send_ascii
        ; Volvemos a leer datos del ADC
        rjmp    intensity_loop
