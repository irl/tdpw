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

#include <stdio.h>
#include <math.h>

int main()
{
	int x;
	int y;

	printf("circles\n");
	printf("elastic\n");
	printf("frames 200\n");	

	for ( x = 10 ; x < 630 ; x += 50 )
		for ( y = 10 ; y < 300 ; y += 50 )
			printf("shape %d %d 10 %d %d random\n",
				x, y,
				(rand() % 6 - 3),
				(rand() % 6 - 3));
	printf("run");

}
