
#include "pnm.h"
#include "stdlib.h"
#include "shape.h"
#include "modulo.h"

/**
 * Draw a rectangle within a picture.
 */
void rect( Pic p, int x0, int y0, int xm, int ym, int hue )
{
        int x, y;

        for ( y = y0; y < y0+ym; y++)
                for (x = x0 ; x < x0+xm ; x++)
                        p.data[modulo(x, p.width)][modulo(y, p.height)] = hue;
}

/**
 * Draw a square within a picture.
 */
void square( Pic p, int x0, int y0, int d, int hue )
{
	rect( p, x0, y0, d, d, hue );
}

int squareCollisionDetect( Shape s1, Shape s2 )
{
	if ( abs( s1.x - s2.x ) < s1.d
		&& abs( s1.y - s2.y ) < s1.d )
	{
		return 1;
	} else {
		return 0;
	}
}

