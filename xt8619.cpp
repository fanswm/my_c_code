#include <iostream>
using namespace std;
int main()
{
	int zunum(int x,int y,int z);
	int i,j,k,m=0;
	for(i=1;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			for(k=0;k<10;k++)
			{
				if((i*i*i+j*j*j+k*k*k)==zunum(i,j,k))
				{
					m++;
					cout<<"the "<<m<<" th flower number is:"<<i<<j<<k<<endl;
				}
			}
		}
	}
	return 0;
}


int zunum(int x,int y,int z)
{
	int sum=0;
	sum=x*100+y*10+z;
	return sum;
}
