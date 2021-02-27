/*
 * PWM_Salidas.c
 *
 *  Created on: 2 sep. 2019
 *      Author: NicoCampos
 */
#include "Regs_LPC176x.h"
#include "RegsLPC1769.h"
#include "Register_PWM.h"
#include "PWM.h"
#include "mqe.h"



//!< Funciones asociadas a las acciones

/**
*	\fn void Habilitar_juego1(void)
*	\brief Pone a 180 el servomotor.
*	\details Detalles
*	\author NicoCampos
*	\date 28-08-2019 10:09:12
*/
void Iniciar_apertura( void )
{
	//!< Codigo propio de la funcion

	PWM_MR1 = 2000;		// 2000uS = 2mS DUTTY

	// Actualizar valores de MR1
	PWM_LER|= (1<<1);	// Actualizar valores de MR1
}

/**
*	\fn void Habilitar_juego3(void)
*	\brief Resumen
*	\details Detalles
*	\author NicoCampos
*	\date 28-08-2019 10:09:12
*/
void Iniciar_cerrando( void )
{
	//!< Codigo propio de la funcion


		PWM_MR1 = 500;		// 1000uS = 1mS DUTTY

		// Actualizar valores de MR1
		PWM_LER |= (1<<1);
}



