#include "mqe.h"
#include "RegsLPC1769.h"
uint8_t buffKey = NO_KEY;
uint8_t Teclado( void )
{
	uint8_t tecla = NO_KEY;

	if (buffKey != NO_KEY )
	{
		tecla = buffKey;
		buffKey = NO_KEY;
	}
	return tecla;
}
