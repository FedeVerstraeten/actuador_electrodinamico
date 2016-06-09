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
;	Rutinas correspondientes a la comunicación USART
;******************************************************************

;*****************************************************************
; CONSTANTES
;*****************************************************************
        .equ    USART_CLOCK     =       16000000
        .equ    USART_BAUD      =       9600
        .equ    USART_UBRR      =       ( CLOCK / ( BAUD * 16 ) ) - 1

;******************************************************************
; USART_Init: Inicialización de la comunicación. En esta rutina
; se configuran los distintos parámetros.
;******************************************************************
USART_Init:
	;; Habilito comunicacion serie de entrada y salida
	LDI temp, (1<<TXEN0) | (1<<RXEN0)
	STS UCSR0B, temp

	;; Configuro que el tipo de comunicacion será de 8 bits
	;; de datos y 1 stop bit, sin paridad
	LDI temp, (1<<UCSZ01) | (1<<UCSZ00)
	STS UCSR0C, temp

	;; Cargo el baud en el registro correspondiente
	;; (Puede ser un numero alto por lo que ocupa
	;;  dos bytes, por eso hay partes High y Low)
	LDI temp, HIGH(UBRRVAL)
	STS UBRR0H, temp
	LDI temp, LOW(UBRRVAL)
	STS UBRR0L, temp

;******************************************************************
; USART_Transmit: Envía un byte utilizando comunicación serie.
;******************************************************************
USART_Transmit:
        push tmp
        ;; Espero a que este listo para leer
transmit_loop:
        lds tmp, UCSR0A
        sbrs tmp, UDRE0
        RJMP transmit_loop
        ;; Almacenamos el byte recibido
        sts UDR0, arg
        pop tmp
        ret

;******************************************************************
; USART_Receive: Recibe un byte utilizando comunicación serie.
;******************************************************************
USART_Receive:
        push tmp
        ;; Espero a que este listo para leer
recieve_loop:
        lds tmp, UCSR0A
        sbrs tmp, RXC0
        RJMP recieve_loop
        ;; Almacenamos el byte recibido
        sts arg, UDR0
        pop tmp
        ret
