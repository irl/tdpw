all:
	g++ -lreadline main.c square.c circle.c modulo.c circle.f pnm.c
	strip a.out
debug:
	g++ -ggdb -lreadline main.c square.c circle.c modulo.c circle.f pnm.c
clean:
	-rm a.out
	-rm *.ppm *.gif *.mpg
