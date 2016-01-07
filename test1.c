#include <stdio.h>
#include <string.h>


/*********************************************************
在字符串from从左到右第n个字符后加入1个空格，返回加入空格后的整个字符串头指针 from. 
第1个(n = 1)字符是第一个。 
**************************************************************/
char *insert_n_blank_to_str(char *from, unsigned int n)
{
	char *t1, *t2, to[100];
	int i = 0;
	
	t1 = from;
	t2 = to;

	for(i = 1; i <= n; i++)
	{
		if( !(*t1) )			/*如果是空字符,则停止*/
		{
			break;
		}
		*t2 = *t1;
		t2++;
		t1++;
	}
	*t2 = ' ';
	t2++;

	while(*t1++)
	{
		*t2 = *t1;
		t2++;
	}

	*t2 = '\0';
	strcpy(from,to);
	return from;
}

int main()
{

	char *a, aa[20] = "123456789";
	char *b,bb[13];

	
	a = aa;
	b = bb;
	
	b = insert_n_blank_to_str(a,3);
	printf("old is:%s,new is:%s\n",a, b);

}
