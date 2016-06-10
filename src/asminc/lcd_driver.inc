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
;     LCD_DRIVER
;******************************************************************
; Rutinas utilizadas para manejar el display LCD.
;******************************************************************

;*****************************************************************
; TODO: CHEQUEAR QUE LOS PUERTOS COINCIDAN A LA HORA DE IMPLEMENTAR
; En este caso parece que los bits 4-7 estan conectados a D4-D7
; del display mientras que LCD_RS es el pin 1 de *PORTC*, LCD_RW
; es el pin 2 de PORTD y LCD_E es el pin 3 de PORTD.
;*****************************************************************


;*****************************************************************
; CONSTANTES
;*****************************************************************
        .equ    LCD_CTRL_PORT   =       PORTD ; Definimos el puerto (escritura)
        .equ    LCD_CTRL_PIN    =       PinD  ; y el pin (lectura) al que estan
        .equ    LCD_CTRL_DDR    =       DDRD  ; conectados los pines de control del display

	.equ	LCD_RS	        =       1 ; Estos corresponden al numero del pin
	.equ	LCD_RW	        =       2 ; del micro al que esta conectado los
	.equ	LCD_E	        =       3 ; pines RS, RW y E del display

        .equ    LCD_CLEAR       =       0x01 ; Limpiar la pantalla
        .equ    LCD_CURSOR_HOME =       0x02 ; LLevar al cursor a home
        .equ    LCD_INC_C       =       0x06 ; Incrementar cursor hacia la derecha
        .equ    LCD_D_ON_C_OFF  =       0x0C ; Display encendido, sin cursor
        .equ    LCD_4_BIT       =       0x20 ; Modo de 4 bit. (Ver http://www.avrbeginners.net/interfacing/44780_lcd/4bit.html)
        .equ    LCD_2_LINE      =       0x28 ; Usar dos lineas, matriz 5x7, modo de 4 bit
        .equ    LCD_CURSOR_2LINE =      0xC0 ; Forzar al cursor hacia el inicio de la 2da línea

;*****************************************************************
; lcd_init: Inicialización del display. Aca se encuentra la
; configuración de los distintos parámetros necesarios para su
; correcto funcionamiento.
;*****************************************************************
lcd_init:
        sbi     LCD_CTRL_DDR, LCD_RS    ; Configuramos a los pines IO del micro
	sbi     LCD_CTRL_DDR, LCD_RW    ; conectados a los pines RS, RW y E del
	sbi     LCD_CTRL_DDR, LCD_E     ; display como salida
	rcall   delay200ms              ; Es necesario esperar un poco para continuar trabajando

	ldi     arg, LCD_4_BIT          ; Utilizamos el modo de trabajo de 4-bit
	rcall   lcd_send_cmd_8b         ; Todavia estamos en modo de 8 bit asi que usamos esa rutina
	rcall   lcd_wait

	ldi     arg, LCD_2_LINE         ; Seteamos 2 lineas y matriz de 5x7
	rcall   lcd_send_cmd_4b
	rcall   lcd_wait

	ldi     arg, LCD_D_ON_C_OFF     ; Setamos el display encendido, sin cursor
	rcall   lcd_send_cmd_4b
	rcall   lcd_wait

	ldi     arg, LCD_CLEAR          ; Limpiamos el display
	rcall   lcd_send_cmd_4b
	rcall   lcd_wait

	ldi     arg, LCD_INC_C          ; Seteamos el cursor en autoincremento
	rcall   lcd_send_cmd_4b
	rcall   lcd_wait
	ret

;*****************************************************************
; lcd_send_cmd_8b: Comandos necesarios para pasar al LCD a modo
; de trabajo de 4 bit. Esta rutina solamente es utilizada
; al inicializar el display.
;*****************************************************************
lcd_send_cmd_8b:
        in	tmp, LCD_CTRL_DDR       ; Obtenemos estado actual del DDR
	sbr	tmp, 0b11110000         ; Solamente queremos el high nibble como salida
	out	LCD_CTRL_DDR, tmp       ; Actualizamos el DDR
	in	tmp, LCD_CTRL_PORT      ; Obtenemos datos del puerto
	cbr	tmp, 0b11110000         ; Borramos la parte de los bits de datos
	cbr	arg, 0b00001111         ; Nos quedamos solamente con los bits de datos
	or	tmp, arg                ; Guardamos el comando que vamos a enviar en tmp
	out	LCD_CTRL_PORT, tmp      ; Envio el comando al display
	sbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 1
	nop                             ; Esperamos a que el
	nop                             ; pulso tenga el ancho
	nop                             ; necesario
	cbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 0 (termina el pulso)
	in	tmp, LCD_CTRL_DDR       ; Seteamos los bits de datos nuevamente
	cbr	tmp, 0b11110000         ; como entrada
	out	LCD_CTRL_DDR, tmp       ; Actualizamos el DDR
	ret

;*****************************************************************
; lcd_putchar: Envía un caracter para que muestre el display.
; Utiliza el modo de trabajo de 4 bit.
;*****************************************************************
lcd_putchar:
	push 	arg 			; Guardamos el argumento ya que lo vamos a modificar
	in	tmp, LCD_CTRL_DDR	; Obtenemos el valor del DDR
	sbr	tmp, 0b11110000		; Seteamos bits de datos como salida
	out	LCD_CTRL_DDR, tmp       ; Actualizamos el DDR
	in	tmp, LCD_CTRL_PORT	; Obtenemos los datos del puerto
	cbr	tmp, 0b11111110         ; Borramos los datos que no usamos
	cbr	arg, 0b00001111		; Solamente queremos los bits de datos del argumento
	or	tmp, arg		; Guardamos los datos en tmp
	out	LCD_CTRL_PORT, tmp	; Enviamos los datos por el puerto
	sbi	LCD_CTRL_PORT, LCD_RS	; Seteamos RS en 1 para habilitar el envio de datos
	sbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 1
	nop
	nop
	nop
	cbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 0 (termina el pulso)
	pop	arg			; Recuperamos el valor original del argumento
	cbr	tmp, 0b11110000		; Hacemos lo mismo que antes, con la diferencia
	swap	arg			; de que ahora nos queremos quedar con el low
	cbr	arg, 0b00001111		; nibble del argumento (i.e., el caracter)
	or	tmp, arg                ; Guardamos los datos en tmp
	out	LCD_CTRL_PORT, tmp      ; Enviamos los datos por el puerto
	sbi	LCD_CTRL_PORT, LCD_RS	; Seteamos RS en 1 para habilitar el envio de datos
	sbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 1
	nop
	nop
	nop
	cbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 0 (termina el pulso)
	cbi	LCD_CTRL_PORT, LCD_RS   ; Seteamos RS en 0
	in	tmp, LCD_CTRL_DDR       ; Obtenemos el valor del DDR
	cbr	tmp, 0b11110000		; Seteamos los bits de datos como entrada
	out	LCD_CTRL_DDR, tmp       ; Actualizamos el DDR
	ret

;*****************************************************************
; lcd_cmd_4b: Envia un comando al LCD, para lo cual necesita
; RS = 0. Es practicamente lo mismo que lcd_putchar pero para enviar
; comandos en vez de información que se debe mostrar en el lcd.
; Utiliza el modo de trabajo de 4 bit.
;*****************************************************************
lcd_send_cmd_4b:
        push	arg			; Guardamos el argumento ya que lo vamos a modificar
	in	tmp, LCD_CTRL_DDR	; copio en tmp 00001110
	sbr	tmp, 0b11110000		; Seteamos los bits de datos como salida
	out	LCD_CTRL_DDR, tmp	; Actualizamos el DDR
	in	tmp, LCD_CTRL_PORT	; Obtenemos los datos del puerto
	cbr	tmp, 0b11111110		; Borramos los datos que no usamos
	cbr	arg, 0b00001111		; Solamente nos quedamos con el high nibble de arg
	or	tmp, arg		; Guardamos los datos en tmp
	out	LCD_CTRL_PORT, tmp	; Enviamos los datos en el puerto
	sbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 1
	nop
	nop
	nop
	cbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 0 (termina el pulso)
	pop	arg			; Recuperamos el valor original del argumento
	cbr	tmp, 0b11110000		; Hacemos lo mismo que antes, con la diferencia
	swap	arg			; de que ahora nos queremos quedar con el low
	cbr	arg, 0b00001111		; nibble del argumento (i.e. el comando)
	or	tmp, arg		; Guardamos los datos en tmp
	out	LCD_CTRL_PORT, tmp	; Enviamos los datos en el puerto
	sbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 1
	nop
	nop
	nop
	cbi	LCD_CTRL_PORT, LCD_E    ; Seteamos enable en 0 (termina el pulso)
	in	tmp, LCD_CTRL_DDR       ; Obtenemos el valor del DDR
	cbr	tmp, 0b11110000		; Seteamos los bits de datos como entrada
	out	LCD_CTRL_DDR, tmp       ; Actualizamos el DDR
	ret

;*****************************************************************
; lcd_getinfo: Setea al display de manera tal que este pueda enviar
; información al microcontrolador. Esto requiere setear RS = 0
; y RW = 1.
;*****************************************************************
lcd_getinfo:
        in	tmp, LCD_CTRL_DDR
	andi 	tmp, 0b00001111
	out	LCD_CTRL_DDR, tmp
	cbi	LCD_CTRL_PORT, LCD_RS	; Seteamos RS en 0 para enviar comandos
	sbi	LCD_CTRL_PORT, LCD_RW	; Seteamos RW en 1 para leer datos del display
	sbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 1
	nop
	in	tmp, LCD_CTRL_PIN	; Obtenemos datos del display
	andi	tmp, 0b11110000		; Nos quedamos solo con D4-D7
	mov	rtn, tmp		; Guardamos la informacion en el registro de retorno
	cbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 0 (termina el pulso)
	nop                             ; Ahora hacemos lo mismo ya que al estar trabajando
	nop                             ; en 4 bit el display nos va a mandar la informacion del low nibble
	sbi	LCD_CTRL, LCD_E		; Seteamos enable en 1
	nop
	in	tmp, LCD_CTRL_PIN	; Obtenemos datos del display
	andi	tmp, 0b11110000		; Nos quedamos solo con D4-D7
	swap	tmp			; Hacemos swap asi queda correctamente guardado
	or	rtn, tmp		; el low nibble en el registro de retorno
	cbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 0 (termina el pulso)
	cbi	LCD_CTRL_PORT, LCD_RW	; Seteamos RW en 0 para escribir datos al display
	ret                             ; ya que esto es lo que se hace por defecto en un lcd

;*****************************************************************
; lcd_wait: Lee información del display haciendo uso de la rutina
; lcd_getinfo. A partir de este byte leido se fija en el bit 7, el
; cual corresponde a la busy flag. Seguimos iterando hasta que
; busy flag es igual a cero, lo cual indica que podemos seguir
; operando con el display.
;*****************************************************************
lcd_wait:
        rcall	LCD_getinfo
	andi	rtn, 0x80		; 0x80 = 0b10000000. si al hacer andi el
	brne	LCD_wait		; resultado es 0x00 setea la flag Z = 1
	ret                             ; de esta manera solamente si busy flag = 0

