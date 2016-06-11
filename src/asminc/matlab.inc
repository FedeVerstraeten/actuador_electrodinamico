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

        .equ    COMM_HANDSHK    =       0xCB

;******************************************************************
; comm_start: Empieza la comunicación con Matlab. Setea el
; handshake como 0 (es decir, no realizado) y muestra por
; pantalla que esta esperando a que se realice el handshake.
;******************************************************************

; Guardo en tmp el byte más viejo y en tmp2 el más reciente
comm_start:
        ; Inicializo handshake en 0
        ldi     handshk, 0x00
        ; Muestro en el display "Esperando handshake"
        ;; ldi     zh, high(strCommIdle)
        ;; ldi     zl, low(strCommIdle)
        ;; rcall   lcd_putstring
        rcall   usart_recieve
        mov     tmp, rtn

;******************************************************************
; comm_idle: Loop que va recibiendo datos por medio de comunicación
; USART y va chequeando si se realizó o no el handshake.
;******************************************************************

comm_idle:
        rcall   usart_recieve
        mov     tmp2, rtn
        rcall   comm_check_state
        mov     tmp, tmp2
        cpi     handshk, 0x00
        breq    comm_idle

;******************************************************************
; comm_loop_start: El handshake se realizó correctamente por lo que
; muestra en el display que esta almacenando las muestras de la
; la señal que se esta enviando desde Matlab.
;******************************************************************

comm_loop_start:
        ; Muestro en el display "Guardando muestras"
        ;; ldi     zh, high(strCommStore)
        ;; ldi     zl, low(strCommStore)
        ;; rcall   lcd_putstring
        ; Inicializo el puntero con el que me voy moviendo
        ; en la memoria en el punto en el que empieza la memoria
        ; de uso libre: SRAM_START
        ldi     Zh, high(SRAM_START)
        ldi     Zl, low(SRAM_START)
        ; Hago una lectura antes del loop, caso contrario quedaria
        ; tmp2=COMM_HANDSHK y se terminaría guardando este valor
        ; como una muestra de la señal que se va a enviar al DAC
        rcall   usart_recieve
        mov     tmp, rtn

;******************************************************************
; comm_loop: Loop principal. En este se van almacenando en la
; memoria del micro las distintas muestras de una señal periódica.
; El loop se termina cuando se recibe nuevamente un handshake,
; indicando el fin de la transmisión de datos.
;******************************************************************

comm_loop:
        rcall   usart_recieve
        mov     tmp2, rtn
        rcall   comm_check_state
        rcall   comm_mem_write
        rjmp    comm_loop

;******************************************************************
; comm_check_state: Verifica si los ultimos dos valores recibidos
; verifican que el handshake se realizó correctamente.
;******************************************************************

comm_check_state:
        cpi     tmp2, COMM_HANDSHK
        brne    end_comm_check_state
        cp      tmp2, tmp
        breq    comm_set_state
end_comm_check_state:
        ret

;******************************************************************
; comm_set_state: Se recibió un handshake por lo que hay que ver
; si esto indica que se va a empezar a recibir muestras (handshk=0x00)
; o que se terminaron de recibir todas las muestras necesarias (handshk!=0x00)
;******************************************************************

comm_set_state:
        cpi     handshk, 0x00
        breq    comm_set_handshake
        rjmp    comm_finish

;******************************************************************
; comm_set_handshake: Almacena en el registro correspondiente
; que el handshake se ha establecido.
;******************************************************************

comm_set_handshake:
        ldi     handshk, 0x01
        ret                     ; Para poder limpiar el SP de cuando se hizo rcall comm_check_state


;******************************************************************
; comm_finish: Finalizó la transmisión de datos y las muestras
; fueron almacenadas en memoria. Solamente falta agregar dos
; valores más que permitan establecer cuando se recorrieron todas
; las muestras de un período y es necesario volver al inicio.
;******************************************************************

comm_finish:
        ; Guardo en memoria dos veces el byte ENDSIG
        ; para indicar que ahi termina la señal
        ldi     tmp, ENDSIG
        st      Z+, tmp
        st      Z, tmp
        ; Hago dos veces pop para poder limpiar el SP
        ; ya que para llegar hasta aca hicimos rcall
        ; comm_set_state y en ningun momentos vamos a
        ; hacer un ret, el cual hace SP <- SP + 2
        ; mientras que cada pop hace SP <- SP + 1
        pop tmp2
        pop tmp2

        rjmp    signal_out_matlab

;******************************************************************
; comm_mem_write: Almacena en memoria los datos correspondientes a una
; muestra de la señal.
;******************************************************************
comm_mem_write:
        ; TODO
        st      Z+, tmp         ; Almaceno la muestra y aumento el puntero
        ret
