/*
 * Inicializacion.c
 *
 *  Created on: 24 feb. 2021
 *      Author: fer_o
 */
#include"Inicializacion.h"
#include"Oscilador.h"
#include"PWM.h"
#include"Register_PWM.h"
#include"RegsLPC1769.h"
#include"Regs_LPC176x.h"
#include "DR_ADC.h"
#include"teclado.h"


static volatile ADC_per_t *ADC = ADC_BASE;

void Inicializacion(void)
{
	InicPLL();
	Init_GPIO_PWM();
	Init_PWM();
	Init_Systick();
	//InitUART0();
	//Init_EINT0();
	ADC_init();
	Inicializar_Teclado();

}

void Inicializar_Teclado( void )
{
	SetPINSEL ( Infotronic_KEY0 , PINSEL_GPIO);
	SetPINSEL ( Infotronic_KEY1 , PINSEL_GPIO);
	SetPINSEL ( Infotronic_KEY2 , PINSEL_GPIO);
	SetPINSEL ( Infotronic_KEY3_RC , PINSEL_GPIO);
	SetPINSEL ( Infotronic_KEY4_RC , PINSEL_GPIO);

	SetDIR ( Infotronic_KEY0 , ENTRADA);
	SetDIR ( Infotronic_KEY1 , ENTRADA);
	SetDIR ( Infotronic_KEY2 , ENTRADA);
	SetDIR ( Infotronic_KEY3_RC , ENTRADA);
	SetDIR ( Infotronic_KEY4_RC , ENTRADA);

	SetPINMODE ( Infotronic_KEY0 , PINMODE_PULLUP);
	SetPINMODE ( Infotronic_KEY1 , PINMODE_PULLUP);
	SetPINMODE ( Infotronic_KEY2 , PINMODE_PULLUP);
	SetPINMODE ( Infotronic_KEY3_RC , PINMODE_PULLUP);
}
/*
void Init_EINT0(void)
{
	SetPINSEL(2,10,1);
	ISER0 |= 0x01 << 18;
	EXTINT |= 0x01 << 0;
	EXTMODE |= 0x01 << 0;
	EXTPOLAR &= 0x01 << 0;

}
*/

void ADC_init(void)
{
	PCONP |= (1 << 12);

	// div_PCLKSEL
	PCLKSEL0 &= ~(0x03 << 24);

	ADC->ADCR.PDN = 1;

	SetPINSEL(0, 25, 1); //Leer entrada
						 //	SetPINSEL(1,31,3); //Potenciometro

	ADC->ADCR.START = 0;
	ADC->ADCR.BURST = 1;

	// f_ADC = (f_CPU / div_PCLKSEL) / ((div_ADC + 1) * 65) = 192KHz
	ADC->ADCR.CLKDIV = 1;

	ADC->ADCR.SEL = (1 << 2);

	ADC->ADINTEN.ADINTEN0 = 0;
	ADC->ADINTEN.ADINTEN1 = 0;
	ADC->ADINTEN.ADINTEN2 = 1;
	ADC->ADINTEN.ADINTEN3 = 0;
	ADC->ADINTEN.ADINTEN4 = 0;
	ADC->ADINTEN.ADINTEN5 = 0;
	ADC->ADINTEN.ADINTEN6 = 0;
	ADC->ADINTEN.ADINTEN7 = 0;
	ADC->ADINTEN.ADGINTEN = 0;

	ISER0 |= (1 << 22);
}

void InitUART0(void)
{
	//1.- Registro PCONP - bit 3 en 1 habilita la UART0
	PCONP |= 0x01<<3;
	//2.- Registro PCLKSEL0 - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea 25MHz
	PCLKSEL0 &= ~(0x03<<6);
	//3.- Registro U1LCR - trama 8 bits, 1 bit stop, sin paridad, sin break cond. (bit DLAB = 1)
	U0LCR = 0x00000083;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 9600 baudios
	U0DLM = 0;
	U0DLL = 0xA3;
	//5.- Habilito las funciones especiales de los pines TX y RX
	//TX0D : PIN ??	-> 	P0[2]
	SetPINSEL(P0, 2, PINSEL_FUNC1);
	//RX0D : PIN ??	-> 	P0[3]
	SetPINSEL(P0, 3, PINSEL_FUNC1);
	//6.- Registro U1LCR, pongo DLAB en 0
	U0LCR = 0x03;
	//7. Habilito las interrupciones de RX y TX en la UART0 (Registro U0IER)
	U0IER = 0x03;
	//8. Habilito la interrupción de la UART0 en el NVIC (Registro ISER0)
	ISER0 |= (1<<5);

}

void InicPLL(void)
{
		SCS       = SCS_Value;

		if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
			while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

		CCLKCFG   = CCLKCFG_Value;      /* Setup Clock Divider                */

		PCLKSEL0  = PCLKSEL0_Value;     /* Peripheral Clock Selection         */
		PCLKSEL1  = PCLKSEL1_Value;

		CLKSRCSEL = CLKSRCSEL_Value;    /* Select Clock Source for PLL0       */

		PLL0CFG   = PLL0CFG_Value;      /* configure PLL0                     */
		PLL0FEED  = 0xAA;
		PLL0FEED  = 0x55;

		PLL0CON   = 0x01;             /* PLL0 Enable                        */
		PLL0FEED  = 0xAA;
		PLL0FEED  = 0x55;

		while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

		PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
		PLL0FEED  = 0xAA;
		PLL0FEED  = 0x55;

		while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

		PLL1CFG   = PLL1CFG_Value;
		PLL1FEED  = 0xAA;
		PLL1FEED  = 0x55;

		PLL1CON   = 0x01;             /* PLL1 Enable                        */
		PLL1FEED  = 0xAA;
		PLL1FEED  = 0x55;

		while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

		PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
		PLL1FEED  = 0xAA;
		PLL1FEED  = 0x55;

		while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

		PCONP     = PCONP_Value;        /* Power Control for Peripherals      */

		CLKOUTCFG = CLKOUTCFG_Value;    /* Clock Output Configuration         */

		FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;

}
void Init_GPIO_PWM(void)
{
	SetPINSEL(PIN_PWM1_1_P1); //Configuro en el puerto 1, pin 18 como funcion de PWM

}
void Init_PWM(void)
{
	PCONP |= 1 << 6; //Habilitar PWM1

		// Elijo el clock completo(como tengo inicializado el PLL --> 100 Mhz)
	PCLKSEL0 &= ~(3 << 12);
	PCLKSEL0 |= 1 << 12;

	PWM_PCR = 0x00;		// Selecciono Single Edge PWM, que seria que empezar en alto la señal de PWM.

	PWM_PR = 100-1;		// para definir este valor hacemos (PCLK * PWM_Resolucion)-1 --> (100Mhz * 1uS)-1 = 100-1

	PWM_MR0 = 20000;	// 20000uS = 20mS

	PWM_MR1 = 500 ;		// 1000us = 1mS DUTTY

	PWM_MCR = 1 << 1;	// Restablecer PWM


	PWM_LER |= (0x01<<0);
	PWM_LER |=(0x01<<1);

	PWM_PCR |= (1<<9);	// Habilitar salida PWM

	PWM_TCR |= (1<<1);	// Reset PWM TC & PR

	PWM_TCR = (1<<0) | (1<<3);	// Habilitar contador y modo PWM

}
void Init_Systick( void )
{
	STRELOAD = (STCALIB/N) - 1; // 10 miliseg con PLL a 100 MHZ.
	STCTRL = 0x07;				// Clock sistema, interrupción habilitada, systick habilitado.
}
