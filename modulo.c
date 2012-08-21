
#include <stdlib.h>

int modulo(int x, int y)
{
	if ( x >= 0 )
		return ( x % y );
	else
		return ( y - ( abs(x) % y ) );
}

