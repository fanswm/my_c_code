#include <iostream>
using namespace std;
int main()
{
	int g;
	char a;
	cout << "enter g:"<<endl;
	cin >> g;
	cout << endl;
	if(g>=90&&g<=100)
		a='A';
	else
	{
		if(g>=80&&g<90)
			a='B';
		else
		{
			if(g>=70&&g<80)
				a='C';
			else
			{
				if(g>=60&&g<70)
					a='D';
				else
				{
					if(g>100)
						cout<<"100fenzhi!!"<<endl;
					else 
						cout<<"bujige!"<<endl;
				}
			}
		}
	}
	if(a>=60) cout<<"a="<<a<<endl;
}
