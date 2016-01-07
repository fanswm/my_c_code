#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
	int e,s,d,ot;
	e=0,s=0,d=0,ot=0;
	char c;
	while((c=getchar())!='\n')
	{
		if(c==' ') s++;
		else if(c>='a'&&c<='z'||c>='A'&&c<='Z') e++;
		else if(c>='0'&&c<='9') d++;
		else ot++;
	}
	cout<<"e="<<e<<";s="<<s<<";d="<<d<<";ot="<<ot<<endl;
}
