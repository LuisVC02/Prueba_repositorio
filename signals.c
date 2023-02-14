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

#define MAG_ADJST 2048


uint16_t sin_DAC(uint16_t paso){
	if(paso <= MAX_DAC_VALUE) return MID_DAC_VALUE+(paso*(-1*paso+MAX_DAC_VALUE))/MAG_ADJST;

	if(paso > TWO_MAX_DAC_VALUE) return 0;

	paso = paso - MAX_DAC_VALUE;
	return MID_DAC_VALUE-(paso*(-1*paso+MAX_DAC_VALUE))/MAG_ADJST;

}


uint16_t triangle_DAC(uint16_t paso){
	if(paso <= MAX_DAC_VALUE) return paso; // Subida de la triangular

	if(paso > TWO_MAX_DAC_VALUE) return 0; // Comprobación por error de rango

	return TWO_MAX_DAC_VALUE-paso; // Bajada triangular
}



uint16_t square_DAC(uint16_t paso){
	if(paso < MAX_DAC_VALUE) return MAX_DAC_VALUE;
	return 0;
}




