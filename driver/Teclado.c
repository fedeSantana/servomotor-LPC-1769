/**
*	\file Teclado.c
*	\brief Todas las funciones necesarias para el teclado del Infotronic
*	\details
*	\author FedericoBua
*	\date 08-09-2018 22:58:22
*/
#include "teclado.h"
#include "Inicializacion.h"


void DriverTeclado(void)
{
	uint8_t CodigoActual ;
	CodigoActual = TecladoHW( );
	tecladoSW( CodigoActual );
}


uint8_t TecladoHW (void)
{
	uint8_t Codigo = NO_KEY;

	if (KEY0_ACTIVO_BAJO) return 0;
	if (KEY1_ACTIVO_BAJO) return 1;
	if (KEY2_ACTIVO_BAJO) return 2;
	if (KEY3_ACTIVO_BAJO) return 3;
	if (KEY4_ACTIVO_BAJO) return 4;
    return Codigo;
}





//Implementacion Switch-Case

/**
*	\fn tecladoSW()
*	\brief Implementacion Switch-Case
*	\details
*	\author FedericoBua
*	\date 08-09-2018 22:58:22
*/
extern uint8_t buffKey;

void tecladoSW(uint8_t codigoActual)
{

		static uint8_t codigoAnterior=NO_KEY;
		static uint8_t contador=0; //Máximo 50
		static int estado = IDLE;

		switch(estado)
		{
			case IDLE:

				if(codigoActual!=NO_KEY)
				{
					codigoAnterior=codigoActual;
					estado = DETECCION;

				}
				if(codigoActual==NO_KEY)
				{

					estado = IDLE;

				}

				break;

			case DETECCION:

				if(codigoActual!=codigoAnterior)
				{

					estado = IDLE;

				}
				if(codigoActual==codigoAnterior)
				{
					contador=MAX_REBOTES;
					estado = CHEQUEO;

				}

				break;

			case CHEQUEO:

				if(codigoActual!=codigoAnterior)
				{
					codigoActual=codigoAnterior;
					estado = DETECCION;

				}
				if(codigoActual==codigoAnterior)
				{
					contador--;
					estado = CHEQUEO;

				}
				if(contador==0)
				{
					buffKey=codigoActual;
					estado = IDLE;
				}
				break;
			default: estado = IDLE;
		}
}

