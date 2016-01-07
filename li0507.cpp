#include <iostream>
using namespace std;
int main()
{
	int input_int(int y);
	bool is_Prime(int x,bool flag);
	int n;
	bool f;
	input_int(n);
	is_Prime(n,f);
	cout<<"the"<<n<<"is prime:"<<f<<endl;
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
	bool f=TRUE;
	for(i=2;i<x;i++)
		if(x%i==0) f=FALSE;
	return f;
}
