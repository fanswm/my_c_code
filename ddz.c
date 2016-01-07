/*****************************************************
纸牌：斗地主
单：花型	点数	级别
组合：
对：
三：
四：
三+单
三+对： 
四+单*2： 
四+对*2： 
连：
双连：
三连2：,
三连2+单*2：
三连2+对*2： 
三连3+单*2：
三连*2+对*2：
三连*3+单*3：

黑桃spade 红桃heart  梅花club 方块diamond
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
	char hua;				/*花型:黑桃B, 红桃H, 梅花M, 方块F*/
	unsigned int dian;		/*点数:1 - 13*/
	unsigned int ji;		/*级别1 - 54*/
};

typedef struct cd Card;
typedef Card * pcd;

struct gamer
{
	pcd pai[20];				/**拥有的牌,指针数组**/
	unsigned char yichu[20];	/**是否已出。未出1, 已出0**/
	char dizhu;					/**是地主？1**/
	char cixu;					/**出牌的先后顺序：1，2，3	**/
};

typedef struct gamer Player;
typedef Player * pplayer;

Player player[3];			/*3个玩家*/
Card card[14][4];			/*56张牌,最后2张无效*/


/*排序: 把arr数组中的num个元素,从大到小*/
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
p指向一个玩家数组,有 player_count 个玩家(ddz中是3).
每一个玩家有一个指向一批牌的指针数组,每一个指针指向一张牌,
共有 num 张牌(ddz中是最多20张) 
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
p指向一个玩家数组,有 player_count 个玩家(ddz中是3).
每一个玩家有一个指向一批牌的指针数组,每一个指针指向一张牌,
共有 num 张牌(ddz中是最多20张) 
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
显示3张底牌是什么 
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
设置每张牌的级别:	黑桃的级别大,方块的级别小
大王	Y
小王	X 
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
设置ddz每张牌的级别:主 1 2； 大王	Y  小王	X 
p指向一个Card的结构数组,这个数组的第一维是x,第二维是y 
pcd是指向Card的指针 
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
	
	(p + 13 * y + 0)->ji = ji++;			/*小王*/
	(p + 13 * y + 1)->ji = ji;				/*大王*/
	printf("set_card_ddz_ji OK!\n");
}

/**********************************************
设置每张牌的花色,点数,级别;
黑桃spade 红桃heart  梅花club 方块diamond
B			H			M		F
黑桃的级别大,方块的级别小
大王	Y
小王	X 
p指向一个Card的结构数组(p指向一副牌),这个数组的第一维是x,第二维是y 
共有 x * y 张牌 
pcd是指向Card的指针 
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
	
	(p + 13 * y + 0)->hua = 'X';			/*小王*/
	(p + 13 * y + 1)->hua = 'Y';			/*大王*/
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
快速排序:
把a[]中的元素快速排序，最小座标low,最大座标high 
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
把map[]中的数(共max个)随机排列到to[]中。
map[]中不能有0的记录 
map和to同样大 
如果成功，返回1，否则返回0； 
*****************************************/
int rand_min_max(int *to, int *map, unsigned int max)
{
	int i, t, j, randmax;

	randmax = max - 1;			/*产生 0 - (max - 1)之间的随机数*/
	for(i = 0; i < max - 1; i++)
	{
		srand( (unsigned)time( NULL ) ); 
		t = rand() % randmax;
		
		to[i] = map[t];
		
		j = randmax;
		while( (map[j] == 0) && (j > 0) )	/*跳过一切是0的记录*/
		{
			j--;
		}
		map[t] = map[j];		/*用最后一个数填补空位*/
		map[j] = 0;				/*等于0，记录为已发牌*/
		
		randmax--;
	}
	
	to[max - 1] = map[0];		/*最后把map[0]移到to[max - 1]中*/
	return 1;		
}

/*************************************
显示一维 int 数组a中的所有元素，共count个 
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
洗牌：把1 - 54个整数随机打乱，放到int数组to中 .
to是一个整型数组，共有54个元素 
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
显示p指向的一副牌的每一张牌: 每个点数1行,共14行 
p指向一个Card的结构数组,这个数组的第一维是x,第二维是y 
pcd是指向Card的指针 
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
显示每一张牌
每个花色为1行,
	共5行 
*************************************************/
void print_card2(pcd p, unsigned int x, unsigned int y )		/*横向,以花为单位*/
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
显示每一张牌的级别,按从级别小到级别大 
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
把玩家的牌排序: p指向一个玩家，这个玩家有一个成员pai，
pai是一个指针数组，每一个元素指向一张牌 。
每张牌有一个成员：dian
把p指向的数组中的count张牌从大到小排序,按级别 
刚发完牌时,count = 17 
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
抢地主，返回谁是地主？基分倍数？, 第一个地主是dz（0，1，2） 
*************************************************/
int qiang_dz(pplayer p, int dz)
{
	
}


/**********************************************
p指向一个玩家数组,有 player_count 个玩家(ddz中是3).
每一个玩家有一个指向一手牌的指针数组,每一个指针指向一张牌,
共有 num 张牌(ddz中是17张),每个玩家只发17张牌 
pcard 指向一副牌的指针，这副牌依次从1到14（共54张牌，第55、56无效）
玩家：
player0			player2
		player1 
返回值：谁是地主？0，1，2 
同时,把底牌存入dipai指向的一个pcd数组,每一个元素是一个指针 
*************************************************/
int fapai(pplayer p, int player_count, int num, pcd pcard, pcd *dipai)
{
	int i, j, dz, dizhi[54], *pdizhi;			/*dizhi[54]中保存1 - 54之间的随机数,前17张牌是第一个玩家的*/
	pcd ppai = pcard;

	
	pdizhi = dizhi;
	printf("fapai start:\n");
	
	srand( (unsigned)time( NULL ) ); 
	dz = rand() % 3;					/*产生一个 0 - 2 之间的随机数，标志谁是地主*/
	
	shuffle(dizhi);						/*洗牌*/
	 
	print_array(dizhi, 54);
	for(i = 0; i < player_count; i++)
	{
		for(j = 0; j < num; j++)
		{
			p->pai[j] = ppai + *pdizhi - 1;	/*p指向一个玩家player,该玩家是一个结构，他有一副牌pai[]*/
											/*这副牌是20个指向Card的指针, pcard是一个指针，指向整副牌*/	
											/*一定要减1, 因为是 1 - 54 的数*/
			pdizhi++;
		}
		p++;
	}
	for(i = 0; i < 3; i++)
	{
		*dipai = ppai + *pdizhi - 1;		/*底牌*/
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






