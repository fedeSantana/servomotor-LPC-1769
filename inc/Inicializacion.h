/*
 * Inicializacion.h
 *
 *  Created on: 24 feb. 2021
 *      Author: fer_o
 */

#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define		RGBB		2,1			//GPIO2
#define		RGBR		2,2			//GPIO2
#define		RGBG		2,3			//GPIO2
#define		BUZZ		0,28		//GPIO0
#define		BUZZ_ON		0
#define		BUZZ_OFF	1


void Inicializacion(void);
void InicPLL(void);
void Init_GPIO_PWM(void);
void Init_PWM(void);
void Init_Systick(void);
void InitUART0(void);
void InitADC(void);
void SetDIR( uint8_t puerto , uint8_t pin , uint8_t dir );
void SetPIN( uint8_t puerto , uint8_t pin , uint8_t estado );
uint8_t GetPIN( uint8_t puerto , uint8_t pin , uint8_t actividad );
void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion );
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo);
void Init_EINT0(void);
void Inicializar_Teclado(void);
void inicBuzzer( void );
void inicRGB( void );
#endif /* INICIALIZACION_H_ */
