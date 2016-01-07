#include <stdio.h>
/*
 *�˳��������: ���뵱ǰ�� ��4λ ��2λ ��2λ, ������һ����
 * ��1979��5��17����ĵڼ���; 
*/

void input_date(int *year, int *month, int *day)
			
/* �˺����������ڣ���4λ����2λ����2λ,�м��ÿո������ 
����year,month,day��ָ��ָ�������������У�
�꣺1500-3000*/
{
	char leapyear = 0;
	int y,m,d;
	
	printf("please input year(4),month(2),day(2)\n");
	scanf("%d %d %d",year,month,day);
	y = *year;
	m = *month;
	d = *day;
	
	leapyear = (char) ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);		/*�ж��Ƿ�������*/
	
	if(y < 1500 || y > 3000 || m < 1 || m > 12 || d <1 || d > 31)
	{
		printf("Error: input error!\n3000\t>\tyear\t>\t1500;\n12\t>\tmonth\t>\t1;\n31\t>\tday\t>\t1;\n");	/*year month day �ķ�Χ*/
		return;
	}
	else if(leapyear && d > 29)
	{
		printf("Error: LeapYear:Feb > 29 \n");
		return;
	}
	else if( d > 28)
	{
		printf("Error: !LeapYear:Feb > 28\n");
		return;
	}
	return;
}

void count_dateone_to_datetwo(int *year1, int *month1, int *day1,
								int *year2, int *month2, int *day2,
								int *sumday,int *zhouqi)
/*��������1������2֮��������������ͷ����β*/ 
{
	int sday,zhq;

	int y1, m1, d1;
	int y2, m2, d2;
	int i; 
	char leapyear = 0;
	
	int a[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int b[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
	
	y1 = *year1; m1 = *month1; d1 = *day1;
	y2 = *year2; m2 = *month2; d2 = *day2;
	
	sday = 0;						/*��ʼΪ0*/
	
	leapyear = (char) ((y1 % 4 == 0 && y1 % 100 != 0) || y1 % 400 == 0);		/*�ж��Ƿ�������*/
	
	if(y2 == y1)						/*�����ͬһ��*/ 
	{
		if(m2 == m1)					/*�����ͬһ����*/ 
		{
			sday += (d2 - d1);
		}
		else if(m2 < m1)
		{
			printf("1st month too big!\n");
			return;								/*���󣺵�һ���´��ڵڶ�����*/
		}
		else
		{
			sday += ( b[m1] - d1 + 1 );
			for(i = m1 + 1; i < m2; i++)
			{
				if(leapyear)
				{
					sday += b[i];
				}
				else
				{
					sday += a[i];
				}
			}
			sday += (d2 - 1);
		}
	}
	else if(y2 < y1)
	{
		printf("1st year too big!\n");
		return;								/*���󣺵�һ����ڵڶ������*/
	}
	else
	{
	
		if(leapyear)					/*����ͬһ�꣬�����һ���µ�����*/
		{
			sday += ( b[m1] - d1 + 1 );
		}
		else
		{
			sday += ( a[m1] - d1 );
		}
		
		i = m1 + 1;						/*������һ��ĵڶ�����*/
	
		for(; i <= 12; i++)				/*�����һ�����һ����֮�������*/
		{
			if(leapyear)
			{
				sday += b[i];
			}
			else
			{
				sday += a[i];
			}
		}
	
		i = y1 + 1;						/*�����ڶ���*/
	
		for(; i < y2; i++)
		{
			leapyear = (char) ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0);		/*�ж��Ƿ�������*/
		
			if(leapyear)
			{
				sday += 366;
			}
			else
			{
				sday += 365;
			}		
		}
	
		/*����ѭ����֮��leapyear ����y2��һ����Ƿ�����*/ 
		if(leapyear)
		{
			for(i = 1; i < m2; i++)
			{
				sday += b[i];
			}
		}	
		else
		{
			for(i = 1; i < m2; i++)
			{
				sday += a[i];
			}
		}
		sday += d2;
	}
	
	zhq = sday % 28;
		
	*sumday = sday;
	*zhouqi = zhq;
}

int main()
{
	int *year1, *month1, *day1, *sd, *zq;
	int *year2, *month2, *day2;
	int y1, m1, d1, s, z;
	int y2, m2, d2;
	
	year1 = &y1; month1 = &m1; day1 = &d1;
	year2 = &y2; month2 = &m2; day2 = &d2;
	sd = &s;
	zq = &z;
	
	input_date(year1, month1, day1);
	
	input_date(year2, month2, day2);
	
	count_dateone_to_datetwo(year1, month1, day1,
							year2, month2, day2,
							sd,zq);

	
	printf("sumday is %d;\nzhouqi is %d;\n",s,z);
	
	return 0;	
}
