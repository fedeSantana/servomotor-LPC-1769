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

#define OK 1
#define	ascii_OK		'1'
#define ascii_FALSE     '0'
#define	FALSE			0
#define TRUE            1
#define	DIEZ		10000
#define NO_KEY		255
#define MAX_TEMPERATURA 37
#define MIN_TEMPERATURA 0



//!< Definicion de Estados
#define	APERTURA		0
#define	CERRANDO		1
#define	INICIO			2
#define	INTERMEDIO		3
#define	TEMPERATURA		4
#define	MOTOR			5
#define DELAY			1000
#define START_TX()	(PopTx((uint8_t*)&U0THR))
#define NO_ABRIR 6
#define	TRAMA			7
#define VERIFICACION 8
#define ON 1
#define OFF 0

#define BUZZER_OFF		SetPIN(BUZZ,BUZZ_OFF)
#define BUZZER_ON		SetPIN(BUZZ,BUZZ_ON)

#define RGBR_ON 	SetPIN(RGBR,ON)
#define RGBR_OFF 	SetPIN(RGBR,OFF)
#define RGBG_ON 	SetPIN(RGBG,ON)
#define RGBG_OFF 	SetPIN(RGBG,OFF)
#define RGBB_ON 	SetPIN(RGBB,ON)
#define RGBB_OFF 	SetPIN(RGBB,OFF)

void Amarillo(void);
void Cian (void);
void Magenta(void);
void Azul(void);
void Aplicacion(void);
void UART0_StartTx(void);
void mqe_motor (void);
void Iniciar_apertura( void );
void Iniciar_cerrando( void );
uint8_t Teclado( void );
uint32_t temp(void);
char ascii (uint8_t letra);
int comparacion(void);
void Esperar_Respuesta(void);
int Respuesta(void);

typedef struct State {
   int value; // Valor del estado
   uint8_t dato; // Valor del dato, viene de QT
   int aperturaEnd; // Variable que define si terminó de abrir
   int timerAperturaActive; // Activador del timer
   int counter; // segundos que iran disminuyendo hassta
   uint32_t temperatura;
} State;

#endif /* MQE_H_ */
