/*
 * PIT_control.c
 *
 *  Created on: 10 feb 2023
 *      Author: luisr
 */

#include <stdint.h>
#include "PIT_control.h"
#include "fsl_clock.h"



void PIT_Initialization(PIT_Type * module, bool debug, PIT_timer timer, uint32_t time_us, uint8_t enable_interrupts){
	CLOCK_SetSimSafeDivs(); // Inicializa los divisores de reloj, como deben estar
	pit_chnl_t channel = (pit_chnl_t) timer;
	// PIT inialization ---------------------------------------------------------
	pit_config_t PIT_Config = {
			debug //Deshabilita el PIT en modo debug
	};

	PIT_Init(module, &PIT_Config); // Inicializa el modulo con la configuracion definida en la estructura

	PIT_Chain_mode(module, channel, false);

	// El clock del modulo PIT es el bus clock, es por eso que se obtiene la frecuencia de este
	PIT_SetTimerPeriod(module, channel, USEC_TO_COUNT(time_us, CLOCK_GetFreq(PIT_clock))); // Establece la recarga del timer USEC_TO_COUNT(us, clock)
	PIT_StartTimer(module, channel); // Inicia el timer

	if(enable_interrupts) PIT_EnableInterrupts(module, channel, kPIT_TimerInterruptEnable); // Habilita interrupcion
	else PIT_DisableInterrupts(module, channel, kPIT_TimerInterruptEnable);                 // Deshabilita interrupcion

	PIT_ClearStatusFlags(module, channel, Timer_flag);
	// --------------------------------------------------------------------------
}



void setTime_us(PIT_Type * module , PIT_timer timer, uint32_t time_us){
	pit_chnl_t channel = (pit_chnl_t) timer;
	PIT_SetTimerPeriod(module, channel, USEC_TO_COUNT(time_us, CLOCK_GetFreq(PIT_clock))); // Establece la recarga del timer USEC_TO_COUNT(us, clock)
}

void setTime_ms(PIT_Type * module , PIT_timer timer, uint32_t time_ms){
	pit_chnl_t channel = (pit_chnl_t) timer;
	PIT_SetTimerPeriod(module, channel, USEC_TO_COUNT(time_ms*1000, CLOCK_GetFreq(PIT_clock))); // Establece la recarga del timer USEC_TO_COUNT(us, clock)
}

