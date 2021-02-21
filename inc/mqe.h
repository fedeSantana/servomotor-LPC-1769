/*
 * mqe.h
 *
 *  Created on: 12 dic. 2020
 *      Author: fer_o
 */

#ifndef MQE_H_
#define MQE_H_

#endif /* MQE_H_ */
void mqe_motor (void);
void Iniciar_apertura( void );
void Iniciar_cerrando( void );
int timerOver();
void Iniciar_Timer10(void);

#define	OK				1
#define	FALSE			0
#define TRUE            1
#define	DIEZ		10000

//!< Definicion de Estados
#define	APERTURA		0
#define	CERRANDO		1
#define	INICIO			2
#define DELAY			1000

typedef struct State {
   int value; // Valor del estado
   int dato; // Valor del dato, viene de QT
   int aperturaEnd; // Variable que define si terminó de abrir
   int timerAperturaActive; // Activador del timer
   int counter; // segundos que iran disminuyendo hassta
} State;
