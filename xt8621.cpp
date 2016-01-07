#include <iostream>
using namespace std;
int main()
{
	int xiang,zi2,zi1=2,mu1=1,mu2;
	float sum;
	int i;
	sum=2/1;

	cout<<"please enter xiang:"<<endl;
	cin >> xiang;
	cout<<"di\t"<<"1\txiang:"<<'\t';
	cout<<zi1<<'\t'<<mu1<<'\t'<<"sum="<<sum<<endl;

	for(i=2;i<=xiang;i++)
	{
		zi2=zi1+mu1;
		mu2=zi1;
		sum=sum+(float)zi2/(float)mu2;
		cout<<"di\t"<<i<<"\txiang:"<<'\t';
		cout<<zi2<<'\t'<<mu2<<'\t'<<"sum="<<sum<<endl;
		zi1=zi2;
		mu1=mu2;
	}
	cout<<"sum="<<sum<<endl;
	return 0;
}

