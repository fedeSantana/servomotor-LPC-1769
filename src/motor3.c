/*
===============================================================================
 Name        : motor3.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "Inicializacion.h"
#include "mqe.h"


int main(void) {

	inicializacion();

    while(1)
    {
    	mqe_motor();

    }
    return 0 ;
}
