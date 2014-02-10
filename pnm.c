#include "pnm.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int red  (unsigned int x){ return (x>>24) & 0xff;}
unsigned int green(unsigned int x){ return (x>>16) & 0xff;}
unsigned int blue (unsigned int x){ return (x>> 8) & 0xff;}

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

void writepbm( Pic p, FILE *dst)
{
    int x, y;
    fprintf(dst,"P1\n%d %d\n", p.width, p.height);
    for ( y = 0 ; y < p.height ; y++){
        for ( x = 0 ; x < p.width ; x++)
            fprintf(dst,"%1d", p.data[x][y]);
        fprintf(dst,"\n");
        }
}

void writepgm( Pic p, FILE *dst)
{
    int x, y;
    fprintf(dst,"P2\n%d %d\n255\n", p.width, p.height);
    for ( y = 0 ; y < p.height ; y++){
        for ( x = 0 ; x < p.width ; x++)
            fprintf(dst," %d", p.data[x][y]);
        fprintf(dst,"\n");
        }
}

void writeppm( Pic p, FILE *dst)
{
    int x, y;
    fprintf(dst,"P3\n%d %d\n255\n", p.width, p.height);
    for ( y = 0 ; y < p.height ; y++){
        for ( x = 0 ; x < p.width ; x++){
          int hue = p.data[x][y];
          fprintf(dst," %d", red(hue));
          fprintf(dst," %d", green(hue));
          fprintf(dst," %d", blue(hue));
           }
        fprintf(dst,"\n");
        }
}

void writepnm(Pic p,  const char * dest)
{
  FILE * dst = (dest) ? fopen(dest, "w") : stdout ;
  switch(p.type){
    case bw:     writepbm(p, dst); break;
    case gray:   writepgm(p, dst); break;
    case colour: writeppm(p, dst); break;
  }
  if (dest) fclose(dst);
}

