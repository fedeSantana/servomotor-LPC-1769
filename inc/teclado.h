/*
 * teclado.h
 *
 *  Created on: 24 feb. 2021
 *      Author: fer_o
 */

#ifndef TECLADO_H_
#define TECLADO_H_
#include "Inicializacion.h"

#define NO_KEY 255
#define KEY0 0
#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4

#define 	IDLE	0
#define 	DETECCION	1
#define 	CHEQUEO	2
#define MAX_REBOTES 200
#define		ACTIVO_BAJO		0
#define		ACTIVO_ALTO		1

#define		Infotronic_KEY0		2,10
#define		Infotronic_KEY1		0,18
#define		Infotronic_KEY2		0,11
#define		Infotronic_KEY3_RC	2,13
#define		Infotronic_KEY4_RC	1,26

#define KEY0_ACTIVO_BAJO   GetPIN(Infotronic_KEY0,ACTIVO_BAJO)
#define KEY1_ACTIVO_BAJO   GetPIN(Infotronic_KEY1,ACTIVO_BAJO)
#define KEY2_ACTIVO_BAJO   GetPIN(Infotronic_KEY2,ACTIVO_BAJO)
#define KEY3_ACTIVO_BAJO   GetPIN(Infotronic_KEY3_RC,ACTIVO_BAJO)
#define KEY4_ACTIVO_BAJO   GetPIN(Infotronic_KEY4_RC,ACTIVO_BAJO)

void tecladoSW(uint8_t codigoActual);
void DriverTeclado(void);
uint8_t TecladoHW (void);


#endif /* TECLADO_H_ */
