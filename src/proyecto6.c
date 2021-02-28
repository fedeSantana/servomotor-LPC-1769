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
#include"mqe.h"


int main(void)
{
	Inicializacion();


    while(1)
    {
    	Aplicacion();

    }
    return 0 ;
}
