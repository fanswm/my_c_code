#include <stdio.h>
/*
 *此程序的作用: 输入当前的 年4位 月2位 日2位, 计算这一天是
 * 自1979年5月17日起的第几天; 
*/

void input_date(int *year, int *month, int *day)
			
/* 此函数输入日期，年4位，月2位，日2位,中间用空格隔开。 
存入year,month,day的指针指定的三个变量中；
年：1500-3000*/
{
	char leapyear = 0;
	int y,m,d;
	
	printf("please input year(4),month(2),day(2)\n");
	scanf("%d %d %d",year,month,day);
	y = *year;
	m = *month;
	d = *day;
	
	leapyear = (char) ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);		/*判断是否是闰年*/
	
	if(y < 1500 || y > 3000 || m < 1 || m > 12 || d <1 || d > 31)
	{
		printf("Error: input error!\n3000\t>\tyear\t>\t1500;\n12\t>\tmonth\t>\t1;\n31\t>\tday\t>\t1;\n");	/*year month day 的范围*/
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
/*计算日期1和日期2之间间隔的天数，计头不计尾*/ 
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
	
	sday = 0;						/*初始为0*/
	
	leapyear = (char) ((y1 % 4 == 0 && y1 % 100 != 0) || y1 % 400 == 0);		/*判断是否是闰年*/
	
	if(y2 == y1)						/*如果是同一年*/ 
	{
		if(m2 == m1)					/*如果是同一个月*/ 
		{
			sday += (d2 - d1);
		}
		else if(m2 < m1)
		{
			printf("1st month too big!\n");
			return;								/*错误：第一个月大于第二个月*/
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
		return;								/*错误：第一年大于第二个年份*/
	}
	else
	{
	
		if(leapyear)					/*不是同一年，计算第一个月的天数*/
		{
			sday += ( b[m1] - d1 + 1 );
		}
		else
		{
			sday += ( a[m1] - d1 );
		}
		
		i = m1 + 1;						/*跳到第一年的第二个月*/
	
		for(; i <= 12; i++)				/*计算第一年除第一个月之外的天数*/
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
	
		i = y1 + 1;						/*跳到第二年*/
	
		for(; i < y2; i++)
		{
			leapyear = (char) ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0);		/*判断是否是闰年*/
		
			if(leapyear)
			{
				sday += 366;
			}
			else
			{
				sday += 365;
			}		
		}
	
		/*以上循环完之后，leapyear 就是y2那一年的是否闰年*/ 
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
