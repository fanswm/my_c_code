#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

bool is_Prime(int x)
{
	int i;
	bool f=1;
	for(i = 2; i * i <= x; i++)
	{
		if(x % i == 0)
		{
			f = 0;
			break;
		}
	}
	return f;
}


long factorial(int x)
{
	long f;
	if( x < 0) cout << "not below 0!" << endl;
	else
	{
		if( x == 0) f = 1;
		else
		{
			f = factorial( x - 1 ) * x;
		}
	}
	return f;
}


double exp(int x)
{
	double r = 1,tmp;
	int i = 1;
	float s1;
	long s2;

	do
	{
		s1 = pow(x,i);
		s2 = factorial(i);
		tmp = s1/s2;
		r += tmp;
		i++;
	} while(tmp >= 0.0000000000001);
	return r;
}


double sinh(double x)
{
	return (exp(x) - exp(-x)) / 2;
}


void gotbaha(int x)
{
	int t1,t2,i;
	if(x < 6 || (x % 2) ) cout << "not below 6! or not a even." << "your input is:" << x << endl;
	else
	{
		for(i = 3; i <= x; i++)
		{
			t1 = i;
			if(! is_Prime(t1) ) continue;
			else
			{
				t2 = x - t1;
				if(! is_Prime(t2) ) continue;
				else 
				{
					cout << x << "=" << t1 << "+" << t2 << endl;
					break;
				}
			}
		}
	}
	return;
}



void show_dec_to_bin(int x)
{
	void dec_to_bin(int x);
	dec_to_bin(x);
	cout << endl;
}
void dec_to_bin(int x)
{
	if( x < 2) 
	{
		cout << x;
	}
	else
	{

		dec_to_bin(x / 2);
		cout << x % 2;
	}
}




double lenndre(int x,int n)
{
	double sum;
	if(n == 0) sum = 1;
	else if(n == 1) sum = x;
	else
	{
		sum = ((2 * n - 1) * x - lenndre(x,n-1) - (n - 1) * lenndre(x,n - 2)) / n;
	}
	return sum;
}



void select_sort_array(int array[],int n)
{
	int i,j,tmp,k;
	for(i = 0; i < n - 1; i++)
	{
		k = i;
		for(j = i + 1; j < n; j++)
		{
			if(array[j] < array[k]) k = j;
		}

		if(k != i)
		{
			tmp = array[i];
            array[i] = array[k];
            array[k] = tmp;
		}
	}
}


void show_array(int array[],int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		cout << "array[" << i << "]=" << array[i] << endl;
	}
	cout << endl;
}




bool array_is_sort(int array[],int n)
{
	int i;
	bool b = true;
	if(array[0] >= array[n-1])
	{
       		 for(i = 1; i < n-1; i++)
       		 {
            		if(array[i] > array[0]) 
           		 {
               			 b = false;
               			 break;
            		}
        	}
    	}
       else
       {
      		  for(i = 1; i < n - 1; i++)
       		  {
           		 if(array[i] < array[0])
           		 {
               			 b = false;
               			 break;
            		 }
       		  }
       }
       return b;
}




void insert_array(int array[],int n,int number) 		/*number: insert number!n:array[n]*/
{
    int i,j,k,tmp;
    if(array_is_sort(array,n))
    {
	    if((array[0] <= array[n - 1] && number >= array[n - 1]) || (array[0] >= array[n - 1] && number <= array[n - 1]))
	    {
		    cout << "mast add!quit!!" << endl;
	    }
	    else if((array[0] <= array[n - 1] && number <array[0] ) || ( array[0] >= array[n - 1] && number < array[n - 1] ))
	    {
		    k = 0;
		    tmp = array[n - 1];

		    for(j = n - 1; j > 0; j--)
		    {
	    		array[j] = array[j - 1];
	    	    }
		
		    array[0] = number;
	    }
	    else
	    {
		    for(i = 0; i < n; i++)
		    {
			    if((number >= array[i] && number < array[i+1]) || (number <= array[i] && number > array[i+1]))
			    {
				    k = i;

				    for(j = n - 1;j > k + 1; j--)
				    {
					    array[j] = array[j - 1];
				    }

			    }
		    }
	
			array[k+1]=number;
	    }
    }
    else cout << "the array must sort!" << endl;
}


/*-------------------------------------------------------------*/
/*calendar start:*/
int is_leap(int year)
{
    return (year%4==0&&year%100!=0)||year%400==0;
}


int d_in_month(int year,int month)
{

    int day;
    switch(month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:day=31;break;
        case 4: case 6: case 9: case 11: day=30;break;
        case 2:
              {
                    if(is_leap(year)) 
                    {
                        day=29;break;
                    }
                    else
                    {
                        day=28;break;
                    }
              }
    }
    return day;
}

long s_today(int year,int month)
{
    /*since 1900-1-1,,,,the month first day is the year de di ji tian*/

    long day=0;
    int i,d=0;

    if(year<1900||year>4000)
        printf("1900-4000:your input error!quit!\n");
    else
    {
        for(i=1901;i<year;i++)
        {
            if(is_leap(i)) day+=366;
            else day+=365;
        }
        day++;
    }

    for(i=1;i<month;i++)
    {
        d+=d_in_month(year,i);
    }

    day+=d;
    return day;
}

int is_week(int year,int month)
{
    /*the month first day is week?*/
    long day;
    int w;
    day=s_today(year,month);
    w=day%7+1;
    return w;
}

void calendar(int year,int month)
{
    int w,i,sum;
   
    if(year<1900||year>4000||month<=0||month>12)
    {
        printf("your input error!quit!\n");
    }
    else
    {
        w=is_week(year,month);
        sum=d_in_month(year,month);
        printf("Year:%d Month:%d\n",year,month);
        printf("---------------------------------------------------\n");
        printf("Mon\tTue\tWen\tThu\tFri\tSat\tSun\n");
        for(i=1;i<w;i++)
            printf("\t");
        for(i=1;i<=sum;i++)
        {
            if((w+i-2)%7==0)
                printf("\n");
            printf("%d\t",i);
        }
    }
    printf("\n---------------------------------------------------\n");
}


/*calendar end*/
/*-------------------------------------------------------------*/

