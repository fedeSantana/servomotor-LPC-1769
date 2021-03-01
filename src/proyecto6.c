/*
===============================================================================
 Name        : proyecto6.c
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
#include"Inicializacion.h"
#include"PR_Serie.h"
#include"mqe.h"


int main(void)
{

	Inicializacion();
	PushTx('h');
	PushTx('o');
	PushTx('l');
	PushTx('a');


    while(1)
    {
    	Aplicacion();

    }
    return 0 ;
}
