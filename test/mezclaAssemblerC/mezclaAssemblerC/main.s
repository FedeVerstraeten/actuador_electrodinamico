
/*
 * main.s
 *
 * Created: 13/06/2016 01:57:28 a.m.
 *  Author: Eze
 */ 
 .global main
.extern seno
main:
;**** Seno
	loop:
		rcall seno
		rjmp loop