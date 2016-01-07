#include <iostream>
using namespace std;
int main()
{
	float sgm(int x);
	int n;
	cout<<"please enter n:"<<endl;
	cin >> n;
	cout<<"sgm(n)="<<sgm(n)<<endl;
}

float sgm(int x)
{
	float jiecheng(int y);
	int i;
	float sum=0;
	for(i=1;i<=x;i++)
	{
		sum=sum+jiecheng(i);
		cout<<"jiecheng("<<i<<")="<<jiecheng(i)<<endl;
	}
	return sum;
}

float jiecheng(int y)
{
	int i;
	float sum=1;
	if(y==0) sum=1;
	else
	{
		for(i=1;i<=y;i++)
		{
			sum=sum*i;
		}
	}
	return sum;
}
