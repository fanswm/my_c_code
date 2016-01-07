#include <conio.h>
#include <stdio.h>
#include <time.h> 
#include <math.h>

int get_rand_under_max(int max)
{
	int x;
	srand( (unsigned)time( NULL ) ); 
	x = rand() % max;
	return x;	
}
