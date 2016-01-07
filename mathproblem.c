#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <math.h>


/*产生两个max以内的随机数，保存到x, y指向的变量*/
void rand_two_max(int *x, int *y, int max)
{
	srand( (unsigned)time( NULL ) ); 
	*x = rand() % max;
	*y = rand() % max;		
}

int main()
{
	int daoshu, max, i;
	int a, b, result, *m, *n;
	int count = 0;
	
	m = &a;
	n = &b;
	
	printf("please input daoshu:\n");
	scanf("%d",&daoshu);
	printf("please input max:\n");
	scanf("%d",&max);
	
	for(i = 0; i < daoshu; i++)
	{
		rand_two_max(m, n, max);
		printf("%d  + %d  = ", a, b);
		scanf("%d", &result);

		if(result == a + b)
		{
			count++;
			printf("V\n");
		}
		else
		{
			printf("X ");
			printf(": %d\n", a+b);
		}
	}
	
}
