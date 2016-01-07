#include <stdio.h>

int ABS(int x)
{
	if(x < 0)
		return (-x);
	else
		return x;
}

int main()
{
	int i, j, m, n;

		for(i = -3; i <= 3; i++)
		{
			for(j = -3; j <= 3; j++)
			{
				m = ABS(i);
				n = ABS(j);

				if(m < n)
				{
					printf("   ");
				}
				else
				{
					printf(" * ");
				}
			}
			printf("\n");
		}
}