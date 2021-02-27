/*
 * mqe.c
 *
 *  Created on: 24 feb. 2021
 *      Author: fer_o
 */
#include"mqe.h"
#include"PR_Serie.h"
#include"teclado.h"
#include"DR_ADC.h"

volatile State state = { INICIO, FALSE, FALSE, FALSE, 300};
uint32_t temperatura = 0;
int termino = 0;
int covid;
//extern uint32_t ADC_average;

void Aplicacion(void)
{
	static uint8_t estado = TEMPERATURA;
	//static uint8_t tecla;
	//static int cont = 0;

	switch(estado)
	{
		/*case INICIO:
			estado = TEMPERATURA;

			tecla = Teclado();
			if(tecla == KEY0)
			{
				if(cont == 0)
				{
					PushTx('#');
				}
				PushTx(tecla);
			}
			if(tecla == KEY1)
			{
				if(cont == 0)
				{
					PushTx('#');
				}
				PushTx(tecla);
			}
			if(tecla == KEY2)
			{
				if(cont == 0)
				{
					PushTx('#');
				}
				PushTx(tecla);
			}
			if(tecla == KEY3)
			{
				if(cont == 0)
				{
					PushTx('#');
				}
				PushTx(tecla);
			}
			if(tecla == KEY4)
			{
				if(cont == 0)
				{
					PushTx('#');
				}
				PushTx(tecla);
			}

			if(cont == 0)
			{
				estado = TEMPERATURA;
			}
			break;
			*/
		case TEMPERATURA:
			temperatura = temp();
			if(temperatura > 37)
			{/*
				PushTx('1');
				PushTx('$');
				estado = INICIO;*/
				covid = 1;
				estado = MOTOR;
			}
			if (temperatura < 37)
			{
				/*
				PushTx('0');
				PushTx('$');
				estado = MOTOR;
				*/
				covid = 0;
				estado = MOTOR;
			}
			break;

		case MOTOR:
			if(covid == 0)
			{
				mqe_motor();
				if (termino == 1)
					estado = TEMPERATURA;
			}
			else
			{
				if (covid == 1)
					estado = TEMPERATURA;

			}

			break;
		default: estado = INICIO;

	}

}


void mqe_motor ()
{

	switch(state.value)
	{
				case INICIO:
					//if( state.dato == OK )
					//{
					state.value = APERTURA;
					state.dato = FALSE;
					//}
					break;
				case APERTURA:
					Iniciar_apertura();
					state.timerAperturaActive = TRUE;
					state.value = INTERMEDIO;

				/*	if( state.aperturaEnd )
					{
						state.value = CERRANDO;
						state.aperturaEnd = FALSE;

					}
				*/
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
					termino = 1;
					break;

				default: state.value = INICIO;

	}

}


uint32_t temp (void)
{
	return ADC_get_average()/12;
}

