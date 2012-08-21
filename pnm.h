
enum Pictype {unknown, bw, gray, colour};

struct pic
{
  int width, height;
  Pictype type;
  unsigned int **data;
};
typedef struct pic Pic;

/* use int as R<<24 + G<<16 + B<<8 + black;
 */ 
 unsigned int red  (unsigned int x);
 unsigned int green(unsigned int x);
 unsigned int blue (unsigned int x);


Pic makenewpic (int w, int h);
Pic readpnm (const char *fname);
void writepnm(Pic p,  const char * dest);

