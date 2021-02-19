/*
 * DR_Systick.c
 *
 *  Created on: 15 ago. 2020
 *      Author: nicoc
 */

#include <DR_Systick.h>
#include "inicializacion.h"
extern int flagTimerOn;
extern int flagTimerOver;
extern int tiempo;


void SysTick_Handler(void)
{

	if (flagTimerOn == 1)
	{
		tiempo--;
		if (tiempo == 0)
		{
			flagTimerOver = 1;
		}
	}

}
