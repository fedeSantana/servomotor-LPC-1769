/*
 * mqe_motor.c
 *
 *  Created on: 12 dic. 2020
 *      Author: fer_o
 */
#include "mqe.h"
#include "Regs_LPC176x.h"
#include "Register_PWM.h"
#include "Inicializacion.h"


//!< Definición de Funciones
void TIMER0_IRQHandler(void);

//!< Definición de variables
volatile State state = { INICIO, OK, FALSE, FALSE, 1000};

void mqe_motor ()
{

	switch(state.value)
	{
				case INICIO:
					if( state.dato == OK )
						state.value = APERTURA;
				case APERTURA:
					Iniciar_apertura();
					state.timerAperturaActive = TRUE;

					if( state.aperturaEnd )
						state.value = CERRANDO;
					break;

				case CERRANDO:

					Iniciar_cerrando();
					state.value = INICIO;

					break;

				default: state.value = APERTURA;

	}

}

void Iniciar_Timer10(void)
{
	flagTimerOn = 1;
}

void TIMER0_IRQHandler(void)
{
	if((T0IR == MR0)) // Si se venció el tiempo
	{
				T0IR |= MR0;
				flagT0 = 1;
	}
}

/*
int Timer10( void )
{
	int res = 0 ;

	if(tiempo == 0)
		res = 1;

	return res;
}
*/
