#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>



/*************************************
��������:
��a[]�е�Ԫ�ؿ���������С����low,�������high 
*****************************************/
void quik_sort(int *a, int low, int high)
{
    int i = low;
    int j = high;  
    int temp = a[i]; 
  
    if( low < high)
    {          
        while(i < j) 
        {
            while( (a[j] >= temp) && (i < j) )
            { 
                j--; 
            }
            a[i] = a[j];
            while( (a[i] <= temp) && (i < j) )
            {
                i++; 
            }  
            a[j]= a[i];
        }
        a[i] = temp;
        quik_sort(a, low, i-1);
        quik_sort(a, j+1, high);
    }
    else
    {
        return;
    }
}

/*************************************
��ʾһά int ���� a�е�����Ԫ�أ���count�� 
*****************************************/
void print_array(int *a, unsigned int count)
{
	int i, *p;
	
	p = a;
	for(i = 0; i < count; i++)
	{
		printf("%d ",*p++);
	}
	printf("\n");
}

/*����: �Ӵ�С*/
void sort(int *arr, int num)
{
	int i, j, tmp;
	
	for(j = 0; j < num - 1; j++)
	{
		for(i = j + 1; i < num; i++)
		{
			if( *(arr + j) < *(arr + i))
			{
				tmp = *(arr + j);
				*(arr + j) = *(arr + i);
				*(arr + i) = tmp;
			}
		}
	}
}


int main()
{
	int s[5] = { 4, 2, 3, 1, 5};
		print_array(s, 5);
	
	sort(s, 5);
	print_array(s, 5);
	
}
