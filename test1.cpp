int b=3;
int power(int x,int y)
{
	int sum;
	if(y==0) sum=1;
	else
	{
		sum=power(x,y-1)*x;
	}
	return sum;
}
