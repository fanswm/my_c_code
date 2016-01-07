#include <iostream>
using namespace std;
int main()
{
	int x,n;
	int wei(int y);
	void day(int y);
	void nixu(int y);
	cout<<"enter x:"<<endl;
	cin >>x;
	if(x>999999999)
		x=999999999;	
	n=wei(x);
	cout<<"gong you n="<<n<<"wei"<<endl;
	day(x);
	nixu(x);
	return 0;
}

int wei(int y)
{
	int i=1;
	int tmp;
	while((tmp=y/10)!=0)
	{
		i++;
		y=tmp;
	}
	return i;
}

void day(int y)
{
	int i=1;
	int p;
	int tmp;
	cout<<y<<endl;
	while((tmp=y/10)!=0)
	{
		p=y%10;
		y=tmp;
		cout<<"di '"<<i<<"' wei is:"<<p<<endl;
		i++;
	}

	cout<<"di '"<<i<<"' wei is:"<<y<<endl;

}

void nixu(int y)
{
	int p;
	int tmp;
	cout<<y<<endl;
	while((tmp=y/10)!=0)
	{
		p=y%10;
		y=tmp;
		cout<<p;
	}
	cout<<y<<endl;
}
