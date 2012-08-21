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
