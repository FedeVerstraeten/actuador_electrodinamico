;; Este programa es una prueba para ver como funciona
;; la comunicacion serie. Basicamente el programa
;; espera a que llegue un dato. Cuando esto sucede guarda
;; el dato en un registro, cambia el estado (ON o OFF) del
;; Puerto C y transmite el valor recibido tal cual esta

#INCLUDE "m328Pdef.inc"

;; Defino algunas variables auxiliares
.DEF temp = R16
.DEF recieved_byte = R17
.DEF ledstate = R18

;; Defino parametros del baud rate
.EQU CLOCK = 16000000
.EQU BAUD = 9600
.EQU UBRRVAL = ( CLOCK / ( BAUD * 16 ) ) - 1

.ORG 0x00

;; Inicializo Stack Pointer correctamente
LDI R16, LOW(RAMEND)
OUT SPL, temp
LDI R16, HIGH(RAMEND)
OUT SPH, temp

JMP MAIN

.ORG 0x0040

MAIN:
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

	;; Configuro al puerto C como salida
	LDI temp, 0xFF
	OUT DDRC, temp

	;; Inicializo al puerto C
	LDI ledstate, 0xFF
	OUT PORTC, ledstate

;; Loop principal
AGAIN:
	CALL READMODE
	CALL SWITCHLED
	CALL WRITEMODE
	RJMP AGAIN

READMODE:
	;; Espero a que este listo para leer
	LDS temp, UCSR0A
	SBRS temp, RXC0
	RJMP READMODE
	;; Cargo el byte recibido
	LDS recieved_byte, UDR0
	RET

WRITEMODE:
	;; Espero a que este listo para escribir
	LDS temp, UCSR0A
	SBRS temp, UDRE0
	RJMP WRITEMODE
	;; Envio el byte recibido anteriormente
	STS UDR0, recieved_byte
	RET

SWITCHLED:
	;; Obtengo el complemento del estado actual del led
	COM ledstate
	;; Defino el nuevo valor del puerto C
	OUT PORTC, ledstate
	RET
