/*
 * DR_Systick.c
 *
 *  Created on: 15 ago. 2020
 *      Author: Tauro
 */

#include <DR_Systick.h>
#include "inicializacion.h"
#include "mqe.h"

extern int flagTimerOver;
extern int tiempo;
extern State state;


void SysTick_Handler(void)
{
	if (state.timerAperturaActive == TRUE){
		state.counter--;
		if (state.counter <= 0 && state.aperturaEnd == FALSE){
			state.aperturaEnd = TRUE;
			state.timerAperturaActive = FALSE;
		}
		else {
		// No deberia entrar aca
		}
	}
}
