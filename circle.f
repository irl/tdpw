C tdpw - Two Dimensional Physics Workbench
C Copyright (C) Iain R. Learmonth 2012-2014.

C This program is free software; you can redistribute it and/or modify
C it under the terms of the GNU General Public License as published by
C the Free Software Foundation; either version 2 of the License, or
C (at your option) any later version.
C
C This program is distributed in the hope that it will be useful,
C but WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
C GNU General Public License for more details.
C
C You should have received a copy of the GNU General Public License along
C with this program; if not, write to the Free Software Foundation, Inc.,
C 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

C Does the circle maths

      INTEGER FUNCTION INCIRC(X,Y,R)
      INTEGER X,Y,R,H
      H = INT(SQRT(REAL((X-R)**2+(Y-R)**2)))
      IF ( H < R ) THEN
      INCIRC = 0
      ELSE
      INCIRC = 1
      END IF
      RETURN

      END
