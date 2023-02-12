/*
 * signals.c
 *
 *  Created on: 10 feb 2023
 *      Author: luisr
 */
#include "signals.h"

#define MAX_DAC_VALUE 4095
#define TWO_MAX_DAC_VALUE 8190
#define MID_DAC_VALUE 2047
#define MIN_DAC_VALUE 0
#define MID_DAC_VALUE_SQUARE 4190209
#define PI 3.141592654
#define TWO_PI 6.283185307
/*
 * 2047*2047 = a*a+ b*b
 * a*a = 2047*2047 - b*b
 * a = sqrt(2047*2047 - b*b)
 */



/*double sqrt(double numero){
	double aproximacion = numero / 2.0;
	double diferencia = (aproximacion*aproximacion)-numero;
	double division = 0;

	diferencia = (diferencia >= 0)? diferencia : diferencia * -1;

	while(diferencia > 0.1){
		division = numero / aproximacion;
		aproximacion = (aproximacion+division)/2;
		diferencia = (aproximacion*aproximacion) - numero;
		diferencia = (diferencia >= 0)? diferencia : diferencia * -1;
	}
	return aproximacion;
}*/



float sin(float rad){
	float result = 0;
	if(rad < 0 || rad > 6.283185) return 0;

	if(rad > PI){
		rad = rad - PI;
		result = ((-1*rad*rad)+(rad*PI))/-2.5;
	}
	else{
		result = ((-1*rad*rad)+(rad*PI))/2.5;
	}
	return result;
}


uint16_t triangle(uint16_t paso){
	if(paso <= MAX_DAC_VALUE) return paso; // Subida de la triangular

	if(paso > TWO_MAX_DAC_VALUE) return 0; // Comprobación por error de rango

	return TWO_MAX_DAC_VALUE-paso; // Bajada triangular
}



uint16_t square(uint16_t paso){
	if(paso < MAX_DAC_VALUE) return MAX_DAC_VALUE;
	return 0;
}




