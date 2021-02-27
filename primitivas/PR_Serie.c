/**
 	\file PR_Serie.c
 	\brief Funciones de Comunicación Serie
 	\details NOTA: Falta completar con PopTx() y PushRX()!!!
 	\author
 	\date
*/

#include "PR_Serie.h"
#include "mqe.h"



// Buffer de Transmisión
uint8_t bufferTx[BUFFER_TX_SIZE];
// Buffer de Recepción
uint8_t bufferRx[BUFFER_RX_SIZE];
extern uint8_t txEnCurso;
// Índices de Transmisión
uint8_t tx_in = 0, tx_out = 0;
// Índices de Recepción
uint8_t rx_in = 0, rx_out = 0;

void PushTx(uint8_t dato)
{
	bufferTx[tx_in] = dato;
	tx_in++;
	tx_in %= BUFFER_TX_SIZE;

	if (txEnCurso == 0) {
		txEnCurso = 1;		//si no había una TX en curso,
		UART0_StartTx();	//fuerzo el inicio de la TX
	}
}

uint32_t PopRx(void)
{
	uint32_t dato = -1; // devuelvo -1 si no hay dato

	if(rx_out != rx_in) {
		// si hay un dato disponible, lo saco del bufferRx
		dato = bufferRx[rx_out];
		rx_out++;
		rx_out %= BUFFER_RX_SIZE; //lo mismo es con un if rx_out = 0
	}

	return dato;
}
