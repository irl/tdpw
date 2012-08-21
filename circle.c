
#include <math.h>

#include "pnm.h"
#include "shape.h"
#include "circle.h"
#include "modulo.h"

int circleCollisionDetect( Shape s1, Shape s2 )
{
	int d;

	d = sqrt( pow((s1.x - s2.x),2) + pow((s1.y - s2.y),2) );

	if ( d < s1.d )
		return 1;
	else
		return 0;
}

void circle( Pic p, int x0, int y0, int d, int hue )
{
        int x, y;

        for ( y = y0 ; y < y0 + ( d ) ; y++ )
                for ( x = x0 ; x < x0 + ( d ) ; x++ )
                        if ( incirc_( x - x0, y - y0, (d/2) ) == 0 )
                                p.data[modulo(x,p.width)][modulo(y,p.height)] = hue;
}

