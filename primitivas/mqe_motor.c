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
#define	OK				1
#define	FALSE			0
#define	DIEZ		10000

//!< Definicion de Estados
#define	APERTURA		0
#define	CERRANDO		1
#define	INICIO			2
#define DELAY			1000

uint8_t dato = OK;
int tiempo = DELAY;
int flagTimerOver = 0;
int flagTimerOn = 0;
volatile int flagT0;

void TIMER0_IRQHandler(void);

void mqe_motor ()
{
	static int estado = INICIO;

	switch(estado)
	{
				case INICIO:
					if( dato == OK)
						estado = APERTURA;
				case APERTURA:

					Iniciar_apertura();
					Iniciar_Timer10();
					if(flagT0 == 1)
						estado = CERRANDO;
					break;

				case CERRANDO:

					Iniciar_cerrando();
					estado = INICIO;

					break;

				default: estado = APERTURA;

	}

}

void Iniciar_Timer10(void)
{
	flagTimerOn = 1;
}

int timerOver()
{
	if(flagTimerOver == 1)
	{
		flagTimerOver = 0;
		flagTimerOn = 0;
		tiempo = DELAY;
		return 1;
	}
	else
	{
		return 0;
	}
}
void TIMER0_IRQHandler(void)
{
	if((T0IR == MR0))
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
