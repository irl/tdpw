
#include <stdio.h>
#include <math.h>

int main()
{
	int x;
	int y;

	printf("circles\nnocollide\nwrap\nframes 50\n");

	for ( x = 20 ; x < 600 ; x += ( rand() % 20 ) + 10 )
		printf("shape %d 10 %d 0 0 random\n", x, ( rand() % 10 ) + 10);

	for ( x = 20 ; x < 600 ; x += ( rand() % 20 ) + 10 )
		printf("shape %d 320 %d 0 0 random\n", x, ( rand() % 10 ) + 10);

	for ( y = 20 ; y < 320 ; y += ( rand() % 20 ) + 10 )
		printf("shape 20 %d %d 0 0 random\n", y, ( rand() % 10 ) + 10);

	for ( y = 20 ; y < 320 ; y += ( rand() % 20 ) + 10 )
                printf("shape 300 %d %d 0 0 random\n", y, ( rand() % 10 ) + 10);

        for ( y = 20 ; y < 320 ; y += ( rand() % 20 ) + 10 )
                printf("shape 590 %d %d 0 0 random\n", y, ( rand() % 10 ) + 10);

	for ( x = 10 ; x < 610 ; x += ( rand() % 20 ) + 10 ) 
		for ( y = 10 ; y < 330 ; y += ( rand() % 20 ) + 10 ) 
			printf("shape %d %d %d 2 2 random\n",
				(rand() % 630), (rand() % 300), (rand() % 20) + 10);

	printf("run");
}
