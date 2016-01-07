#include <iostream>
using namespace std;
int main()
{
	int showmaxtomin(int x1,int x2,int x3,int x4);
	int a1,a2,a3,a4;
	cout<<"please enter four number:"<<endl;
	cin>>a1>>a2>>a3>>a4;
	showmaxtomin(a1,a2,a3,a4);
	return 0;
}

int showmaxtomin(int x1,int x2,int x3,int x4)
{
	int m1,m2,m3,m4,tmp;
	m1=x1;m2=x2;m3=x3;m4=x4;
	if(m1>m2)
	{
		tmp=m1;m1=m2;m2=tmp;
	}
	if(m2>m3)
	{
		tmp=m2;m2=m3;m3=tmp;
	}
	if(m3>m4)
	{
		tmp=m3;m3=m4;m4=tmp;
	}

	if(m1>m2)
	{
		tmp=m1;m1=m2;m2=tmp;
	}
	if(m2>m3)
	{
		tmp=m2;m2=m3;m3=tmp;
	}
	if(m1>m2)
	{
		tmp=m1;m1=m2;m2=tmp;
	}
	cout<<m1<<"-"<<m2<<"-"<<m3<<"-"<<m4<<endl;
}
