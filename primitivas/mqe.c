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
	static int i = 1;
	state.temperatura = temp();
	switch(estado)
	{
		case INICIO:
			tecla[i] = Teclado();

			if(tecla[i] == KEY1)
			{
				tecla[i] = KEY1;
				i++;
				Amarillo();

			}
			if(tecla[i] == KEY2)
			{
				tecla[i] = KEY2;
				i++;
				Azul();

			}
			if(tecla[i] == KEY3)
			{
				tecla[i] = KEY3;
				i++;
				Magenta();

			}
			if(tecla[i] == KEY4)
			{
				tecla[i] = KEY4;
				i++;
				Cian();
			}
			if(i == 5)
			{
				estado = TEMPERATURA;
				i = 0;
				RGBG_ON;
				RGBR_OFF;
				RGBB_OFF;
			}
			break;

		case TEMPERATURA:

			if(state.temperatura > MAX_TEMPERATURA)
			{
				tecla[0] = 1;
				estado = TRAMA;

			}
			else
			{
				if(state.temperatura > MIN_TEMPERATURA)
				{
					tecla[0] = 0;
					estado = TRAMA;
				}
			}
			break;

		case TRAMA:

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
				if (PopRx() == '%')
				{
					state.dato = PopRx();

					if(PopRx() == '#')
					{
						if (state.dato == OK || state.dato == ascii_OK)
						{
							estado = MOTOR;
							tecla[1] = NO_KEY;
							tecla[2] = NO_KEY;
							tecla[3] = NO_KEY;
							tecla[4] = NO_KEY;
						}
						else
						{
							if (state.dato == FALSE || state.dato == ascii_FALSE)
							{
								estado = INICIO;
								tecla[1] = NO_KEY;
								tecla[2] = NO_KEY;
								tecla[3] = NO_KEY;
								tecla[4] = NO_KEY;
							}
						}
					}
				}
			}
			break;

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
					RGBG_OFF;
					RGBR_ON;
					state.value = INTERMEDIO;
					PushTx('%');
					PushTx('A');
					PushTx('#');
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
					RGBG_ON;
					RGBR_OFF;
					state.value = INICIO;
					estado = INICIO;
					PushTx('%');
					PushTx('C');
					PushTx('#');
					break;

				default: state.value = INICIO;

	}

}

void Cian (void)
{
	RGBG_OFF;
	RGBR_ON;
	RGBB_ON;

}

void Magenta(void)
{
	RGBG_ON;
	RGBR_OFF;
	RGBB_ON;

}

void Amarillo(void)
{
	RGBG_ON;
	RGBR_ON;
	RGBB_OFF;
}

void Azul(void)
{
	RGBG_OFF;
	RGBR_OFF;
	RGBB_ON;

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
