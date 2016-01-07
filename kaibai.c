#include <stdio.h>
#include <stdlib.h>

int leapyear(int year)
{
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

/*	参数依次填：年份，开班表的第一天从什么位置开始（1-18），
	元旦放几天假，
	春节是哪一天（4个数字的字符串:MMDD），春节放几天假（从除夕当天开始）
	劳动节放几天假（从5。1当天开始），
	中秋节是哪一天（4个数的字符串:MMDD），中秋节放几天假，
	国庆节放几天假（从10。1开始）
	spring_festival_days为春节放假天数*/
void write_kaibanbiao_to_file(int year, int first,
			int newyears_days,
			char *spring_festival, int spring_festival_days,
			int date_qingming, int qingming_days,
			int labor_days,
			char *mid_autumn, int mid_autumn_days,
			int national_days)   /* (2016, 17, 1, "0218", 14, 4, 1, 1, "0927", 1, 3)  */
{
	int mon, day, col, sumday, leap;
	int mon_spring_festival, date_spring_festival;
	int mon_mid_autumn, date_mid_autumn;
	int tmp, flag;

	FILE *outtxt;
	int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const char bai[3][18] = {
					{'A','A','A','C','C','C','B','B','B','A','A','A','C','C','C','B','B','B'},
					{'B','B',' ','A','A',' ','C','C',' ','B','B',' ','A','A',' ','C','C',' '},
					{'C','C','B','B','B','A','A','A','C','C','C','B','B','B','A','A','A','C'}
				};

    tmp = atoi(spring_festival);
    mon_spring_festival = tmp / 100;
    date_spring_festival = tmp % 100;

    tmp = atoi(mid_autumn);
    mon_mid_autumn = tmp / 100;
    date_mid_autumn = tmp % 100;

    if(year < 1000 || year > 9999 || first > 18 || first <=0 ||
       mon_spring_festival > 12 || mon_spring_festival <= 0 ||
       date_spring_festival > 31 || date_spring_festival <= 0 ||
       mon_mid_autumn > 12 || mon_mid_autumn <= 0 ||
       date_mid_autumn > 31 || date_mid_autumn <= 0)
    {
        printf("Your input is error!\n");
        return;
    }

	leap = leapyear(year);

	if((outtxt = fopen("D:\\kaibanbiao.txt","w+")) == NULL)
    {
        fprintf(stderr,"Cannot open output file.\n");
        return;
    }

	/*  initlize table face */
	fprintf(outtxt, "%d年\n", year);

	for(col = 0; col < 3; col++)
	{
		fprintf(outtxt, "%d\t" , col + 1);
		for(day = 0; day < 18; day++)
		{
			fprintf(outtxt, "%c\t", bai[col][day]);
		}
		fprintf(outtxt, "\n");
	}


	/*  print every days */
	tmp = 0;
	for(mon = 1; mon <= 12; mon++)
	{
		/* is leapyear? */
		if(mon == 2)
		{
			sumday = days[2] + leap;
		}
		else
		{
			sumday = days[mon];
		}

		/*print month name*/
		fprintf(outtxt, "%d\t", mon);
		/*  every month, first print all blanks  */
		for(col = 1; col < first; col++)
		{
			fprintf(outtxt, "\t");
		}

		day = 1 + tmp;
		tmp = 0;
		flag = 1;
		while(day <= sumday)
		{
		    if(mon == 1 && day == 1)    /*  元旦 */
            {
                day += newyears_days;
            }
            else if(mon == mon_spring_festival && day == (date_spring_festival - 1) )/*  春节 */
            {
                day += spring_festival_days;
                if(day > days[mon_spring_festival])
                {
                    tmp = day - days[mon_spring_festival];
                    printf("spring_tmp:%d\n", tmp);
                }
            }
            else if(mon == 4 && day == date_qingming)        /*  清明 */
            {
                day += qingming_days;
            }
            else if(mon == 5 && day == 1)       /*  5.1 */
            {
                day += labor_days;
            }
            else if(mon == mon_mid_autumn && day == date_mid_autumn) /*  中秋 */
            {
                day += mid_autumn_days;
                if(day > days[mon_mid_autumn])
                {
                    tmp = day - days[mon_mid_autumn];
                    printf("mid_autumn_tmp:%d\n", tmp);
                }
            }
            else if(mon == 10 && (day == 1 || flag == 1) )      /*  国庆 */
            {
                day += national_days;
            }

            if(tmp)
            {
                tmp--;
            	printf("tmp:%d\n", tmp);
            	break;
			}
			else
			{
				fprintf(outtxt, "%d\t", day);		/* 关键点:写入日期 */
			}

			day++;
			flag++;
			col++;
			if(col > 18)
			{
				fprintf(outtxt, "\n");
				col %= 18;
				fprintf(outtxt, "%d\t", mon);
			}
		}
		fprintf(outtxt, "\n");
		first = col;
	}
	fprintf(outtxt, "Newyears_days is:%ddays\n", newyears_days);
    fprintf(outtxt, "Spring_festival is:%dmon%ddate;days is:%d\n", mon_spring_festival, date_spring_festival, spring_festival_days);
    fprintf(outtxt, "Qingming is:4mon%ddate;days is:%d\n", date_qingming, qingming_days);
    fprintf(outtxt, "Labor_days is:%ddays\n", labor_days);
    fprintf(outtxt, "Mid_autumn is:%dmon%ddate;days is:%d\n", mon_mid_autumn, date_mid_autumn, mid_autumn_days);
    fprintf(outtxt, "National days is:%ddays\n", national_days);
}

void write_kaibanbiao_to_file2()
{
	int year, first;
	int newyears_days;							/* 元旦 */
	int mon_spring_festival, date_spring_festival, spring_festival_days; /* 春节 */
	int date_qingming, qingming_days; 			/* 清明 */
	int labor_days;								/* 劳动节 */
	int mon_mid_autumn, date_mid_autumn, mid_autumn_days; /* 中秋节 */
	int national_days;							/*   国庆节 */

	int mon, day, col, sumday, leap;
	int tmp, flag;
	char ch;

	FILE *outtxt;
	int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const char bai[3][18] = {
					{'A','A','A','C','C','C','B','B','B','A','A','A','C','C','C','B','B','B'},
					{'B','B',' ','A','A',' ','C','C',' ','B','B',' ','A','A',' ','C','C',' '},
					{'C','C','B','B','B','A','A','A','C','C','C','B','B','B','A','A','A','C'}
				};
	printf("Input year(1000-9999):\n");			/* 输入年份 */
	scanf("%d", &year);
	printf("Input Newyears at?first(1-18):\n");/* 输入元旦第一天的起始位置 */
	scanf("%d", &first);

	printf("newyears_days default:1? Yes:input ch:s\n");
	ch = getchar();
	if(ch == 's')
	{
		newyears_days = 1;
	}
	else
	{
		printf("Input newyears_days(default:1):\n");/* 输入元旦放假天数 */
		scanf("%d", &newyears_days);
	}
	printf("Input mon_spring_festival:\n");		/* 输入春节月份 */
	scanf("%d", &mon_spring_festival);
	printf("Input date_spring_festival:\n");	/* 输入春节日期 */
	scanf("%d", &date_spring_festival);
	printf("Input spring_festival_days:\n");	/* 输入春节放假天数 */
	scanf("%d", &spring_festival_days);
	printf("Input date_qingming:\n");			/* 输入清明节日期 */
	scanf("%d", &date_qingming);

	printf("qingming_days default:1? Yes:input ch:s\n");
	ch = getchar();
	if(ch == 's')
	{
		qingming_days = 1;
	}
	else
	{
		printf("Input qingming_days:\n");			/* 输入清明节放假天数 */
		scanf("%d", &qingming_days);
	}

	printf("labor_days default:1? Yes:input ch:s\n");
	ch = getchar();
	if(ch == 's')
	{
		labor_days = 1;
	}
	else
	{
		printf("Input labor_days:\n");				/* 输入劳动节放假天数 */
		scanf("%d", &labor_days);
	}

	printf("Input mon_mid_autumn:\n");			/* 输入中秋节月份 */
	scanf("%d", &mon_mid_autumn);
	printf("Input date_mid_autumn:\n");			/* 输入中秋节日期 */
	scanf("%d", &date_mid_autumn);

	printf("mid_autumn_days default:1? Yes:input ch:s\n");
	ch = getchar();
	if(ch == 's')
	{
		mid_autumn_days = 1;
	}
	else
	{
		printf("Input mid_autumn_days:\n");			/* 输入中秋节放假天数 */
		scanf("%d", &mid_autumn_days);
	}

	printf("Input national_days:\n");			/* 输入国庆节放假天数 */
	scanf("%d", &national_days);

	/*  判断输入的日期是否合理? */
    if(year < 1000 || year > 9999 || first > 18 || first <=0 ||
       mon_spring_festival > 12 || mon_spring_festival <= 0 ||
       date_spring_festival > 31 || date_spring_festival <= 0 ||
       mon_mid_autumn > 12 || mon_mid_autumn <= 0 ||
       date_mid_autumn > 31 || date_mid_autumn <= 0)
    {
        printf("Your input is error!\n");
        return;
    }

	leap = leapyear(year);

	if((outtxt = fopen("D:\\kaibanbiao.txt","w+")) == NULL)
    {
        fprintf(stderr,"Cannot open output file.\n");
        return;
    }

	/*  initlize table face */
	fprintf(outtxt, "%d年\n", year);
	for(col = 0; col < 3; col++)
	{
		fprintf(outtxt, "%d\t" , col + 1);
		for(day = 0; day < 18; day++)
		{
			fprintf(outtxt, "%c\t", bai[col][day]);
		}
		fprintf(outtxt, "\n");
	}

	/*  print every days */
	tmp = 0;
	for(mon = 1; mon <= 12; mon++)
	{
		/* is leapyear? */
		if(mon == 2)
		{
			sumday = days[2] + leap;
		}
		else
		{
			sumday = days[mon];
		}

		/*print month name*/
		fprintf(outtxt, "%d\t", mon);
		/*  every month, first print all blanks  */
		for(col = 1; col < first; col++)
		{
			fprintf(outtxt, "\t");
		}

		day = 1 + tmp;
		tmp = 0;
		flag = 1;
		while(day <= sumday)
		{
		    if(mon == 1 && day == 1)    /*  元旦 */
            {
                day += newyears_days;
            }
            else if(mon == mon_spring_festival && day == (date_spring_festival - 1) )/*  春节 */
            {
                day += spring_festival_days;
                if(day > days[mon_spring_festival])
                {
                    tmp = day - days[mon_spring_festival];
                    printf("spring_tmp:%d\n", tmp);
                }
            }
            else if(mon == 4 && day == date_qingming)        /*  清明 */
            {
                day += qingming_days;
            }
            else if(mon == 5 && day == 1)       /*  5.1 */
            {
                day += labor_days;
            }
            else if(mon == mon_mid_autumn && day == date_mid_autumn) /*  中秋 */
            {
                day += mid_autumn_days;
                if(day > days[mon_mid_autumn])
                {
                    tmp = day - days[mon_mid_autumn];
                    printf("mid_autumn_tmp:%d\n", tmp);
                }
            }
            else if(mon == 10 && (day == 1 || flag == 1) )     /*  国庆 */
            {
                day += national_days;
            }

            if(tmp)
            {
                tmp -= 1;
            	printf("tmp:%d\n", tmp);
            	break;
			}
			else
			{
				fprintf(outtxt, "%d\t", day);		/* 关键点:写入日期 */
			}

			day++;
			col++;
			flag++;
			if(col > 18)
			{
				fprintf(outtxt, "\n");
				col %= 18;
				fprintf(outtxt, "%d\t", mon);
			}
		}
		fprintf(outtxt, "\n");
		first = col;
	}
	fprintf(outtxt, "Newyears_days is:%ddays\n", newyears_days);
    fprintf(outtxt, "Spring_festival is:%dmon%ddate;days is:%d\n", mon_spring_festival, date_spring_festival, spring_festival_days);
    fprintf(outtxt, "Qingming is:4mon%ddate;days is:%d\n", date_qingming, qingming_days);
    fprintf(outtxt, "Labor_days is:%ddays\n", labor_days);
    fprintf(outtxt, "Mid_autumn is:%dmon%ddate;days is:%d\n", mon_mid_autumn, date_mid_autumn, mid_autumn_days);
    fprintf(outtxt, "National days is:%ddays\n", national_days);
}

int main()
{
	write_kaibanbiao_to_file(2015, 17, 2, "0219", 14, 5, 2, 2, "0928", 3, 6);

}
