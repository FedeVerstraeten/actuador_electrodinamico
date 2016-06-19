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
;	BIN_TO_ASCII
;******************************************************************
; Rutinas para convertir un número binario de 16 bit que se
; obtuvo con el ADC del microcontrolador en un número decimal
; codificado en ASCII de manera tal que se puede mostrar en el
; display el valor medido.
; Creditos por el código: http://www.avr-asm-tutorial.net
;******************************************************************

;******************************************************************
; bin_to_asc_lb: Convierte un número binario de 16 bit en un
; número decimal de 5 digital codificado en ASCII.
; Entrada: número binario de 16 bit en rBin1H:L, puntero Z apuntando
; al principio de una cadena de 5 caracteres. Si hay ceros en los
; digitos más significativos del número decimal obtenido se
; rellena la cadena con espacios blancos (blanks).
;******************************************************************

bin_to_asc_lb:
	rcall   bin_to_bcd      ; convert binary to BCD
	ldi     tmp, 4          ; Counter is 4 leading digits
	mov     rBin2L, tmp
bin_to_asc_lb_loop_a:
	ld      tmp, z          ; read a BCD digit
	tst     tmp             ; check if leading zero
	brne    bin_to_asc_lb_loop_b     ; No, found digit >0
	ldi     tmp, ' '        ; overwrite with blank
	st      z+, tmp         ; store and set to next position
	dec     rBin2L          ; decrement counter
	brne    bin_to_asc_lb_loop_a     ; further leading blanks
	ld      tmp, z          ; Read the last BCD
bin_to_asc_lb_loop_b:
	inc     rBin2L          ; one more char
bin_to_asc_lb_loop_c:
	subi    tmp, -'0'       ; Add ASCII-0
	st      z+, tmp         ; store and inc pointer
	ld      tmp, z          ; read next char
	dec     rBin2L          ; more chars?
	brne    bin_to_asc_lb_loop_c     ; yes, go on
	sbiw    ZL, 5           ; Pointer to beginning of the BCD
	ret                     ; done


;******************************************************************
; bin_to_asc: Se trata de una rutina identica a bin_to_asc_lb con
; la diferencia de que en el caso de que haya ceros en los digitos
; más significativos del número decimal obtenido no los llena con
; espacios blancos.
;******************************************************************

bin_to_asc:
	rcall   bin_to_asc_lb   ; Convert binary to ASCII
	ldi     tmp, 6          ; Counter is 6
	mov     rBin2L, tmp
bin_to_asc_loop_a:
	dec     rBin2L          ; decrement counter
	ld      tmp, z+         ; read char and inc pointer
	cpi     tmp, ' '        ; was a blank?
	breq    bin_to_asc_loop_a      ; Yes, was a blank
	sbiw    ZL, 1           ; one char backwards
	ret                     ; done

;******************************************************************
; bin_to_bcd: Convierte un número binario de 16 bit en un
; BCD de 5 dígitos.
; Entrada: Número binario de 16 bit almacenado en rBin1H:L y
; puntero Z apuntando al primer digito en el que se guarda el
; resultado.
;******************************************************************

bin_to_bcd:
	push    rBin1H          ; Save number
	push    rBin1L
	ldi     tmp, HIGH(10000); Start with tenthousands
	mov     rBin2H, tmp
	ldi     tmp, LOW(10000)
	mov     rBin2L, tmp
	rcall   bin_to_digit    ; Calculate digit
	ldi     tmp, HIGH(1000) ; Next with thousands
	mov     rBin2H, tmp
	ldi     tmp, LOW(1000)
	mov     rBin2L, tmp
	rcall   bin_to_digit    ; Calculate digit
	ldi     tmp, HIGH(100)  ; Next  with hundreds
	mov     rBin2H, tmp
	ldi     tmp, LOW(100)
	mov     rBin2L, tmp
	rcall   bin_to_digit    ; Calculate digit
	ldi     tmp, HIGH(10)   ; Next with tens
	mov     rBin2H, tmp
	ldi     tmp, LOW(10)
	mov     rBin2L, tmp
	rcall   bin_to_digit    ; Calculate digit
	st      z, rBin1L       ; Remainder are ones
	sbiw    ZL, 4           ; Put pointer to first BCD
	pop     rBin1L          ; Restore original binary
	pop     rBin1H
	ret                     ; and return

;******************************************************************
; bin_to_digit: Convierte un digito decimal por medio de sustracción
; continua de un BCD.
;******************************************************************

bin_to_digit:
	clr     tmp             ; digit count is zero
bin_to_digit_loop_a:
	cp      rBin1H, rBin2H  ; Number bigger than decimal?
	brcs    bin_to_digit_loop_c    ; MSB smaller than decimal
	brne    bin_to_digit_loop_b    ; MSB bigger than decimal
	cp      rBin1L, rBin2L  ; LSB bigger or equal decimal
	brcs    bin_to_digit_loop_c    ; LSB smaller than decimal
bin_to_digit_loop_b:
	sub     rBin1L, rBin2L  ; Subtract LSB decimal
	sbc     rBin1H, rBin2H  ; Subtract MSB decimal
	inc     tmp             ; Increment digit count
	rjmp    bin_to_digit_loop_a    ; Next loop
bin_to_digit_loop_c:
	st      z+, tmp         ; Save digit and increment
	ret                     ; done
