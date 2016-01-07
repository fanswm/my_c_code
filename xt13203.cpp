#include <iostream>
using namespace std;
int main()
{
	int input_int(int y);
	bool is_Prime(int x,bool flag);
	int n;
	bool f;
	n=input_int(n);
	f=is_Prime(n,f);
	cout<<"the "<<n<<" is prime:"<<f<<endl;
	return 0;
}

int input_int(int y)
{
	cout<<"please enter a int number:"<<endl;
	cin>>y;
	cout<<endl;
	return y;
}
bool is_Prime(int x,bool flag)
{
	int i;
	bool f=1;
	for(i=2;i*i<=x;i++)
	{
		if(x%i==0)
		{
			f=0;
			break;
		}
	}
	return f;
}
