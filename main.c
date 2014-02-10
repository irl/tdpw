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

/**
 * Defaults, may be overridden
 */
#define TYPE 0
#define WIDTH 640
#define HEIGHT 360
#define FRAMES 200
#define ELASTIC 1
#define WRAP 1
#define FREEZE 0

#include "shape.h"
#include "pnm.h"
#include "circle.h"
#include "square.h"
#include "modulo.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * Convert an ASCII representation of a colour
 * to its hex value.
 */
int strtocolour(char* colour)
{
	if ( strcmp(colour, "random") == 0 )
	{
		int r = rand() % 7;
		switch ( r )
		{
			case 0: colour = "red";
				break;
			case 1: colour = "green";
				break;
			case 2: colour = "blue";
				break;
			case 3: colour = "yellow";
				break;
			case 4: colour = "cyan";
				break;
			case 5: colour = "purple";
				break;
			case 6: colour = "white";
				break;
		}
	}

	if ( strcmp(colour, "red") == 0 )
	{
		return 0xff000000;
	}
	else if ( strcmp(colour, "green") == 0 )
	{
		return 0x00ff0000;
	}
        else if ( strcmp(colour, "blue") == 0 )
        {
                return 0x0000ff00;
        }
	else if ( strcmp(colour, "yellow") == 0 )
	{
		return 0xffff0000;
	}
	else if ( strcmp(colour, "cyan") == 0 )
	{
		return 0x00ffff00;
	}
	else if ( strcmp(colour, "purple") == 0 )
	{
		return 0xff00ff00;
	}
	else if ( strcmp(colour, "white") == 0 )
	{
		return 0xffffff00;
	}
}

/**
 * Parse the input script. This may either be interactive if a
 * tty is detected, or simply reading stdin with no prompts if
 * no tty is detected. In interactive mode, the printf statement
 * for each new frame is replaced with a nice progress bar.
 */
void parseInput(int *t, int *w, int *h, int *f, int *el, int *wr, int *fz, int *ss, Shape *s)
{
        *t = TYPE;
        *w = WIDTH;
        *h = HEIGHT;
        *f = FRAMES;
	*el = ELASTIC;
	*wr = WRAP;
	*fz = FREEZE;

	*ss = 0;

	char *input;
	char *op;
	char prompt[7];

	if ( isatty(fileno(stdin)) )
	{
		printf("Entering interactive mode:\n");
		strcpy(prompt, "tdpw> ");
	}
	else
	{
		prompt[0] = '\0';
	}

        while (1)
        {
		

		input = readline(prompt);


		if ( input == 0 || *input == 0 )
			continue;

		add_history(input);

		op = strtok(input, " ");

		if ( strcmp(op, "exit") == 0 )
		{
			exit(0);
		}

		if ( strcmp(op, "run") == 0 )
		{
			break;
		}

		if ( strcmp(op, "squares") == 0 )
		{
			*t = 0;
			continue;
		}

		if ( strcmp(op, "circles") == 0 )
		{
			*t = 1;
			continue;
		}

		if ( strcmp(op, "echo") == 0 )
		{
			op = strtok(NULL, "");
			printf("%s\n", op);
			continue;
		}

		if ( strcmp(op, "frames") == 0 )
		{
			op = strtok(NULL, " ");
			*f = atoi(op);

			continue;
		}

		if ( strcmp(op, "elastic") == 0 )
		{
			*el = 1;

			continue;
		}

		if ( strcmp(op, "inelastic") == 0 )
		{
			*el = 0;

			continue;
		}

		if ( strcmp(op, "nocollide") == 0 )
		{
			*el = 2;
			continue;
		}

		if ( strcmp(op, "freeze") == 0 )
		{
			*fz = atoi(strtok(NULL, " "));
			continue;
		}

		if ( strcmp(op, "shape") == 0 )
		{
			s[*ss].x = atoi(strtok(NULL, " "));
                        s[*ss].y = atoi(strtok(NULL, " "));
                        s[*ss].d = atoi(strtok(NULL, " "));
                        s[*ss].xv = atoi(strtok(NULL, " "));
                        s[*ss].yv = atoi(strtok(NULL, " "));
                        s[*ss].h = strtocolour(strtok(NULL, " "));	

			++*ss;

			continue;
		}

		if ( strcmp(op, "wrap") == 0 )
		{
			*wr = 0;
			continue;
		}

		if ( strcmp(op, "nowrap") == 0 )
		{
			*wr = 1;
			continue;
		}

		printf("Syntax error, please try again.\n");
	}
	
}

/**
 * Main Control
 *
 * 1) Initialise everything and get input
 * 2) Draw frames
 *   a. Draw shapes
 *   b. Do movement
 * 3) Make animated gif with gifsicle
 * 4) Launch a sane HTML viewer
 */
int main(int argc, char* argv[])
{
	//Shapes array to be populated
	Shape s[1000];

	Pic p;

	/**
	 * t: Type
	 * w: Width of image
	 * h: Height of image
	 * f: Number of frames to create in total
	 * el: Collision type (0: inelastic, 1: elastic, 2: none)
	 * ss: Total number of shapes
	 * wr: Wrap around edges (0: true, 1: false)
	 * fz: Number of frames before movement begins
	 */
	int t, w, h, f, el, ss, wr, fz;

	/**
	 * Loop Counters
	 * i, j: Shape indexes
	 * cf: Current frame
	 * e: Progress bar drawing
	 */
	int i, j, cf, e;

	struct winsize tty;

	//Function pointers
	int (*cd)(Shape, Shape);
	void (*ds)(Pic, int, int, int, int);

	parseInput(&t, &w, &h, &f, &el, &wr, &fz, &ss, s);

	switch ( t )
	{
		case 0: cd = &squareCollisionDetect;
			ds = &square;
			break;
		case 1: cd = &circleCollisionDetect;
			ds = &circle;
			break;
	}

	printf("Creating frames...\n");

	for ( cf = 0; cf < f ; ++cf )
	{
		char ppmname[30], gifname[30], cmd[100];

		p = makenewpic(w, h);
		p.type = colour;

		//Draw background
		rect(p, 0, 0, w, h, 0x00000000 );

		//Draw shapes
		for ( i = 0 ; i < ss ; ++i )
                {
                        ds(p, s[i].x, s[i].y, s[i].d, s[i].h);
		}

		//If movement has begun, do movement
		if ( cf > fz )
		{

		for ( i = 0 ; i < ss ; ++i )
		{
			for ( j = i + 1 ; j < ss ; ++j )
			{
				if ( cd(s[i], s[j]) && el == 1 )
				{
					s[i].xv ^= s[j].xv;
					s[j].xv ^= s[i].xv;
					s[i].xv ^= s[j].xv;

					s[i].yv ^= s[j].yv;
					s[j].yv ^= s[i].yv;
					s[i].yv ^= s[j].yv;
				}

				if ( cd(s[i], s[j]) && el == 0 )
				{
					s[i].xv = s[j].xv = ( s[i].xv + s[j].xv ) / 2;
					s[i].yv = s[j].yv = ( s[i].yv + s[j].yv ) / 2;
				}
			}
		}

		for ( i = 0 ; i < ss ; ++i )
		{

			s[i].x += s[i].xv;
			s[i].y += s[i].yv;

			if ( wr )
			{
				if ( s[i].x + s[i].d >= w )
				{
					s[i].xv *= -1;
					s[i].x = w - s[i].d - 1;
				}
				else if ( s[i].x < 0 )
				{
					s[i].xv *= -1;
					s[i].x = 0;
				}

				if ( s[i].y + s[i].d >= h )
				{
					s[i].yv *= -1;
					s[i].y = h - s[i].d - 1;
				}
				else if ( s[i].y < 0 )
				{
					s[i].yv *= -1;
					s[i].y = 0;
				}
			} else {
				s[i].x = modulo(s[i].x, w);
				s[i].y = modulo(s[i].y, h);
			}
		}

		}

		sprintf(ppmname,"_%03d.ppm",cf);
		sprintf(gifname,"_%03d.gif",cf);

		//Write image files
		writepnm(p, ppmname);

		sprintf(cmd,"ppmtogif %s 2>/dev/null > %s", ppmname, gifname);

		system(cmd);

		if ( isatty(fileno(stdin)) )
		{
			ioctl(0, TIOCGWINSZ, &tty);
	
			putchar('[');
	
			for ( e = 0 ; e < ( ( ( ( cf + 1 ) * 100 ) / f ) * ( tty.ws_col - 12 ) / 100 ) ; ++e )
				putchar('=');
	
			putchar('>');
	
			for ( e = 0 ; e < ( tty.ws_col - 12 ) - ( ( ( ( cf + 1 ) * 100 ) / f ) * ( tty.ws_col - 12 ) / 100 ) ; ++e )
				putchar(' ');
	
			putchar(']');
	
			printf("  %3d/%3d\r", cf + 1, f);
	
			fflush(stdout);
		}
		else
		{
			printf("Creating frame %3d of %3d...\n", cf + 1, f);
		}
	}

	if ( isatty(fileno(stdin)) )
	{
		for ( e = 0 ; e < tty.ws_col ; e ++ )
			putchar(' ');
		
		putchar('\r');
	}
	
	printf("Creating animated GIF...\n");

	system("gifsicle _*.gif > anim.gif");

	printf("Cleaning up...\n");

	system("rm -f _*.ppm _*.gif");

}

