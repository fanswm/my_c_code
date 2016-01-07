#include <iostream>
using namespace std;
int main()
{
	float bonus,bonus1,bonus2,bonus4,bonus6,bonus10;
	float i;
	int d;

	cout<<"please enter i:"<<endl;
	cin>> i;

	if(i>1000000)
	{
		d=10;
	}
	else
	       	d=((int)i)/100000;

	bonus1=100000*0.1;
	bonus2=bonus1+100000*0.075;
	bonus4=bonus2+200000*0.05;
	bonus6=bonus4+200000*0.03;
	bonus10=bonus6+400000*0.015;
	switch(d)
	{
		case 0:bonus=i*0.1;
		case 1:bonus=bonus1+(i-100000)*0.75;
		case 2:
		case 3:bonus=bonus2+(i-200000)*0.05;
		case 4:
		case 5:bonus=bonus4+(i-400000)*0.03;
		case 6:
		case 7:
		case 8:
		case 9:bonus=bonus6+(i-600000)*0.015;
		case 10:bonus=bonus10+(i-1000000)*0.01;
	}
	cout << "bonus="<<bonus<<endl;
	return 0;
}
