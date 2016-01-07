#include <iostream>
using namespace std;
int main()
{
	int sn(int a,int n);
	int sna,snn,sum;
	cout<<"please enter sna & snn:"<<endl;
	cin>>sna>>snn;
	sum=sn(sna,snn);
	cout<<"sum="<<sum<<endl;
}


int sn(int a,int n)
{
	int snxiang(int p,int q);
	int i;
	int snsum=0;
	for(i=1;i<=n;i++)
	{
		snsum=snsum+snxiang(a,i);
		cout<<"snxiang"<<i<<"="<<snxiang(a,i)<<endl;
	}
	return snsum;
}

int snxiang(int p,int q)
{
	int power(int a,int b);
	int i,sum=0;
	if(q==1) sum=p;
	else
	{
		for(i=1;i<=q;i++)
		{
			sum=sum*10+p;
		}
	}
	return sum;
}

int power(int a,int b)
{
	int i=1,sum=1;
	if(b==0)
	{
		 sum=1;
	}
	else
	{
		for(i=1;i<=b;i++)
		{
			sum=sum*a;
		}
	}
	return sum;
}
