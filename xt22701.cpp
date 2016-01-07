#include <iostream>
using namespace std;
struct Date
	{
		int year;
		int month;
		int day;
		int count;
	}
int main()
{
	Date date;
	void input_date(Date *);
	void print_date(Date *);
	Date *p;
	p=&date;
	input_date(p);
	print_date(p);
	return 0;
}

void input_date(Date *p)
{
	cin>>p->year;
	cin>>p->month;
	cin>>p->day;
	return;
}

void print_date(Date *p)
{
	cout<<p->year;
	cout<<p->month;
	cout<<p->day;
	return;
}