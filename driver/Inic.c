

#include "Oscilador.h"
#include "Inicializacion.h"
#include "Register_PWM.h"
#include "PWM.h"
#include "DR_Systick.h"



void inicializacion( void )
{

	InicPLL();
	Init_GPIO_PWM();
	Init_PWM();
	Init_Systick();
	Init_EINT0();

}


void Init_Systick( void )
{
	STRELOAD = (STCALIB/N) - 1; // 1 miliseg con PLL a 100 MHZ.
	STCTRL = 0x07;				// Clock sistema, interrupción habilitada, systick habilitado.
}
void Init_EINT0(void)
{
	SetPINSEL(2,10,1);
	ISER0 |= 1<<18;
	EXTINT |= 1<<0;
	EXTMODE |= 1<<0;
	EXTPOLAR &= 0<<0;

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

	PWM_MR1 = 500;		// 500uS = 5mS DUTTY

	PWM_MCR = 1 << 1;	// Restablecer PWM


	PWM_LER |= (0x01<<0);
	PWM_LER |=(0x01<<1);

	PWM_PCR |= (1<<9);	// Habilitar salida PWM

	PWM_TCR |= (1<<1);	// Reset PWM TC & PR

	PWM_TCR = (1<<0) | (1<<3);	// Habilitar contador y modo PWM
}


