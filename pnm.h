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
void writepnm(Pic p,  const char * dest);

