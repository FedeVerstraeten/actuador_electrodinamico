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
;	USART
;******************************************************************
; Rutinas correspondientes a la comunicación serie USART.
;******************************************************************

;*****************************************************************
; CONSTANTES
;*****************************************************************
        .equ    USART_CLOCK     =       16000000
        .equ    USART_BAUD      =       9600
        .equ    USART_UBRR      =       ( USART_CLOCK / ( USART_BAUD * 16 ) ) - 1

;******************************************************************
; usart_init: Inicialización de la comunicación. En esta rutina
; se configuran los distintos parámetros.
;******************************************************************
usart_init:
	;; Habilito comunicacion serie de entrada y salida
	ldi     tmp, (1<<TXEN0) | (1<<RXEN0)
	sts     UCSR0B, tmp

	;; Configuro que el tipo de comunicacion será de 8 bits
	;; de datos y 1 stop bit, sin paridad
	ldi     tmp, (1<<UCSZ01) | (1<<UCSZ00)
	sts     UCSR0C, tmp

	;; Cargo el baud en el registro correspondiente
	;; (Puede ser un numero alto por lo que ocupa
	;;  dos bytes, por eso hay partes High y Low)
	ldi     tmp, HIGH(USART_UBRR)
	sts     UBRR0H, tmp
	ldi     tmp, LOW(USART_UBRR)
	sts     UBRR0L, tmp

;******************************************************************
; usart_transmit: Envía un byte utilizando comunicación serie.
;******************************************************************
usart_transmit:
        push    tmp
        ;; Espero a que este listo para leer
transmit_loop:
        lds     tmp, UCSR0A
        sbrs    tmp, UDRE0
        rjmp    transmit_loop
        ;; Almacenamos el byte recibido
        sts     UDR0, arg
        pop     tmp
        ret

;******************************************************************
; usart_recieve: Recibe un byte utilizando comunicación serie.
;******************************************************************
usart_recieve:
        push     tmp
        ;; Espero a que este listo para leer
recieve_loop:
        lds     tmp, UCSR0A
        sbrs    tmp, RXC0
        rjmp    recieve_loop
        ;; Almacenamos el byte recibido
        lds     rtn, UDR0
        pop     tmp
        ret
