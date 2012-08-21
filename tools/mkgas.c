
#include <stdio.h>
#include <math.h>

int main()
{
	int x;
	int y;

	printf("circles\n");
	printf("elastic\n");
	printf("frames 200\n");	

	for ( x = 10 ; x < 630 ; x += 50 )
		for ( y = 10 ; y < 300 ; y += 50 )
			printf("shape %d %d 10 %d %d random\n",
				x, y,
				(rand() % 6 - 3),
				(rand() % 6 - 3));
	printf("run");

}
