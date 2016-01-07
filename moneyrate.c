#include <stdio.h>
#include <math.h>

#define HUOQI_RATE 			0.0035	/*����*/ 
#define THREEMONTHS_RATE 	0.0235	/*3��*/ 
#define SIXMONTHS_RATE 		0.0255	/*6��*/
#define ONEYEAR_RATE 		0.0275	/*1��*/
#define TWOYEARS_RATE 		0.0335	/*2��*/
#define THREEYEARS_RATE 	0.04	/*3��*/
#define FIVEYEARS_RATE 		0.0475	/*5��*/

/*1	2012-7-6��
���ڣ�0.35	
3���£�2.35	
6����2.55	
һ�꣺2.75
���꣺3.35	
���꣺4	
���꣺4.75*/

/*
 *���ڣ�ÿһ��Ͷ�����fen,���������ʣ���ÿһ��ĩ���������㡣Ҳ����˵��ÿ��ĩȥ����ȡ���ش棻
 *3���£�ÿ3����Ͷ��fen,ÿ3����ĩȡ��fen*(1 + (0.0235 / 12) * 3)�ش棬��������Ϣ�� 
 *6���£�ÿ6����Ͷ��fen,ÿ6����ĩȡ��fen*(1 + (0.0255 / 12) * 6)�ش棬��������Ϣ�� 
 *1�꣺ÿ1��Ͷ��fen��ÿ��ĩȡ���ش棬��������Ϣ��
 *3�꣺ÿ1��Ͷ��fen,ÿ��3��ĩȡ��fen * (1 + 0.04 * 3)�ش棬��������Ϣ������������3�ı������������꣬��1��Ķ������ʺ��㣻 
 *5�꣺��3��*/

/*ÿһ��ָ����ÿ�����Ͷ������
�����ĵ�λ�ǣ��ꡣ*/ 

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
	
	qi = qi_shu / 2;			/*������2�Ķ��ٱ�,�������������*/ 
	
	if(rate == 0)				/*���δָ������,��TWOYEARS_RATE */
	{
		rate = TWOYEARS_RATE;
	}
	sum = unit_rate(mei_fen_money, qi, rate * 2) * 2;   
	
	sum *= (1 + ONEYEAR_RATE);		/*qiָ����sum�ٴ�1�궨��֮��ı�Ϣ�ϼ�*/ 

	sum += (mei_fen_money * (1 + ONEYEAR_RATE) );	/*1��Ǯ���������ı�Ϣ�ϼ��ټ�����ǰ�ı�Ϣ�ϼ�*/ 
	
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
