#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n,m,sum;
	for(n=1;n<=1000;n++)
	{
		sum=0;
		for(m=1;m<=n/2;m++)
			if(n%m==0)
				sum+=m;

		if(n==sum)
		{
			printf("%d its factors are",n);
			for(m=1;m<=n/2;m++)
				if(n%m==0)
					printf("%d,",m);
			printf("\b \n");
		}
	}
	return 0;
}
