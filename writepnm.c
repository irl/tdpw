// just write the uncompressed versions

#include "pnm.h"
#include <stdio.h>
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
