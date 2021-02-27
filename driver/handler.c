/*
 * handler.c
 *
 *  Created on: 24 feb. 2021
 *      Author: fer_o
 */

#include "mqe.h"
#include "DR_ADC.h"
#include "Regs_LPC176x.h"
#include "RegsLPC1769.h"

#define MAX_MUESTRA 4095
#define BUFFER_TX_SIZE	32
#define BUFFER_RX_SIZE	32
static volatile ADC_per_t *ADC = ADC_BASE;
static volatile uint32_t ADC_buffer[4095];
static volatile uint32_t ADC_buffer_index = 0;
static  uint32_t ADC_average = 0;

int muestras = 4096;
uint8_t txEnCurso;
extern State state;
extern uint8_t tx_in, tx_out;
// Índices de Recepción
extern uint8_t rx_in, rx_out;
// Buffer de Transmisión
extern uint8_t bufferTx[BUFFER_TX_SIZE];
// Buffer de Recepción
extern uint8_t bufferRx[BUFFER_RX_SIZE];

void SysTick_Handler(void)
{
	if (state.timerAperturaActive == TRUE){
		state.counter--;
		if ((state.counter == 0) && (state.aperturaEnd == FALSE))
		{
			state.aperturaEnd = TRUE;
			state.timerAperturaActive = FALSE;
			state.counter = 300;
		}
		else {
		// No deberia entrar aca
		}
	}
	void DriverTeclado(void);
}

void ADC_IRQHandler(void)
{
	static uint32_t acummulator = 0;

	ADDR_reg_t ADDR2 = ADC->ADDR[2];

	ADC_buffer[ADC_buffer_index] = ADDR2.RESULT;
	acummulator += ADC_buffer[ADC_buffer_index];

	ADC_buffer_index++;
	ADC_buffer_index %= MAX_MUESTRA;

	if(!ADC_buffer_index)
	{
		ADC_average = acummulator / MAX_MUESTRA;
		acummulator = 0;
	}
}

uint32_t ADC_get_average(void)
{
	return ADC_average;
}

void UART0_IRQHandler (void)
{
	uint8_t iir, dato;

	do {
		//Para limpiar los flags de IIR hay que leerlo, una vez que lo leí se resetea.
		iir = U0IIR;
		//THRE (Interrupción por TX)
		if (iir & 0x02) {
			if(tx_out != tx_in) {
				// hay un dato en el bufferTx para enviar <- reemplazar por PopTx()!!!
				dato = bufferTx[tx_out];
				tx_out++;
				tx_out %= BUFFER_TX_SIZE;
				// transmito el dato
				U0THR = dato;
			}
			else {
				// si no hay más datos a enviar, limpio el flag
				txEnCurso = 0;
			}
		}
		//Data Ready (Interrupción por RX)
		if ( iir & 0x04 ) {
			// guardo el dato recibido en el bufferRx <- reemplazar por PushRx()!!!
			dato = U0RBR;
			bufferRx[rx_in] = dato;
			rx_in++;
			rx_in %= BUFFER_RX_SIZE;
		}
	} while(!(iir & 0x01));	/* me fijo si cuando entre a la ISR habia otra
						    int. pendiente de atencion: b0=0 */
}

void UART0_StartTx(void)
{
	uint8_t dato;

	dato = bufferTx[tx_out];
	tx_out++;
	tx_out %= BUFFER_TX_SIZE;
	// transmito el dato
	U0THR = dato;
}
