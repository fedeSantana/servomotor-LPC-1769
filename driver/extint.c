#include "RegsLPC1769.h"
#include "mqe.h"
extern State state;
void EINT0_IRQHandler(void)
{
	EXTINT |= 0x1 << 0; // Limpio el flag de la EINT0 escribiendo un UNO.
	state.dato = 1;
}

