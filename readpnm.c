/* read ppm file into array
 *
 * see man ppm for format
 *
 * this reads chars type pgm or pbm
 *
 * P1 = pbm chars
 * P2 = pgm chars
 * P3 = ppm chars - colour
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "pnm.h"

/* use int as R<<24 + G<<16 + B<<8 + black;
 */ 
 unsigned int red  (unsigned int x){ return (x>>24) & 0xff;}
 unsigned int green(unsigned int x){ return (x>>16) & 0xff;}
 unsigned int blue (unsigned int x){ return (x>> 8) & 0xff;}

int
fgetnc (FILE * src)
/* get a character from src after stripping comments */
{
  int res = fgetc (src);
  if (res == '#')		// # .. eol = comment
    while (!feof (src) && res != '\n')
      res = fgetc (src);
  return res;
}

int
getintval (FILE * src)
/* get an integer from src after stripping comments */
{
  int c;
  while (isspace (c = fgetnc (src)))
    ;
  assert (isdigit (c));
  int res = c - '0';
  while (isdigit (c = fgetnc (src)))
    res = 10 * res + c - '0';
  return res;
}

Pic
makenewpic (int w, int h)
{
  Pic res;
  int x;
  res.width = w;
  res.height = h;
  res.data = (unsigned int **) malloc (sizeof (unsigned int *) * res.width);
  for (x = 0; x < res.width; x++)
    res.data[x]=(unsigned int *)malloc(sizeof(unsigned int) * res.height);
  return res;
}

void
readpbm_char (FILE * src, Pic * p)	// p bit m, as chars
{
  int x, y;
  for (y = 0; y < p->height; y++)
    for (x = 0; x < p->width; x++)
      {
	fscanf (src, " %1d", &(p->data[x][y]));
      }
}

void readpbm_byte(FILE * src, Pic *p)
{
  int x,y,j, nwide = 1+(p->width-1)/8;
  for (y = 0; y < p->height; y++)
    for (x = 0; x < nwide; x++)
      {
	int b = fgetc(src);
	for ( j =0 ; j < 8 ; j++){
	  if ( x*8+j < p->width)
	    p->data[x*8+j][y] = (b & 0x80)?1:0 ;
	  b <<= 1;
	}
      }
}

void
readpgm_char (FILE * src, Pic * p)	// p grey m, as chars
{
  int x, y;
  for (y = 0; y < p->height; y++)
    for (x = 0; x < p->width; x++)
      {
	fscanf (src, " %d", &(p->data[x][y]));
      }
}

void
readpgm_byte (FILE * src, Pic * p)	// p grey m, as bytes
{
  int x, y;
  for (y = 0; y < p->height; y++)
    for (x = 0; x < p->width; x++)
      {
	(p->data[x][y]) = fgetc (src);
      }
}

void
readppm_char (FILE * src, Pic * p)	// p colour m, as chars
{
  int x, y;
  for (y = 0; y < p->height; y++)
    for (x = 0; x < p->width; x++)
      {
			unsigned int r,g,b;
			fscanf (src, " %d", &r);
			fscanf (src, " %d", &g);
			fscanf (src, " %d", &b);
			p->data[x][y] = (r<<24) + (g<<16) + (b<<8);
      }
}

void
readppm_byte (FILE * src, Pic * p)	// p colour m, as bytes
{
  int x, y;
  for (y = 0; y < p->height; y++)
    for (x = 0; x < p->width; x++)
      {
			unsigned int r,g,b;
			r = fgetc(src) & 0xff;
			g = fgetc(src) & 0xff;
			b = fgetc(src) & 0xff;
			p->data[x][y] = (r<<24) + (g<<16) + (b<<8);
      }
}



Pic
readpnm (const char *fname)
/* read a ppm file (as generated by convert) into an Pic */
{
  Pic p;
  int ww, hh, maxvals, x, y, ch;
  FILE *src = fopen (fname, "rb");
  assert (fgetc (src) == 'P');
  ch = fgetc (src);
  ww = getintval (src);
  hh = getintval (src);
  if (ch != '1' && ch != '4') {
  	maxvals = getintval (src);
  	assert (maxvals < 256);
  }
  p = makenewpic (ww, hh);
  //fprintf(stderr, " hh = %d, ww = %d, ch = %c\n", hh,ww,ch);
  switch (ch)
    {
    case '1':  readpbm_char (src, &p); p.type = bw;     break;
    case '2':  readpgm_char (src, &p); p.type = gray;   break;
    case '3':  readppm_char (src, &p); p.type = colour; break;
    case '4':  readpbm_byte (src, &p); p.type = bw;     break;
    case '5':  readpgm_byte (src, &p); p.type = gray;   break;
    case '6':  readppm_byte (src, &p); p.type = colour; break;
    }
  fclose (src);
  return p;
}
