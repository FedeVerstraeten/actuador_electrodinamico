; Simple demo of 44780-based LCD display, 4-bit mode.
; Good for running at up to 4 MHz

; You need to change the following to match your microcontroller
.include "m88def.inc" 
 
; You need to change this to match the port where the four data lines DB4..DB7
; of the display are connected. These MUST be on the four high pins of the port
.equ LCD_DATA      = PORTD
.equ LCD_DATA_DIR  = DDRD

; You need to change this to match the port where the three control lines RS, R/W 
; and E of the display are connected. They must all be on the same port.
; Port:
.equ LCD_CTRL      = PORTD
.equ LCD_CTRL_DIR  = DDRD
; Pin numbers:
.equ LCD_RS = 0
.equ LCD_RW = 1
.equ LCD_E  = 2

;-- YOU SHOULD NOT NEED TO ALTER ANYTHING BEYOND THIS POINT --------------

; Lets not hard code the instructions to the LCD either...
.equ LCD_FUNCTION_SET      = 0x38 ; 0b00111000
.equ LCD_FUNCTION_SET_4BIT = 0x28 ; 0b00101000
.equ LCD_DISPLAY_OFF       = 0x08 ; 0b00001000
.equ LCD_DISPLAY_ON        = 0x0F ; 0b00001111
.equ LCD_DISPLAY_CLEAR     = 0x01 ; 0b00000001
.equ LCD_ENTRY_MODE_SET    = 0x06 ; 0b00000110
.equ LCD_CURSOR_HOME       = 0x02 ; 0b00000010

; Define better names for some of the registers
.def   lcdData   = r16
.def   lcdTemp   = r17
.def   waitTemp1 = r18
.def   waitTemp2 = r19

; A macro for a longer delay
.macro wait15ms
   rcall wait5ms
   rcall wait5ms
   rcall wait5ms
.endmacro

; A macro to strobe data to the LCD, ie. joggle the E line.
; Data has to be steady on the LCD_DATA port and RS and R/W
; set to desired states.
.macro strobe
   sbi LCD_CTRL,LCD_E
   ; Data has to be stable for 80 ns before we strobe (lower E)
   ; We have to clock the AVR with 12,5 MHz for a single CLK to 
   ; take that long, so we can strobe immediately if we run slower
   ; than that.
   cbi LCD_CTRL,LCD_E 
   ; Data has to be stable for 10 ns after we strobed
   ; We have to clock the AVR @ 100 MHz for one CLK to take that
   ; long so thats no problem at all!
.endmacro

; A few macros to set and clear R/W and RS
.macro rwLow
   cbi LCD_CTRL,LCD_RW 
.endmacro

.macro rwHigh
   cbi LCD_CTRL,LCD_RW 
.endmacro

.macro rsLow
   cbi LCD_CTRL,LCD_RS 
.endmacro

.macro rsHigh
   sbi LCD_CTRL,LCD_RS 
.endmacro

; Send the parameter as a command
.macro lcdCommand
   rsLow
   ldi lcdData, @0
   ;rcall lcdBusyWait
   rcall lcdOutNibble
   swap  lcdData
   rcall lcdOutNibble
.endmacro

; Display  a character in lcdData
.macro lcdChar
   rsHigh
   ;rcall lcdBusyWait
   rcall lcdOutNibble
   swap lcdData
   rcall lcdOutNibble
.endmacro


;====================================================================
.org 0
rjmp reset

reset:
   ; Set up stack pointer
   ldi R16, low(RAMEND)
   out SPL, R16 
   ldi R16, high(RAMEND) 
   out SPH, R16 

   ; Set up LCD ports...
   in  lcdTemp,LCD_DATA_DIR
   ori lcdTemp,0xF0
   out LCD_DATA_DIR,lcdTemp
   in  lcdTemp,LCD_CTRL_DIR
   ori lcdTemp,((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_E))
   out LCD_CTRL_DIR,lcdTemp

LCD_INIT:

   ; First part of init sequence is 3 x Function Set with
   ; stipulated waits (no Busy Flag available). This is done
   ; in eight bit mode although four low bits are not 
   ; connected and ignored.
   rwLow
   rsLow 
   ldi lcdData,LCD_FUNCTION_SET
   wait15ms
   rcall lcdOutNibble
   rcall wait5ms
   rcall lcdOutNibble
   rcall wait100us
   rcall lcdOutNibble

   ; Now, still in 8-bit mode, set the display to 4-bit mode
   ldi lcdData,LCD_FUNCTION_SET_4BIT
   rcall wait100us
   rcall lcdOutNibble

   ; We are now in 4-bit mode, and the busy flag is available. 
   ; Do the rest of the init sequence.
   lcdCommand LCD_FUNCTION_SET_4BIT
   lcdCommand LCD_DISPLAY_ON
   lcdCommand LCD_DISPLAY_CLEAR 
   lcdCommand LCD_ENTRY_MODE_SET 
   lcdCommand LCD_DISPLAY_ON

main:
   lcdCommand LCD_CURSOR_HOME

   ; Send the characters of the message string to the display.
   ; They are in FLASH so we'll use some indirect addressing.

   ; Set up FLASH pointer
   ldi ZH, high(message*2)
   ldi ZL, low(message*2)
message_loop:
   lpm lcdData, Z+      ; Load from FLASH and increment pointer
   tst lcdData          ; End of string? (NUL character?)
   breq infinite_loop   ; Yes, bail out
   lcdChar
   rjmp message_loop    ; Next char

infinite_loop: 
      breq infinite_loop 

;-- Delay routines ----------------------------------------
wait5ms:
   ldi waitTemp1, 0x20 ; This is very conservative! Tweak this for faster output.
wait5msOuter:
   ldi waitTemp2, 0xFF
wait5msInner:
   dec waitTemp2
   brne wait5msInner
   dec waitTemp1
   brne wait5msOuter
   ret

wait100us:
   ldi waitTemp1,0x8F  ; 0x8F @ 4 MHz
wait100usLoop:
   dec waitTemp1
   brne wait100usLoop
   ret

;-- lcdOutNibble - send a half-byte to the display --------
; The routine sends the four upper bits of lcdData
; to the display.
lcdOutNibble:
   ; Wait for the Busy Flag to clear
   ; Not Yet Implemented, so we'll use a delay instead.
   rcall wait5ms
   
   ; Copy to temp register
   mov lcdTemp,lcdData
   ; Mask off low nibble
   andi lcdTemp, 0xF0
   ; Read LCD_PORT
   in waitTemp1, LCD_DATA
   ; Mask off high nibble
   andi waitTemp1, 0x0F
   ; Combine these two nibbles
   or lcdTemp, waitTemp1
   ; Output the result
   out LCD_DATA, lcdTemp
   strobe
   ret

; Here's how to do it if You have connected the four data 
; lines DB7-4 to the four low pins of the AVR port 
; (eg PORTx.3 - PORTx.0).
; We want the interface to lcdOutNibble to be unchanged
; so the nibble to be sent should still be the upper one.
   ; Copy to temp register
   mov lcdTemp,lcdData
   ; Swap the nibbles
   swap lcdTemp
   ; Mask off high nibble
   andi lcdTemp, 0x0F
   ; Read LCD_PORT
   in waitTemp1, LCD_DATA
   ; Mask off low nibble
   andi waitTemp1, 0xF0
   ; Combine these two nibbles
   or lcdTemp, waitTemp1
   ; Output the result
   out LCD_DATA, lcdTemp
   strobe
   ret

;----------------------------------------------------------

message:
.db "Hello LCD!",0,0
