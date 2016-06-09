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
;	REGISTER_ALIAS
;******************************************************************
; Definición de alias (.DEF) de cada uno de los registros
; utilizados en la implementación.
;******************************************************************

	.def	test1	=	r0		; Definicion de prueba 0
	.def	test2	=	r1		; Definicion de prueba 1
	.def	wrdl	=	r10		; Almacena parte baja de WORD cargado en ROM
	.def	wrdh 	=	r11		; Almacena parte alta de WORD cargado en ROM
	.def	tmp	=	r16		; Registro para uso general
	.def	tmp2	=	r17		; Registro para uso general
	.def	arg	=	r18		; Registro pasaje de Argumentos
        .def    rtn     =       r19             ; Registro para valores de retorno de rutinas

