/*
 * math.c
 *
 *  Created on: 11 feb 2023
 *      Author: luisr
 */

#include "math.h"

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


double sin(double rad){
	double result = 0;
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
