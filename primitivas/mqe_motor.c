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
#include "DR_ADC.h"
#define FIN 9

//!< Definición de Funciones


//!< Definición de variables
volatile State state = { INICIO, FALSE, FALSE, FALSE, 300, 0};

void mqe_motor ()
{
	state.temperatura = temp();


	switch(state.value)
	{
		case INICIO:
			if( state.temperatura!=0)
			{
				state.value= FIN;
			}
			break;
		case FIN:
			state.value = INICIO;
	}

	/*
	}
				case INICIO:
					if( state.dato == OK )
					{
						state.value = APERTURA;
						state.dato = FALSE;
					}
					break;
				case APERTURA:
					Iniciar_apertura();
					state.timerAperturaActive = TRUE;
					state.value = INTERMEDIO;

					if( state.aperturaEnd )
					{
						state.value = CERRANDO;
						state.aperturaEnd = FALSE;

					}

					break;
				case INTERMEDIO:
					if(state.aperturaEnd)
					{
						state.value = CERRANDO;
						state.aperturaEnd = FALSE;
					}
					break;
				case CERRANDO:

					Iniciar_cerrando();
					state.value = INICIO;

					break;

				default: state.value = INICIO;*/
}

uint32_t temp (void)
{
	return ADC_get_average()/12;

}


