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
;     LCD_DRIVER
;******************************************************************
; Rutinas utilizadas para manejar el display LCD.
;******************************************************************

;*****************************************************************
; CONSTANTES
;*****************************************************************
        .equ    LCD_CTRL_PORT   =       PORTB ; Definimos el puerto (escritura)
        .equ    LCD_CTRL_PIN    =       PINB  ; y el pin (lectura) al que estan
        .equ    LCD_CTRL_DDR    =       DDRB  ; conectados los pines de control del display

        .equ	LCD_RS          =       0 ; Estos corresponden al numero del pin
        .equ	LCD_RW          =       1 ; del micro al que esta conectado los
        .equ	LCD_E           =       2 ; pines RS, RW y E del display

        .equ LCD_FUNCTION_SET   =       0x38 ; 0b00111000
        .equ LCD_FUNCTION_SET_4BIT =    0x28 ; 0b00101000
        .equ LCD_DISPLAY_OFF    =       0x08 ; 0b00001000
        .equ LCD_DISPLAY_ON     =       0x0F ; 0b00001111
        .equ LCD_DISPLAY_CLEAR  =       0x01 ; 0b00000001
        .equ LCD_ENTRY_MODE_SET =       0x06 ; 0b00000110
        .equ LCD_CURSOR_HOME    =       0x02 ; 0b00000010
        .equ LCD_FIRST_LINE     =       0x80
        .equ LCD_SECOND_LINE    =       0xC0
        .equ LCD_CURSOR_OFF     =       0x0C

;*****************************************************************
; lcd_init: Inicialización del display. Aca se encuentra la
; configuración de los distintos parámetros necesarios para su
; correcto funcionamiento.
;*****************************************************************
lcd_init:
        ; Inicializamos los data direction registers
        in      tmp, LCD_CTRL_DDR
        ori     tmp, 0xF0
	out     LCD_CTRL_DDR, tmp
	in      tmp, LCD_CTRL_DDR
	ori     tmp, ( (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_E) )
	out     LCD_CTRL_DDR, tmp

	; First part of init sequence is 3 x Function Set with
	; stipulated waits (no Busy Flag available). This is done
	; in eight bit mode although four low bits are not
	; connected and ignored.
        ; La primera parte de la secuencia de inicio consiste
        ; en enviar 3 veces consecutivas el comando function set
        ; con un intervalo de tiempo entre cada uno (se puede
        ; mejorar si se utiliza la busy flag del display.
        ; Todo esto se hace en modo de 8 bit pero los 4 bit
        ; menos significativos no estan conectados y son
        ; ignorados.
	ClearLcdRWBit
	ClearLcdRSBit
	ldi     arg, LCD_FUNCTION_SET
        rcall   wait5ms
  	rcall   wait5ms
  	rcall   wait5ms
	rcall   lcd_send_high_nibble
	rcall   wait5ms
	rcall   lcd_send_high_nibble
	rcall   wait100us
	rcall   lcd_send_high_nibble

	; Ahora seteamos el display en modo de 4 bit
	ldi     arg, LCD_FUNCTION_SET_4BIT
	rcall   wait100us
	rcall   lcd_send_high_nibble

	; Hacemos el resto de la secuencia de comandos
	LcdSendCommand LCD_FUNCTION_SET_4BIT
	LcdSendCommand LCD_DISPLAY_ON
	LcdSendCommand LCD_DISPLAY_CLEAR
	LcdSendCommand LCD_ENTRY_MODE_SET
	LcdSendCommand LCD_DISPLAY_ON

	ret


;*****************************************************************
; lcd_send_high_nibble: Envia solamente los 4 bits más significativos
; (parte high) del byte almacenado en la variable arg.
;*****************************************************************

lcd_send_high_nibble:
        ; Como no esta implementado el algoritmo para
        ; esperar a que la busy flag este en el estado
        ; correcto usamos un delay.
        rcall   wait5ms
        mov     tmp,arg
        ; Usamos una mascara para quedarnos solo con la parte high
        andi    tmp, 0xF0
        ; Leemos el puerto
        in      tmp2, LCD_CTRL_PORT
        ; Vamos a cambiar la parte high asi que aplicamos una mascara
        andi    tmp2, 0x0F
        ; Combinamos los resultados
        or      tmp, tmp2
        ; Enviamos los datos al display
        out     LCD_CTRL_PORT, tmp
        SendLcdStrobe
        ret

;*****************************************************************
; lcd_send_ascii: Rutina utilizada en la parte de medición de
; intensidad lumínica. Para funcionar correctamente se debe
; cargar el puntero Z apuntando al primero de los 5 caracteres
; (correspondientes a un numero entero de 5 digitos) que se van
; a leer. Usamos esta rutina en vez de lcd_putstring ya que
; los strings terminan en ENDSTR y estos 5 caracteres que leemos
; salen de la rutina Bin2ToAsc, la cual no añade ENDSTR al final.
;*****************************************************************

lcd_send_ascii:
        ldi     tmp3, 5         ; Contador que utilizamos
        ld      arg, Z+         ; Almacenamos un caracter en arg
lcd_send_ascii_loop:
        LcdPutChar              ; Mostramos el caracter en el lcd
	ld	arg, Z+         ; Almacenamos otro caracter
	dec     tmp3            ; Decrementamos el contador
	cpi     tmp3, 0         ; Si es cero termina el loop
	brne    lcd_send_ascii_loop  ; si no, continua
        ret

;; ;*****************************************************************
;; ; lcd_getinfo: Setea al display de manera tal que este pueda enviar
;; ; información al microcontrolador. Esto requiere setear RS = 0
;; ; y RW = 1.
;; ;*****************************************************************
;; lcd_getinfo:
;;         in	tmp, LCD_CTRL_DDR
;; 	andi 	tmp, 0b00001111
;; 	out	LCD_CTRL_DDR, tmp
;; 	cbi	LCD_CTRL_PORT, LCD_RS	; Seteamos RS en 0 para enviar comandos
;; 	sbi	LCD_CTRL_PORT, LCD_RW	; Seteamos RW en 1 para leer datos del display
;; 	sbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 1
;; 	nop
;; 	in	tmp, LCD_CTRL_PIN	; Obtenemos datos del display
;; 	andi	tmp, 0b11110000		; Nos quedamos solo con D4-D7
;; 	mov	rtn, tmp		; Guardamos la informacion en el registro de retorno
;; 	cbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 0 (termina el pulso)
;; 	nop                             ; Ahora hacemos lo mismo ya que al estar trabajando
;; 	nop                             ; en 4 bit el display nos va a mandar la informacion del low nibble
;; 	sbi	LCD_CTRL_PORT, LCD_E		; Seteamos enable en 1
;; 	nop
;; 	in	tmp, LCD_CTRL_PIN	; Obtenemos datos del display
;; 	andi	tmp, 0b11110000		; Nos quedamos solo con D4-D7
;; 	swap	tmp			; Hacemos swap asi queda correctamente guardado
;; 	or	rtn, tmp		; el low nibble en el registro de retorno
;; 	cbi	LCD_CTRL_PORT, LCD_E	; Seteamos enable en 0 (termina el pulso)
;; 	cbi	LCD_CTRL_PORT, LCD_RW	; Seteamos RW en 0 para escribir datos al display
;; 	ret                             ; ya que esto es lo que se hace por defecto en un lcd

;; ;*****************************************************************
;; ; lcd_wait: Lee información del display haciendo uso de la rutina
;; ; lcd_getinfo. A partir de este byte leido se fija en el bit 7, el
;; ; cual corresponde a la busy flag. Seguimos iterando hasta que
;; ; busy flag es igual a cero, lo cual indica que podemos seguir
;; ; operando con el display.
;; ;*****************************************************************
;; lcd_wait:
;;         rcall	lcd_getinfo
;; 	andi	rtn, 0x80		; 0x80 = 0b10000000. si al hacer andi el
;; 	brne	lcd_wait		; resultado es 0x00 setea la flag Z = 1
;; 	ret                             ; de esta manera solamente si busy flag = 0

