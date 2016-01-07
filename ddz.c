/*****************************************************
ֽ�ƣ�������
��������	����	����
��ϣ�
�ԣ�
����
�ģ�
��+��
��+�ԣ� 
��+��*2�� 
��+��*2�� 
����
˫����
����2��,
����2+��*2��
����2+��*2�� 
����3+��*2��
����*2+��*2��
����*3+��*3��

����spade ����heart  ÷��club ����diamond
b			h			m			f 
*****************************************************/

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>

struct cd
{
	char hua;				/*����:����B, ����H, ÷��M, ����F*/
	unsigned int dian;		/*����:1 - 13*/
	unsigned int ji;		/*����1 - 54*/
};

typedef struct cd Card;
typedef Card * pcd;

struct gamer
{
	pcd pai[20];				/**ӵ�е���,ָ������**/
	unsigned char yichu[20];	/**�Ƿ��ѳ���δ��1, �ѳ�0**/
	char dizhu;					/**�ǵ�����1**/
	char cixu;					/**���Ƶ��Ⱥ�˳��1��2��3	**/
};

typedef struct gamer Player;
typedef Player * pplayer;

Player player[3];			/*3�����*/
Card card[14][4];			/*56����,���2����Ч*/


/*����: ��arr�����е�num��Ԫ��,�Ӵ�С*/
void sort(int *arr, int num)
{
	int i, j, tmp;
	
	for(j = 0; j < num - 1; j++)
	{
		for(i = j + 1; i < num; i++)
		{
			if( *(arr + j) < *(arr + i))
			{
				tmp = *(arr + j);
				*(arr + j) = *(arr + i);
				*(arr + i) = tmp;
			}
		}
	}
}

/**********************************************
pָ��һ���������,�� player_count �����(ddz����3).
ÿһ�������һ��ָ��һ���Ƶ�ָ������,ÿһ��ָ��ָ��һ����,
���� num ����(ddz�������20��) 
*************************************************/
void print_player(pplayer p, int player_count, int num)
{
	int i, j;	
	printf("print_player start:\n");

	for(i = 0; i < player_count; i++)
	{
		for(j = 0; j < num; j++)
		{
			printf("%c%d ", p->pai[j]->hua, p->pai[j]->dian);
		}
		p++;
		printf("\n");
	}
	printf("\n");
	printf("print_player OK!\n");
}

/**********************************************
pָ��һ���������,�� player_count �����(ddz����3).
ÿһ�������һ��ָ��һ���Ƶ�ָ������,ÿһ��ָ��ָ��һ����,
���� num ����(ddz�������20��) 
*************************************************/
void print_player_no_hua(pplayer p, int player_count, int num)
{
	int i, j;
	printf("print_player_no_hua start:\n");

	for(i = 0; i < player_count; i++)
	{
		for(j = 0; j < num; j++)
		{
			printf("%d ", p->pai[j]->dian);
		}
		p++;
		printf("\n");
	}
	printf("\n");
	printf("print_player_no_hua OK!\n");
}

/**********************************************
��ʾ3�ŵ�����ʲô 
*************************************************/
void print_dipai(pcd dipai[])
{
	int i;
	printf("print_dipai start:\n");

	for(i = 0; i < 3; i++)
	{
		printf("%c%d ",dipai[i]->hua, dipai[i]->dian );	
	}
	printf("\n");
	printf("print_dipai OK!\n");
}


/**********************************************
����ÿ���Ƶļ���:	���ҵļ����,����ļ���С
����	Y
С��	X 
*************************************************/
void set_card_ji(pcd p )
{
	int i;
	printf("set_card_ji start:\n");
	for(i = 1; i <= 54; i++)
	{
		(p + i - 1)->ji = i;
	}
	printf("set_card_ji OK!\n");
}

/**********************************************
����ddzÿ���Ƶļ���:�� 1 2�� ����	Y  С��	X 
pָ��һ��Card�Ľṹ����,�������ĵ�һά��x,�ڶ�ά��y 
pcd��ָ��Card��ָ�� 
*************************************************/
void set_card_ddz_ji(pcd p, unsigned int x, unsigned int y )
{
	int i, j, ji;
	
	printf("set_card_ddz_ji start:\n");
	
	ji = 1;	
	for(i = 2; i < x - 1; i++)
	{
		for(j = 0; j < y; j++)
		{
			(p + i * y + j)->ji = ji;
		}
		ji++;
	}
	
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < y; j++)
		{
			(p + i * y + j)->ji = ji;
		}
		ji++;
	}
	
	(p + 13 * y + 0)->ji = ji++;			/*С��*/
	(p + 13 * y + 1)->ji = ji;				/*����*/
	printf("set_card_ddz_ji OK!\n");
}

/**********************************************
����ÿ���ƵĻ�ɫ,����,����;
����spade ����heart  ÷��club ����diamond
B			H			M		F
���ҵļ����,����ļ���С
����	Y
С��	X 
pָ��һ��Card�Ľṹ����(pָ��һ����),�������ĵ�һά��x,�ڶ�ά��y 
���� x * y ���� 
pcd��ָ��Card��ָ�� 
*************************************************/
void set_card(pcd p, unsigned int x, unsigned int y )
{
	int i, j;
	printf("set_card start:\n");
	for(i = 0; i < x - 1; i++)
	{
		(p + i * y + 0)->hua = 'F';			/*i0*/
		(p + i * y + 1)->hua = 'M';			/*i1*/
		(p + i * y + 2)->hua = 'H';			/*i2*/
		(p + i * y + 3)->hua = 'B';			/*i3*/
		
		for(j = 0; j < y; j++)
		{
			(p + i * y + j)->dian = i + 1;
		}
	}
	
	(p + 13 * y + 0)->hua = 'X';			/*С��*/
	(p + 13 * y + 1)->hua = 'Y';			/*����*/
	(p + 13 * y + 2)->hua = ' ';
	(p + 13 * y + 3)->hua = ' ';
	
	(p + 13 * y + 0)->dian = 14;
	(p + 13 * y + 1)->dian = 14;
	(p + 13 * y + 2)->dian = 0;
	(p + 13 * y + 3)->dian = 0;
	
	(p + 13 * y + 0)->ji = 53;
	(p + 13 * y + 1)->ji = 54;
			
	printf("set card OK!\n");
}

/*************************************
��������:
��a[]�е�Ԫ�ؿ���������С����low,�������high 
*****************************************/
void quik_sort(int *a, int low, int high)
{
    int i = low;
    int j = high;  
    int temp = a[i]; 
  
    if( low < high)
    {          
        while(i < j) 
        {
            while( (a[j] >= temp) && (i < j) )
            { 
                j--; 
            }
            a[i] = a[j];
            while( (a[i] <= temp) && (i < j) )
            {
                i++; 
            }  
            a[j]= a[i];
        }
        a[i] = temp;
        quik_sort(a, low, i - 1);
        quik_sort(a, j+1, high);
    }
    else
    {
        return;
    }
}


/*************************************
��map[]�е���(��max��)������е�to[]�С�
map[]�в�����0�ļ�¼ 
map��toͬ���� 
����ɹ�������1�����򷵻�0�� 
*****************************************/
int rand_min_max(int *to, int *map, unsigned int max)
{
	int i, t, j, randmax;

	randmax = max - 1;			/*���� 0 - (max - 1)֮��������*/
	for(i = 0; i < max - 1; i++)
	{
		srand( (unsigned)time( NULL ) ); 
		t = rand() % randmax;
		
		to[i] = map[t];
		
		j = randmax;
		while( (map[j] == 0) && (j > 0) )	/*����һ����0�ļ�¼*/
		{
			j--;
		}
		map[t] = map[j];		/*�����һ�������λ*/
		map[j] = 0;				/*����0����¼Ϊ�ѷ���*/
		
		randmax--;
	}
	
	to[max - 1] = map[0];		/*����map[0]�Ƶ�to[max - 1]��*/
	return 1;		
}

/*************************************
��ʾһά int ����a�е�����Ԫ�أ���count�� 
*****************************************/
void print_array(int *a, unsigned int count)
{
	int i, *p;
	
	printf("print_array start:\n");
	p = a;
	for(i = 0; i < count; i++)
	{
		printf("%d ",*p++);
	}
	printf("\nprint_array OK!\n");
}


/*************************************
ϴ�ƣ���1 - 54������������ң��ŵ�int����to�� .
to��һ���������飬����54��Ԫ�� 
*****************************************/
void shuffle(int *to)
{
	int i, from[54];
	
	printf("shuffle start:\n");
		
	for(i = 0; i < 54; i++)
	{
		from[i] = i + 1;
	}
	rand_min_max(to, from, 54);
	printf("shuffle OK!\n");
}

/**********************************************
��ʾpָ���һ���Ƶ�ÿһ����: ÿ������1��,��14�� 
pָ��һ��Card�Ľṹ����,�������ĵ�һά��x,�ڶ�ά��y 
pcd��ָ��Card��ָ�� 
*************************************************/
void print_card(pcd p, unsigned int x, unsigned int y )
{
	int i, j;
	
	printf("print card start:\n");	

	for(i = 0; i < x; i++)
	{		
		for(j = 0; j < y; j++)
		{
			printf("%c%d\t", (p + i * y + j)->hua, (p + i * y + j)->dian );
		}
		printf("\n");
	}
	printf("print card OK!\n");
}

/**********************************************
��ʾÿһ����
ÿ����ɫΪ1��,
	��5�� 
*************************************************/
void print_card2(pcd p, unsigned int x, unsigned int y )		/*����,�Ի�Ϊ��λ*/
{
	int i, j;	
	printf("print card2 start:\n");
	for(j = 0; j < y; j++)
	{		
		for(i = 0; i < x - 1; i++)
		{
			printf("%c%d ", (p + i * y + j)->hua, (p + i * y + j)->dian );
		}
		printf("\n");
	}
	
	for(j = 0; j < 2; j++)
	{
		printf("%c%d ", (p + 13 * y + j)->hua, (p + 13 * y + j)->dian );
	}
	printf("\n");
	printf("print card2 OK!\n");	
}


/**********************************************
��ʾÿһ���Ƶļ���,���Ӽ���С������� 
*************************************************/
void print_card_ji(pcd p )
{
	int i;
	printf("print_card_ji start:\n");
	
	for(i = 0; i < 54; i++)
	{
		printf("%c%dd%d ", (p + i)->hua, (p + i)->dian,(p + i)->ji );
	}
	printf("\n");
	printf("print_card_ji OK!\n");
}

/**********************************************
����ҵ�������: pָ��һ����ң���������һ����Աpai��
pai��һ��ָ�����飬ÿһ��Ԫ��ָ��һ���� ��
ÿ������һ����Ա��dian
��pָ��������е�count���ƴӴ�С����,������ 
�շ�����ʱ,count = 17 
*************************************************/
void player_sort( pplayer p, int count )
{
	int i, j;
	pcd tmp;
	
	printf("player_sort start:\n");
	for(j = 0; j < count -1; j++)
	{
		for(i = j + 1; i < count; i++)
		{
			if( (p->pai[j]->ji) < (p->pai[i]->ji) )
			{
				tmp = p->pai[j];
				p->pai[j] = p->pai[i];
				p->pai[i] = tmp;				
			}
		}
	}
	printf("player_sort OK!\n");	
}

void all_player_sort( pplayer p, int player_count, int count )
{
	int i;
	
	printf("all_player_sort start:\n");
	for(i = 0; i < player_count; i++)
	{
		player_sort(p, count);
		p++;
	}
	printf("all_player_sort OK!\n");	
}

/**********************************************
������������˭�ǵ��������ֱ�����, ��һ��������dz��0��1��2�� 
*************************************************/
int qiang_dz(pplayer p, int dz)
{
	
}


/**********************************************
pָ��һ���������,�� player_count �����(ddz����3).
ÿһ�������һ��ָ��һ���Ƶ�ָ������,ÿһ��ָ��ָ��һ����,
���� num ����(ddz����17��),ÿ�����ֻ��17���� 
pcard ָ��һ���Ƶ�ָ�룬�⸱�����δ�1��14����54���ƣ���55��56��Ч��
��ң�
player0			player2
		player1 
����ֵ��˭�ǵ�����0��1��2 
ͬʱ,�ѵ��ƴ���dipaiָ���һ��pcd����,ÿһ��Ԫ����һ��ָ�� 
*************************************************/
int fapai(pplayer p, int player_count, int num, pcd pcard, pcd *dipai)
{
	int i, j, dz, dizhi[54], *pdizhi;			/*dizhi[54]�б���1 - 54֮��������,ǰ17�����ǵ�һ����ҵ�*/
	pcd ppai = pcard;

	
	pdizhi = dizhi;
	printf("fapai start:\n");
	
	srand( (unsigned)time( NULL ) ); 
	dz = rand() % 3;					/*����һ�� 0 - 2 ֮������������־˭�ǵ���*/
	
	shuffle(dizhi);						/*ϴ��*/
	 
	print_array(dizhi, 54);
	for(i = 0; i < player_count; i++)
	{
		for(j = 0; j < num; j++)
		{
			p->pai[j] = ppai + *pdizhi - 1;	/*pָ��һ�����player,�������һ���ṹ������һ����pai[]*/
											/*�⸱����20��ָ��Card��ָ��, pcard��һ��ָ�룬ָ��������*/	
											/*һ��Ҫ��1, ��Ϊ�� 1 - 54 ����*/
			pdizhi++;
		}
		p++;
	}
	for(i = 0; i < 3; i++)
	{
		*dipai = ppai + *pdizhi - 1;		/*����*/
		dipai++;
		pdizhi++;
	}
	
	printf("fapai OK!\n");
	return dz;			
}


int main()
{
	pcd pointer, *dp, fanswm;
	pcd dipai[3];		
	
	pointer = card;
	dp = dipai;
	
	set_card(pointer, 14, 4);
	set_card_ddz_ji(pointer, 14, 4);
	
	print_card(pointer, 14, 4);
	print_card2(pointer, 14, 4);
	print_card_ji(pointer);
	
	fapai(player, 3, 17, pointer, dp);
	
	print_player(player,3,17);
	print_dipai(dp);
	
	all_player_sort(player, 3, 17);
	print_player_no_hua(player,3,17);
	
}






