// Este programa es una prueba para ver como funciona
// la comunicacion serie. Basicamente el programa
// espera a que llegue un dato. Cuando esto sucede guarda
// el dato en un registro, cambia el estado (ON o OFF) del
// Puerto C y transmite el valor recibido tal cual esta

// Frecuencia de clock de 16 MHz
#define F_CPU 16000000UL
// Baud Rate de 9600
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE ( ( ( F_CPU / (USART_BAUDRATE * 16UL) ) ) - 1 )

#include<avr/io.h>

int main(void) {
  uint8_t recieved_byte;

  // Habilitamos el data direction register del puerto C para salida
  DDRC |= 0xFF;

  // Habilitamos los bits para recibir y transmitir
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
  // Configuramos la comunicación serie como una de 8 bit de datos y 1 stop bit
  UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
  // Cargamos el BAUD_PRESCALE en la parte baja y alta del registro UBRR0H
  UBRR0H  = (uint8_t) (BAUD_PRESCALE >> 8);
  UBRR0L  = (uint8_t) BAUD_PRESCALE;

  // Inicializamos el puerto C como encendido
  PORTC = 0x00;

  // Armo el loop infinito
  while(1) {
    // Esperamos hasta que el puerto esta listo para leer
    while( ( UCSR0A & ( 1 << RXC0 ) ) == 0 ){}
 
    // Guardo el byte recibido
    recieved_byte = UDR0;

    // Esperamos hasta que el puerto este listo para transmitir
    while( ( UCSR0A & ( 1 << UDRE0 ) ) == 0 ){}

    // Si el byte recibido es 0xFF complemento el valor del puerto C
    if(recieved_byte == 0xFF) {
      PORTC = ~PORTC;
    }

    // Reenvio el byte recibido
    UDR0 = recieved_byte;

  }

  // Nunca debería llegar hasta este punto
  return (0);
}
