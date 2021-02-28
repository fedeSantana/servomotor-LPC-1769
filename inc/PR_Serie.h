/*
 * PR_Serie.h
 *
 *  Created on:
 *      Author:
 */

#ifndef PR_SERIE_H_
#define PR_SERIE_H_

#include "Regs_LPC176x.h"


void PushTx(uint8_t dato);
uint32_t PopRx(void);

//NOTA: Falta completar con PopTx() y PushRX()!!!

#endif /* PR_SERIE_H_ */
