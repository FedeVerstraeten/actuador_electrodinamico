/*
 * CFile1.c
 *
 * Created: 13/06/2016 01:59:46 a.m.
 *  Author: Eze
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n_puntos 256 //256 para el micro de 8 bit
extern void seno (void);

void seno(void)
{	
	DDRB = 0xFF;	//puerto B es salida
	/*
	float pi = 3.141592;
	float w ;    // ?
	float yi ;
	float fase;
	int sign_samp;
	int sin_data[n_puntos];  // la tabla de consulta del seno
	int i;
	int j;
	w= 2*pi;
	w= w/n_puntos;
	for (i = 0; i < n_puntos; i++)
	{
		yi= 127*sin(fase);
		fase=fase+w;
		sign_samp=127+yi;     // dc offset para 8 bits
		sin_data[i]=sign_samp; //escribo valor en el arreglo
		PORTB = sin_data[i];
	}
	*/
    while(1)
    {
		float pi = 3.141592;
		float w ;    
		float yi ;
		float fase=0;
		int sign_samp;
		int sin_data[n_puntos];  // la tabla de consulta del seno
		int i;
		int j;
		w= 2*pi;
		w= w/n_puntos;
		for (i = 0; i < n_puntos; i++)
		{
			yi= 127*sin(fase);
			fase=fase+w;
			sign_samp=127+yi;     // dc offset para 8 bits
			sin_data[i]=sign_samp; //escribo valor en el arreglo
			PORTB = sin_data[i];
		}/*
	    for (j = 0; j< n_puntos; j++)
		{
			PORTB = sin_data[j];	// mando al puerto el valor en esa parte del arreglo
		}*/
    }

}