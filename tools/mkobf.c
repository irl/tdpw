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

	printf("circles\nnocollide\nwrap\nframes 50\n");

	for ( x = 20 ; x < 600 ; x += ( rand() % 20 ) + 10 )
		printf("shape %d 10 %d 0 0 random\n", x, ( rand() % 10 ) + 10);

	for ( x = 20 ; x < 600 ; x += ( rand() % 20 ) + 10 )
		printf("shape %d 320 %d 0 0 random\n", x, ( rand() % 10 ) + 10);

	for ( y = 20 ; y < 320 ; y += ( rand() % 20 ) + 10 )
		printf("shape 20 %d %d 0 0 random\n", y, ( rand() % 10 ) + 10);

	for ( y = 20 ; y < 320 ; y += ( rand() % 20 ) + 10 )
                printf("shape 300 %d %d 0 0 random\n", y, ( rand() % 10 ) + 10);

        for ( y = 20 ; y < 320 ; y += ( rand() % 20 ) + 10 )
                printf("shape 590 %d %d 0 0 random\n", y, ( rand() % 10 ) + 10);

	for ( x = 10 ; x < 610 ; x += ( rand() % 20 ) + 10 )
		for ( y = 10 ; y < 330 ; y += ( rand() % 20 ) + 10 )
			printf("shape %d %d %d 2 2 random\n",
				(rand() % 630), (rand() % 300), (rand() % 20) + 10);

	printf("run");
}
