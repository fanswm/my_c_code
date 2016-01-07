#include <iostream>
using namespace std;
int main()
{
	int all(int day);
	int sum;
	sum=all(1);
	cout<<"begin:"<<sum<<endl;
	return 0;
}

int all(int day)
{
	int s;
	if(day==10)
		s=1;
	else
		s=(all(day+1)+1)*2;
	return s;
}
