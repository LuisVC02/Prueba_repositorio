#include <stdint.h>
#include "MK64F12.h"
#include "fsl_common_arm.h"
#include "fsl_clock.h"
#include "fsl_dac.h"
#include "PIT_control.h"
#include "signals.h"
#include "NVIC.h"

#define time_us 10
#define DAC DAC0
#define DAC_REF kDAC_ReferenceVoltageSourceVref2


volatile static uint8_t flanco = 0;

int main(void){
	CLOCK_SetSimSafeDivs(); // Inicializa los divisores de reloj, como deben estar

	dac_config_t DAC_config = {
			DAC_REF,
			false
	};

	DAC_Init(DAC, &DAC_config);
	DAC_Enable(DAC, true);
	DAC_EnableBuffer(DAC, true);


	PIT_Initialization(PIT_module, false, T0, time_us, true);

	// NVIC initialization ------------------------------------------------------
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;
	// --------------------------------------------------------------------------

	uint16_t counter = 0;

	while(1){
		if(flanco){
			flanco = 0;
			if(counter >= 4097) counter = 0;
			else counter ++;
			DAC_SetBufferValue(DAC, 0U, triangle(counter));
		}
	}
	return 0;
}

void PIT0_DriverIRQHandler(void){
	flanco = 1;
	Clear_interrupt_flag(PIT_module, T0, Timer_flag);
}
