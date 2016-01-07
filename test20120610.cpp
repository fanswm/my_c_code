#include <iostream>
using namespace std;
void show(int n)
{
	if(n>=10)
	{
		show(n/10);
		cout<<" ";
	}
	cout<<n%10;
}

int main()
{
	show(183);
	cout<<endl;
	return 0;
}
