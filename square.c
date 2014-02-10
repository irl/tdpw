/**
 * tdpw - Two Dimensional Physics Workbench
 * Copyright (C) Iain R. Learmonth 2012-2014.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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

