#include <iostream>
using namespace std;
int main()
{
	int f(int x);
	int a,y;
	cout << "please enter a="<<endl;
	cin >> a;
	y=f(a);	
	cout << "y="<<y << endl;	
}

int f(int x)
{
	int fx;
	if(x>1)
		fx=x;
	if(x<10&&x>=1)
		fx=x*2-1;
	if(x>=10)
		fx=x*3-11;
	return fx;		
}
