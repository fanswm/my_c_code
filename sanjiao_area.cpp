#include "fan.h"
#define S(a,b,c) (a+b+c)/2
#define AREA(a,b,c) sqrt(S(a,b,c)*(S(a,b,c)-a)*(S(a,b,c)-b)*(S(a,b,c)-c))
int main()
{
	int a,b,c;
	cin>>a>>b>>c;
	double area;
	area=AREA(a,b,c);
	cout<<area<<endl;
	return 0;
}
