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

