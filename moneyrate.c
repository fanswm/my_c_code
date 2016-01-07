#include <stdio.h>
#include <math.h>

#define HUOQI_RATE 			0.0035	/*活期*/ 
#define THREEMONTHS_RATE 	0.0235	/*3月*/ 
#define SIXMONTHS_RATE 		0.0255	/*6月*/
#define ONEYEAR_RATE 		0.0275	/*1年*/
#define TWOYEARS_RATE 		0.0335	/*2年*/
#define THREEYEARS_RATE 	0.04	/*3年*/
#define FIVEYEARS_RATE 		0.0475	/*5年*/

/*1	2012-7-6：
活期：0.35	
3个月：2.35	
6个月2.55	
一年：2.75
二年：3.35	
三年：4	
五年：4.75*/

/*
 *活期：每一年投入份数fen,按活期利率，到每一期末按复利计算。也就是说：每年末去银行取出重存；
 *3个月：每3个月投入fen,每3个月末取出fen*(1 + (0.0235 / 12) * 3)重存，按复利计息； 
 *6个月：每6个月投入fen,每6个月末取出fen*(1 + (0.0255 / 12) * 6)重存，按复利计息； 
 *1年：每1年投入fen，每年末取出重存，按复利计息；
 *3年：每1年投入fen,每第3年末取出fen * (1 + 0.04 * 3)重存，按复利计息；若期数不是3的倍数，则余数年，按1年的定期利率核算； 
 *5年：仿3年*/

/*每一份指的是每年初的投入数；
期数的单位是：年。*/ 

double unit_rate(unsigned mei_fen, 
				unsigned int qi_shu, 
				float rate)
{
	int i;
	double mei_qi_chu;
	
	mei_qi_chu = 0;
	
	for(i = 1; i <= qi_shu; i++)
	{
		mei_qi_chu = (mei_qi_chu + mei_fen) * (1 + rate);
	}
	return mei_qi_chu;
}

double huoqi_oneyear_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	if(rate == 0)
	{
		rate = HUOQI_RATE;
	}
	
	return (unit_rate(mei_fen_money, qi_shu, rate));
}

double threemonths_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	if(rate == 0)
	{
		rate = THREEMONTHS_RATE;
	}
	return unit_rate(mei_fen_money / 12 * 3, qi_shu * 12 / 3, rate / 12 * 3);
}

double sixmonths_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	if(rate == 0)
	{
		rate = SIXMONTHS_RATE;
	}
	return unit_rate(mei_fen_money / 12 * 6, qi_shu * 12 / 6, rate / 12 * 6);
}

double oneyear_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	if(rate == 0)
	{
		rate = ONEYEAR_RATE;
	}
	return unit_rate(mei_fen_money, qi_shu, rate);
}

double twoyears_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	double sum = 0;
	unsigned int qi;
	int i;
	
	qi = qi_shu / 2;			/*期数是2的多少倍,余数的年数另计*/ 
	
	if(rate == 0)				/*如果未指定利率,则按TWOYEARS_RATE */
	{
		rate = TWOYEARS_RATE;
	}
	sum = unit_rate(mei_fen_money, qi, rate * 2) * 2;   
	
	sum *= (1 + ONEYEAR_RATE);		/*qi指定的sum再存1年定期之后的本息合计*/ 

	sum += (mei_fen_money * (1 + ONEYEAR_RATE) );	/*1份钱存余数年后的本息合计再加上以前的本息合计*/ 
	
	return sum;
}

double threeyears_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	double sum = 0;
	unsigned int qi;
	int i;
	
	qi = qi_shu / 3;
	
	if(rate == 0)
	{
		rate = THREEYEARS_RATE;
	}
	sum = unit_rate(mei_fen_money, qi, rate * 3) * 3;
	
	qi = qi_shu % 3;
	for(i = 1; i <= qi; i++)
	{
		sum *= (1 + ONEYEAR_RATE);
	}
	
	sum += unit_rate(mei_fen_money, qi, ONEYEAR_RATE);
	
	return sum;
}

double fiveyears_rate(unsigned mei_fen_money,
							unsigned int qi_shu,
							float rate)
{
	double sum = 0;
	unsigned int qi;
	int i;
	
	qi = qi_shu / 5;
	
	if(rate == 0)
	{
		rate = FIVEYEARS_RATE;
	}
	sum = unit_rate(mei_fen_money, qi, rate * 5) * 5;
	
	qi = qi_shu % 5;
	for(i = 1; i <= qi; i++)
	{
		sum *= (1 + ONEYEAR_RATE);
	}
	
	sum += unit_rate(mei_fen_money, qi, ONEYEAR_RATE);
	
	return sum;
}


int main()
{
	unsigned int mei_fen_money;
	double h, th, six, one, two, three, five;
	unsigned int qi;
	
	printf("please input meifenmoney,qi:\n");
	scanf("%d %d",&mei_fen_money, &qi);

	h = huoqi_oneyear_rate(mei_fen_money, qi, 0);
	th = threemonths_rate(mei_fen_money, qi, 0);
	six = sixmonths_rate(mei_fen_money, qi, 0);
	one = oneyear_rate(mei_fen_money, qi, 0);
	two = twoyears_rate(mei_fen_money, qi, 0);
	three = threeyears_rate(mei_fen_money, qi, 0);
	five = fiveyears_rate(mei_fen_money, qi, 0);
	
	printf("huoqi sum:\t%f\n",h);
	printf("threemonths sum:\t%f\n",th);
	printf("sixmonths sum:\t%f\n",six);
	printf("oneyears sum:\t%f\n",one);
	printf("twoyears sum:\t%f\n",two);
	printf("threeyears sum:\t%f\n",three);
	printf("fiveyears sum:\t%f\n",five);
	
	return;
}
