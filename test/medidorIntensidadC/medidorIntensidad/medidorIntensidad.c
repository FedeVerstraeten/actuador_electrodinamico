/*
 * medidorIntensidad.c
 *
 * Created: 11/06/2016 03:57:17 a.m.
 *  Author: Eze
 */ 


    #include <avr/io.h>
    
    #define F_CPU 1000000
    
    #include <util/delay.h>
   
    
    #define    E   5
    //enable va a ser el 5to pin de PORTD seteado mas adelante
    #define RS  6
    //el selector de registro va a ser el 6to pin de portD
    
    void send_a_command(unsigned char command);
    void send_a_character(unsigned char character);
    void send_a_string(char *string_of_characters);
    
	int main(void)
    {
	    DDRB = 0xFF;
	    
	    DDRD = 0xFF;
	    _delay_ms(50);
	    DDRC = 0;//PORTC entrada
	    
	    ADMUX |=(1<<REFS0);//seteo la referencia del ADC
	    ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0);
	    //habilito ADC,modo free running, prescalar 2
	    float i =0;
	    float LDR= 0; //almaceno la salida (que es digital)
	    char LDRSHOW [7]; //para mostrar la salida en el lcd
	    send_a_command(0x01); //limpio pantalla
	    _delay_ms(50);
	    send_a_command(0x38); // aca usaba 8bit 
	    _delay_ms(50);
	    send_a_command(0b00001111); //pantalla prendida y cursor parpadeando
	    ADCSRA |=(1<<ADSC);  //conversion ADC empieza
	    
	    send_a_string ("Entrada  ");
	    send_a_command(0x80 + 0x40 + 0);// corro cursor abajo en seg linea
	    send_a_string ("LDR res=");
	    send_a_command(0x80 + 0x40 + 8);// corro cursor al medio en seg linea
	    while(1)
	    {
			i=ADC/25.6;// con m328p tengo 7 bit ADC Vref(5V)/128=39mV tengo 1V cuando el incremento del contador va por 25.6
			LDR= (i*7/(5-i));
		    dtostrf(LDR, 4, 1, LDRSHOW);
		    send_a_string(LDRSHOW);
		    send_a_string("K   ");
			//explicacion de lo que hace dtostrf que encontre piola
		    //dtostr(double precision value, width, precision, string that will store the numbers);
		    // Value is either a direct value plugged into this place, or a variable to contains a value.
		    //Width that is used with dtostrf is the number of characters in the number that includes the negative sign (-). For instance, if the number is -532.87, 
			//the width would be 7 including the negative sign and the decimal point.
		    //Precision is how many numbers would be after the decimal point in the dtostrf usage.
		    _delay_ms(50);
		    send_a_command(0x80 + 0x40 + 8);//vuelvo a donde escribo valor en display
	    }
	    
    }

    void send_a_command(unsigned char command)
    {
	    PORTB = command;
	    PORTD &= ~ (1<<RS); //pongo 0 en RS para decirle al lcd que se manda un comando
	    PORTD |= 1<<E; //le digo al lcd lcdque reciba comando/dato
	    _delay_ms(50);
	    PORTD &= ~1<<E;//le aviso al lcd que se termino de enviar comandos
	    PORTB= 0;
    }
    
    void send_a_character(unsigned char character)
    {
	    PORTB= character;
	    PORTD |= 1<<RS;//idem anterior solo que mando datos y no comandos
	    PORTD |= 1<<E;////le digo al lcd lcdque reciba comando/dato
	    _delay_ms(50);
	    PORTD &= ~1<<E;//le aviso al lcd que se termino de enviar comandos/datos
	    PORTB = 0;
    }
    void send_a_string(char *string_of_characters)
    {
	    while(*string_of_characters > 0)
	    {
		    send_a_character(*string_of_characters++);
	    }
    }