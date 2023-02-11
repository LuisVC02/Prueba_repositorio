/*
 * signals.c
 *
 *  Created on: 10 feb 2023
 *      Author: luisr
 */
#include "signals.h"

#define MAX_DAC_VALUE 4095
#define MID_DAC_VALUE 2047
#define MIN_DAC_VALUE 0
#define MID_DAC_VALUE_SQUARE 4190209

/*
 * 2047*2047 = a*a+ b*b
 * a*a = 2047*2047 - b*b
 * a = sqrt(2047*2047 - b*b)
 */



double sqrt(double numero){
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
}



uint16_t sin(uint16_t paso){
	return (uint16_t)sqrt(MID_DAC_VALUE_SQUARE + (paso*paso));
}



uint16_t triangle(uint16_t paso){
	if(paso <= MID_DAC_VALUE) return 2*paso;
	return (2*MAX_DAC_VALUE)-(2*paso);
}



uint16_t square(uint16_t paso){
	if(paso < MID_DAC_VALUE) return MAX_DAC_VALUE;
	return 0;
}




