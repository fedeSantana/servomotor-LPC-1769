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
volatile State state = {INICIO, FALSE, FALSE, FALSE, DELAY,0};


static int estado = INICIO;
static uint8_t tecla[5];
int tiempo_espera = 0;

void Aplicacion(void)
{
	static int i = 0;
	state.temperatura = temp();
	switch(estado)
	{
		case INICIO:
			tecla[i] = Teclado();

			if(tecla[i] == KEY1)
			{
				tecla[i] = KEY1;
				i++;
			}
			if(tecla[i] == KEY2)
			{
				tecla[i] = KEY2;
				i++;
			}
			if(tecla[i] == KEY3)
			{
				tecla[i] = KEY3;
				i++;

			}
			if(tecla[i] == KEY4)
			{
				tecla[i] = KEY4;
				i++;
			}
			if(i == 4)
			{
				estado = TEMPERATURA;
				i = 0;
			}
			break;

		case TEMPERATURA:

			if(state.temperatura > MAX_TEMPERATURA)
			{
				tecla[4] = 1;
				estado = TRAMA;

			}
			else
			{
				if(state.temperatura > MIN_TEMPERATURA)
				{
					tecla[4] = 0;
					estado = TRAMA;
				}
			}
			break;

		case TRAMA:
/*
			if (comparacion() == OK)
			{
				state.dato = OK;
				estado = MOTOR;
				tecla[0] = NO_KEY;
				tecla[1] = NO_KEY;
				tecla[2] = NO_KEY;
				tecla[3] = NO_KEY;

			}
			else
			{
				estado = INICIO;
				tecla[0] = NO_KEY;
				tecla[1] = NO_KEY;
				tecla[2] = NO_KEY;
				tecla[3] = NO_KEY;

			}
*/
			PushTx('%');
			PushTx(ascii(tecla[0]));
			PushTx(ascii(tecla[1]));
			PushTx(ascii(tecla[2]));
			PushTx(ascii(tecla[3]));
			PushTx(ascii(tecla[4]));
			PushTx('#');
			Esperar_Respuesta();
			estado = VERIFICACION;
			break;

		case VERIFICACION:
			if(Respuesta())
			{
				state.dato = PopRx();
				if (state.dato == OK || state.dato == ascii_OK)
				{
					estado = MOTOR;
					tecla[0] = NO_KEY;
					tecla[1] = NO_KEY;
					tecla[2] = NO_KEY;
					tecla[3] = NO_KEY;
				}
				else
				{
					if (state.dato == FALSE || state.dato == ascii_FALSE)
					{
						estado = INICIO;
						tecla[0] = NO_KEY;
						tecla[1] = NO_KEY;
						tecla[2] = NO_KEY;
						tecla[3] = NO_KEY;
					}
				}
			}

		case MOTOR:
			mqe_motor();
			break;

		default: estado = INICIO;

	}

}


void mqe_motor ()
{

	switch(state.value)
	{
				case INICIO:
					if(state.dato == OK || state.dato == ascii_OK)
					{
						state.value = APERTURA;
						state.dato = FALSE;
					}
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
					estado = INICIO;
					break;

				default: state.value = INICIO;

	}

}

uint32_t temp (void)
{
	return ADC_get_average()/12;
}

void Esperar_Respuesta(void)
{
	tiempo_espera = 1000;

}

int Respuesta(void)
{

	if(tiempo_espera == 0)
		return OK;

	return FALSE;

}

char ascii (uint8_t letra){
	return letra + '0';
}
