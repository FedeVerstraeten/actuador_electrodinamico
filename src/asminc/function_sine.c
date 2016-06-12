#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_POINTS 256 // Es el maximo valor en un micro de 8 bits

void function_sine(void)
{
    DDRB = 0xFF; // Puerto B es salida

    float pi = 3.141592;
    float yi;
    float phase = 0.00;
    int sine_sample;
    int sine_table[NUM_POINTS];  // Tabla de consulta del seno
    int i;
    float w = (2 * pi) / NUM_POINTS;

    for (i = 0 ; i < NUM_POINTS ; i++) // Lleno la tabla
    {
        yi = 127 * sin(phase);
        phase += w;
        sine_sample = 127 + yi; // DC offset para 8 bits (para no tener que lidiar con numeros negativos)
        sine_table[i] = sine_sample; // Escribo valor en el arreglo
    }

    while(1) // Loop principal
    {
        for (i = 0 ; i < NUM_POINTS ; i++)
        {
            PORTB = sine_table[i]; // Mando al puerto el valor en esa parte del arreglo
        }
    }
}
