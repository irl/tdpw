all:
	g++ -lreadline main.c square.c circle.c modulo.c circle.f readpnm.c writepnm.c
	strip a.out
debug:
	g++ -ggdb -lreadline main.c square.c circle.c modulo.c circle.f readpnm.c writepnm.c
clean:
	-rm a.out
	-rm *.ppm *.gif *.mpg
