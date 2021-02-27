/*
 * mqe.h
 *
 *  Created on: 24 feb. 2021
 *      Author: fer_o
 */
#include"RegsLPC1769.h"

#ifndef MQE_H_
#define MQE_H_

#define BUFFER_TX_SIZE	32
#define BUFFER_RX_SIZE	32

#define	OK				1
#define	FALSE			0
#define TRUE            1
#define	DIEZ		10000
#define NO_KEY		255

//!< Definicion de Estados
#define	APERTURA		0
#define	CERRANDO		1
#define	INICIO			2
#define	INTERMEDIO		3
#define	TEMPERATURA		4
#define	MOTOR			5
#define DELAY			1000
#define START_TX()	(PopTx((uint8_t*)&U0THR))

void Aplicacion(void);
void UART0_StartTx(void);
void mqe_motor (void);
void Iniciar_apertura( void );
void Iniciar_cerrando( void );
uint8_t Teclado( void );
//uint32_t temp(void);


typedef struct State {
   int value; // Valor del estado
   int dato; // Valor del dato, viene de QT
   int aperturaEnd; // Variable que define si terminó de abrir
   int timerAperturaActive; // Activador del timer
   int counter; // segundos que iran disminuyendo hassta
} State;

#endif /* MQE_H_ */
