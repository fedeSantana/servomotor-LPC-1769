/*
 * DR_Systick.c
 *
 *  Created on: 15 ago. 2020
 *      Author: Tauro
 */

#include <DR_Systick.h>
#include "inicializacion.h"
#include "mqe.h"
#include "RegsLPC1769.h"

extern int flagTimerOver;
extern int tiempo;
extern State state;


void SysTick_Handler(void)
{
	if (state.timerAperturaActive == TRUE){
		state.counter--;
		if ((state.counter <= 0) && (state.aperturaEnd == FALSE))
		{
			state.aperturaEnd = TRUE;
			state.timerAperturaActive = FALSE;
			state.counter = 10000;
		}
		else {
		// No deberia entrar aca
		}
	}
}


void EINT0_IRQHandler(void)
{
	EXTINT |= 0x1 << 0; // Limpio el flag de la EINT0 escribiendo un UNO.
	state.dato = 1;
}



