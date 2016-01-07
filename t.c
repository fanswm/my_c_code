#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void swap_item_strarray(char (*from_format_name_sign)[5],
								unsigned int one,
								unsigned int two)
{
	char (*f)[5];
	char tmp[5];

	f = from_format_name_sign;	
	
	strcpy(tmp, (f + one -1));
	strcpy((f + one -1), (f + two -1));
	strcpy((f + two -1), tmp);
}

void del_item_strarray(char (*from_format_name_sign)[5],
							unsigned int sign_count,
								unsigned int del)
{
	char (*f1)[5];
	char (*f2)[5];
	int i;
	 
	for(i = del; i < sign_count; i++)
	{
		f1 = from_format_name_sign + del;
		f2 = f1 + 1;
		strcpy(f1, f2);
		f1 = f2;
	}
}


void s(int *a, int *b)
{
	int tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{

	int i, a, b, *x, *y;
	char str [2][5] = {
			{'f','a','n','\0'},
			{'y','u','e','\0'}
		};
	char (*p)[5];
		
	p = str;
	a = 2; b = 3;
	
	x = &a;
	y = &b;
	
	printf("1a = %d, b = %d,\n",a,b);
	s(x,y);
	printf("2a = %d, b = %d,\n",a,b);
	
	swap_item_strarray(p, 1, 2);
	
	printf("arr:  %s\n%s\n", *p++,*p);
	
	del_item_strarray(p, 2, 1);
		printf("del:  %s\n%s\n", *p++,*p);
	
	
	
}
