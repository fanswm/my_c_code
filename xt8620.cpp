#include <iostream>
using namespace std;
int main()
{
	int n,m,sum;
	int maxn;
	cout<<"please enter maxn:"<<endl;
	cin>>maxn;
	for(n=1;n<=maxn;n++)
	{
		sum=0;
		for(m=1;m<=n/2;m++)
		{
			if(n%m==0)
			{
				sum=sum+m;
			}
		}

		if(n==sum)
		{
			cout<<n<<"its factors are:";
			for(m=1;m<=n/2;m++)
			{
				if(n%m==0)
					cout<<m<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
