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
;	MACROS
;******************************************************************


;******************************************************************
; MoveZTo: Mueve el puntero Z hasta la posición indicada.
; ZH:ZL <- ZH:ZL + @0. Usado para desplazarse en las cadenas (.db)
; que forman al menu.
;******************************************************************
.MACRO	MoveZTo
	adiw	ZH:ZL, @0
.ENDMACRO


;******************************************************************
; LoadWord: Carga contenido en ROM apuntado por Z en registros
; para Word (wrdh:wrdl). La dirección que almacenada en los
; registros se carga nuevamente en Z.
; Z queda apuntando a una nueva dirección de memoria en ROM.
; wrdh:wrdl <- (ZH:ZL)
; ZH:ZL	<- wrdh:wrdl
;******************************************************************
.MACRO	LoadWord
	lpm	wrdh, Z+
	lpm	wrdl, Z+
	movw	Zh:Zl, wrdh:wrdl
.ENDMACRO

;*****************************************************************
; SendLcdStrobe: Envia un pulso en el bit de datos Enable.
;*****************************************************************

.macro SendLcdStrobe
        sbi     LCD_CTRL_PORT, LCD_E
        ; Hay que esperar al menos 80 ns antes de cerrar el
        ; pulso (E=0). Como usamos clock de 16 Mhz es necesario
        ; usar unos nop para que pase el tiempo.
        nop
        nop
        nop
        cbi     LCD_CTRL_PORT, LCD_E
        ; Los datos tienen que estar estables 10ns luego de haber
        ; hecho un strobe. Para no cumplir esto deberia haber
        ; un clock de más de 100 Mhz asi que no es un problema.
.endmacro

;*****************************************************************
; ClearLcdRWBit, SetLcdRWBit: Establece en 0 o 1 el bit RW.
;*****************************************************************

.macro ClearLcdRWBit
        cbi     LCD_CTRL_PORT, LCD_RW
.endmacro

.macro SetLcdRWBit
        sbi     LCD_CTRL_PORT, LCD_RW
.endmacro

;*****************************************************************
; ClearLcdRSBit, SetLcdRSBit: Establece en 0 o 1 el bit RS.
;*****************************************************************

.macro ClearLcdRSBit
        cbi     LCD_CTRL_PORT, LCD_RS
.endmacro

.macro SetLcdRSBit
        sbi     LCD_CTRL_PORT, LCD_RS
.endmacro

;*****************************************************************
; LcdSendCommand: Envia un comando almacenado en la variable
; arg al display.
;*****************************************************************

.macro LcdSendCommand
        ClearLcdRSBit
        ldi     arg, @0
        ;; rcall   lcdBusyWait
        rcall   lcd_send_high_nibble
        swap    arg
        rcall   lcd_send_high_nibble
.endmacro

;*****************************************************************
; LcdPutChar: Envia un caracter almacenado en la variable
; arg al display.
;*****************************************************************

.macro LcdPutChar
        SetLcdRSBit
        ;; rcall lcdBusyWait
        rcall   lcd_send_high_nibble
        swap    arg
        rcall   lcd_send_high_nibble
.endmacro

;******************************************************************
; SetLCDClearAtHome: Limpia la pantalla del display y luego ubica
; al cursor en Home.
;******************************************************************

.MACRO	SetLcdClearAtHome
        LcdSendCommand LCD_DISPLAY_CLEAR
	LcdSendCommand LCD_CURSOR_HOME
.ENDMACRO

;******************************************************************
; SecondLine: Ubica al cursor en el inicio de la segunda
; línea del display.
;******************************************************************

.MACRO	SecondLine
	LcdSendCommand LCD_SECOND_LINE
.ENDMACRO

;******************************************************************
; CheckSignalEnd: Verifica que no se haya llegado al final de las
; muestras de una señal que se encuentran almacenadas en memoria.
; Si el resultado es negativo sigue con la rutina al ir a la
; etiqueta continue que toma como primer parámetro.
; Si el resultado es positivo entonces vuelve al inicio de las
; las muestras desviandose hacia la etiqueta que lleva como
; segundo parámetro.
;******************************************************************

.MACRO	CheckSignalEnd
        ; 0xCB = ENDSIG pero el include de las macros está
        ; antes que el equ por lo que el compilador tira error
        cpi     tmp2, 0xCB
        brne    @0
        cp      tmp2, tmp
        breq    @1
.ENDMACRO
