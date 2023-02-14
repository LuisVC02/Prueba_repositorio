#include <stdint.h>
#include "MK64F12.h"
#include "fsl_common_arm.h"
#include "fsl_clock.h"
#include "fsl_dac.h"
#include "PIT_control.h"
#include "signals.h"
#include "NVIC.h"

#define time_us_change 15
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

	PIT_Initialization(PIT_module, false, T1, time_us_change, true);

	// NVIC initialization ------------------------------------------------------
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;
	// --------------------------------------------------------------------------

	uint16_t counter = 0;

	while(1){
		if(flanco){
			flanco = 0;
			counter += 100;
			if(counter >= 8190) counter = 0;
			DAC_SetBufferValue(DAC, 0U, sin_DAC(counter));
		}
	}
	return 0;
}

void PIT1_DriverIRQHandler(void){
	flanco = 1;
	Clear_interrupt_flag(PIT_module, T1, Timer_flag);
}

