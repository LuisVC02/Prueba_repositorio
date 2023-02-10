/*
 * PIT_control.h
 *
 *  Created on: 10 feb 2023
 *      Author: luisr
 */

#ifndef PIT_CONTROL_H_
#define PIT_CONTROL_H_

#include "MK64F12.h"
#include "fsl_pit.h"

// Definiciones ---------------------------------------------
#define PIT_clock kCLOCK_BusClk // Reloj de los timers
#define PIT_module PIT          // Direccion base apuntada al modulo PIT
#define Timer_flag kPIT_TimerFlag // Bandera interrupcion
// ----------------------------------------------------------


// Timers del modulo PIT ------------------------------------
typedef enum{
	T0 = kPIT_Chnl_0,
	T1 = kPIT_Chnl_1,
	T2 = kPIT_Chnl_2,
	T3 = kPIT_Chnl_3
}PIT_timer;
// ----------------------------------------------------------

// Interrupcion ---------------------------------------------
void PIT0_DriverIRQHandler(void); // Vector de interrupcion
// ----------------------------------------------------------


// Inicializacion ----------------------------------------------------------------------

// module            @ Direccion base apuntada al PIT
// debug             @ Activa o desactiva el PIT en debug
// timer             @ Timer a inicializar (del modulo PIT)
// time_us           @ Tiempo de inicio en us
// enable_interrupts @ Habilita o deshabilita interrupcion, no modifica el NVIC.

void PIT_Initialization(PIT_Type * module, bool debug, PIT_timer timer, uint32_t time_us, uint8_t enable_interrupts);

// -------------------------------------------------------------------------------------

// Set time -----------------------------------------------------------------------------

// module            @ Direccion base apuntada al PIT
// timer             @ Timer (del modulo PIT)
// time_us           @ Tiempo de inicio en us
// time_ms           @ Tiempo de inicio en ms

void setTime_us(PIT_Type * module , PIT_timer timer, uint32_t time_us);
void setTime_ms(PIT_Type * module , PIT_timer timer, uint32_t time_ms);
// --------------------------------------------------------------------------------------

// Clear flag interrupt -----------------------------------------------------------------

// module            @ Direccion base apuntada al PIT
// timer             @ Timer (del modulo PIT)
// flag              @ Bandera interrupcion -> Timer_flag (definida al inicio)

// Utilizado en el vector de interrupcion para limpiar la bandera de interrupcion

#define Clear_interrupt_flag(module, timer, flag)           PIT_ClearStatusFlags(module, (pit_chnl_t) timer, flag);
// --------------------------------------------------------------------------------------


#endif /* PIT_CONTROL_H_ */
