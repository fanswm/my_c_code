#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INPUT_BUF_SIZE	200				/*键盘输入时的最大长度字符数*/

#define YARN_NAME_SIZE	100				/*纱线品种名称长度*/
#define CLOTH_NAME_SIZE	200				/*棉布品种名称长度*/

#define NAME_SIGN_SIZE	30				/*把每一个品种名称分解成sign,sign的长度*/
#define	NAME_SIGN_COUNT	30				/*把每一个品种名称分解成sign的个数*/

#define MATERIAL_NAME_SIZE	10			/*原料名称长度*/
#define MATERIAL_COUNT		5			/*每一种纱中的原料种类数*/
#define CLOTH_YARN_COUNT	5			/*经纱/纬纱中的纱线种类数*/

const static char yarn_flag [][NAME_SIGN_SIZE] = {
	{'1','3','1','2','1','\0'},						/*0	T/C29T			*/
	{'1','3','1','2','3','2','2','1','\0'	},		/*1	T/C65/35 29T	*/
	{'1','2','3','1','2','2','1','\0'},				/*2	T65/C35 29T		*/
	{'1','2','1','\0'},								/*3	C29T			*/
	{'1','3','1','2','8','2','1','\0'},				/*4	T/C29+20D		*/
	{'1','3','1','2','7','2','1','\0'},				/*5	T/C18X2D 		*/
	{'1','3','1','2','3','2','2','7','2','1','\0'},	/*6	C/T60/40 18X2D	*/
	{'1','2','3','1','2','2','7','2','1','\0'},		/*7	C50/T50 18*2D	*/
	{'1','2','7','2','1','\0'},						/*8	T18*2D			*/
	{'1','2','8','2','1','1','\0'},					/*9	C36+20D T		*/
	{'1','2','8','2','1','7','2','1','\0'},			/*10	C36+20D*2TW		*/
	{'1','3','1','3','1','2','3','2','3','2','2','1','\0'},			/*11	T/C/A 30/30/40 36T	*/
	{'1','3','1','3','1','2','3','2','3','2','2','7','2','1','\0'},	/*12	T/C/A 30/30/40 36*2T	*/
	{'1','2','3','1','2','3','1','2','2','1','\0'},					/*13	A30/B30/C40  36T	*/
	{'1','2','3','1','2','3','1','2','2','7','2','1','\0'},			/*14	A30/B30/C40  36*2T	*/
	{'1','3','1','3','1','3','1','2','3','2','3','2','3','2','2','1','\0'},	/*15	A/B/C/D 20/20/20/40 36T	*/
	{'1','2','3','1','2','3','1','2','3','1','2','2','1','\0'},				/*16	A20/B20/C20/D40 36T	*/
	{'1','3','1','3','1','3','1','3','1','2','3','2','3','2','3','2','3','2','2','1','\0'},	/*17	A/B/C/D/E 20/20/20/20/20 36T	*/
	{'1','2','3','1','2','3','1','2','3','1','2','3','1','2','2','1','\0'}					/*18	A20/B20/C20/D20/E20 36T	*/
};

/*纱线*/
struct Order_name_yarn
{
	char name[YARN_NAME_SIZE];			/*品种名称全称*/
	char material[MATERIAL_COUNT][MATERIAL_NAME_SIZE];		/*原料代号,长度为:MATERIAL_NAME_SIZE,一共有	MATERIAL_COUNT个原料*/
	
	float proportion[MATERIAL_COUNT];		/*原料混比比例:保留2位小数,最多MATERIAL_CONUT个原料,总和 = 100*/
	
	float tex;				/*号数*/
	unsigned int plying;	/*股数*/
	
	char use[6]; 			/*用途*/
	char flag[2];			/*标志*/
	char explain[20];		/*说明*/
};

typedef struct Order_name_yarn Yarn_name;
typedef Yarn_name * p_Yarn_name;

/*棉布*/
struct Order_name_cloth
{
	char name[CLOTH_NAME_SIZE];					/*品种名称全称*/
	
	Yarn_name tex_t[CLOTH_YARN_COUNT];			/*经纱,最多YARN_COUNT种*/	
	Yarn_name tex_w[CLOTH_YARN_COUNT];			/*纬纱*/

	
	float density_t;		/*经纱密度*/
	float density_w;		/*纬纱密度*/
	
	float  width;			/*幅宽*/
	
	char texture[6];		/*织物组织: 3/1;2/1;1/1;*/
	char texture_name[20]; 	/*织物组织名称:卡,府,平,双经双纬,变化斜纹*/
	char flag[2];			/*标志*/
	char explain[20];		/*说明*/ 
};

/****************************************************
1,用键盘输入一个表示品种名称的字符串,保存到str中,总字符个数
2,不得超过INPUT_BUF_SIZE - 1 
******************************************************/
void input_string(char *str)
{
	char *p = str;
	char ch;
	int i = 0;
	
	while( 
			( (ch = getch()) != '\r') 
			&& i < INPUT_BUF_SIZE  
		)
	{
		*p = ch;	
		putch(ch);
		
		i++;
		if(i == INPUT_BUF_SIZE)
		{
			printf("FUN:input_string:\nerror: your input is too long!\n");
			continue;
		}
		p++;
	}
	*p = '\0';
	putch('\n');
}

/****************************************************
1,把 from 表示的字符串中的所有字符分类,标记到*to_sign:

2,把符号的类型标记到*to_lei:

字母:1;	数字:2;	斜杠	/:3;	空格:	4; 左括号:	5;
右括号:	6;乘号x X *:	7;加号:	8;减号：	9；其他非空格的可打印字符:	a;

如果是：Xx,则替换成	*	； 

3,再有其他的字符:Error,返回-1; 
4,正常时,返回符号类型的种类:count_lei
5,字母,就把其中所有小写的变成大写的
******************************************************/
unsigned int input_to_name(	char (*to_sign)[NAME_SIGN_SIZE], 
					char *to_lei, 
					const char *from)
{
	int i;
	unsigned int count_lei;
	
	const char *pfrom = from;	
	char (*ptosign) [NAME_SIGN_SIZE], *ptolei;	/*sign用来存符号, lei把符号分类*/ 
	
	char tmp[NAME_SIGN_SIZE];					/*tmp临时存放符号串*/
	char *ptmp;
	
	ptosign = to_sign;
	ptolei = to_lei;

	count_lei = 0;

	while(isspace(*pfrom))			/*去除首空格*/
	{
		pfrom++;
	}
	
	while(*pfrom)
	{
		if(
			isalpha(*pfrom) && 
			!(
				(*pfrom == 'X' || *pfrom == 'x') 
				&& isdigit( *(pfrom + 1) )
				&& count_lei > 0
			 )			
		  )		/*如果是字母‘X’或'x',同时右边一个是数字，同时count_lei > 0.则把以上这种情况排除掉*/
					/*字母:	1*/
		{
			ptmp = tmp;
			while(isalpha(*pfrom))
			{
				*ptmp++ = toupper(*pfrom);			/*只要是字母,就把其中所有小写的变成大写的*/
				pfrom++;
			}
			*ptmp = '\0';
			
			*ptolei++ = '1';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(isdigit(*pfrom) || *pfrom == '.')		/*数字或小数点:	2*/
		{
			ptmp = tmp;
			while(isdigit(*pfrom) || *pfrom == '.')
			{
				*ptmp++ = *pfrom++;
			}
			*ptmp = '\0';
			
			*ptolei++ = '2';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '\/')				/*	"/":	3*/
		{
			ptmp = tmp;
			*ptmp++ = '\/';
			*pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '3';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(isspace(*pfrom))			/* 空格:	4*/
		{
			ptmp = tmp;
			while(isspace(*pfrom))
			{
				*pfrom++;					/*所有空格只要连续只算一个空格*/
			}
			*ptmp++ = ' ';
			*ptmp = '\0';
			
			*ptolei++ = '4';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '(' || *pfrom == '[' )		/*左括号:	5*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '5';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == ')' || *pfrom == ']')			/*右括号:	6*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '6';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == 'X' || *pfrom == 'x' || *pfrom == '*')	/*棉布规格分隔符:X	x	*  : 7.并格式化为:星号	*/
		{
			ptmp = tmp;
			*ptmp++ = '*';
			pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '7';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '+')			/*	加号:	8*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '8';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '-')			/*	减号:	9*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '9';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(
					isgraph(*pfrom)
				&&	!isalpha(*pfrom)
				&&	!isdigit(*pfrom)
				&&	*pfrom != '\/' 
				&&	*pfrom != ' ' 
				&&	*pfrom != '(' 
				&&	*pfrom != '['
				&&	*pfrom != ')' 
				&&	*pfrom != ']'
				&&	*pfrom != '+' 
				&&	*pfrom != '-' 
				&&	*pfrom != '*' 
				)			/*除以上之外的可打印字符*/ 
		{
			ptmp = tmp;
			while(*pfrom)
			{
				*ptmp++ = *pfrom++;
			}
			*ptmp = '\0';
			
			*ptolei++ = 'a';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else					/*Error:	-1	*/
		{
			ptosign = to_sign;
			ptolei = to_lei;
			ptosign = NULL;
			ptolei = NULL;
			return -1;
		}
	}
	*ptolei = '\0';
	
	return count_lei;		/*返回符号类型的种类*/
}


/*******************************************************
1,把分好类的编号sign:	from_name_sign中的空格去掉,
2,把去掉空格后的字符串保存到	formatstr;
3,把相应的分类编号保存到	leiformat; 
*******************************************************/
unsigned int format_name(	char (*signformat)[NAME_SIGN_SIZE],
					char *leiformat,
					char (*from_name_sign)[NAME_SIGN_SIZE],
					char *from_name_lei)
{
	char *lt, *le, *fnm;
	char (*st)[NAME_SIGN_SIZE], (*s)[NAME_SIGN_SIZE];
	unsigned int count;
	int i;

	st = signformat;
	lt = leiformat;
	s = from_name_sign;
	le = from_name_lei;
	count = 0;

	while(*le)
	{
		if(*le != '4')
		{
			*lt++ = *le++;
			strcpy(st,s);
			
			st++;
			s++;
			count++;
		}
		else
		{
			le++;
			s++;
		}
	}
	*lt = '\0';

	return count;
}

/*********************************************************
在字符串from从左到右第n个字符后加入1个空格，返回加入空格后的整个字符串头指针 from. 
第1个(n = 0)字符是第一个。 
**************************************************************/
char *insert_n_blank_to_str(char *from, unsigned int n)
{
	char *t1, *t2, to[100];
	int i;
	
	t1 = from;
	t2 = to;

	for(i = 0; i < n; i++)
	{
		if( !(*t1) )			/*如果是空字符,则停止*/
		{
			break;
		}
		*t2 = *t1;
		t2++;
		t1++;
	}
	*t2 = ' ';
	t2++;

	while(*t1++)
	{
		*t2 = *t1;
		t2++;
	}

	*t2 = '\0';
	strcpy(from,to);
	return from;
}

/****************************************************************
1，在from_format_name_sign的所第end项后插入一个字符串:insert_str;并把所有项组合成
	一个字符串,赋给to; 
	把	insert_str代表的字符串,插入到目标字符串to的	第end项后,(第0项)是第一个即:from_name_sign[0]. 
2,把from_name_sign[NAME_SIGN_SIZE]数组中的每一个字符串项连成一个字符串，并完成插入工作。 
	前提是NAME_SIGN_SIZE足够大 
******************************************************************/
void insert_item_to_strarray(char *to,
								char (*from_format_name_sign)[NAME_SIGN_SIZE],
								unsigned int sign_count,
								unsigned int end,
								char *insert_str)
{
	char (*f)[NAME_SIGN_SIZE];
	int i;

	f = from_format_name_sign;	
	
	for(i = 0; i < sign_count; i++)
	{
		if(i == end)					/*如果到了end项，则把第end项连接后，然后再连上insert_str项*/
		{
			strcat(to,*f);
			strcat(to,insert_str);
			f++;
		}
		else
		{
			strcat(to,*f);
			f++;
		}
	}
	return to;	
}

/****************************************************************
1，把字符串数组from_format_name_sign的第one项和第two项交换（物理交接）; 
    第一项是0,即第一项是第0项； 
2, 前提是NAME_SIGN_SIZE足够大 
******************************************************************/
void change_item_strarray(char (*from_format_name_sign)[NAME_SIGN_SIZE],
								unsigned int one,
								unsigned int two)
{
	char (*f)[NAME_SIGN_SIZE];
	char tmp[NAME_SIGN_SIZE];

	f = from_format_name_sign;	
	
	strcpy(tmp, (f + one));
	strcpy((f + one), (f + two));
	strcpy((f + two), tmp);
}

/****************************************************************
1，把字符串数组from_format_name_sign的第one项删除(逻辑删除); 
    第0项是0； 
2, 返回删除之后的总项数sign_count;
3, 前提是NAME_SIGN_SIZE足够大 
******************************************************************/
unsigned int delete_item_strarray(char (*from_format_name_sign)[NAME_SIGN_SIZE],
							unsigned int sign_count,
							unsigned int del)
{
	char (*f1)[NAME_SIGN_SIZE];
	char (*f2)[NAME_SIGN_SIZE];
	int i; 

	for(i = del; i < sign_count; i++)
	{
		f1 = from_format_name_sign + del;
		f2 = f1 +1;
		strcpy(f1, f2);
		f1 = f2;
	}
}

/*把结构: 把pyname指向的结构:order_yarn_name初始化*/
void initialize_yarn(p_Yarn_name pyname)
{
	int i;
	
	pyname->name[0] = '\0';
	
	for(i = 0; i < MATERIAL_COUNT; i++)
	{
		pyname->material[i][0] = '\0';
	}
	
	for(i = 0; i < MATERIAL_COUNT; i++)
	{
		pyname->proportion[i] = 0.0;
	}
	
	pyname->tex = 0.0;
	pyname->plying = 0;
	pyname->use[0] = '\0';
	pyname->flag[0] = '\0';
	pyname->explain[0] = '\0';
}


/**/
void order_and_write_yarn_name(	p_Yarn_name pyname,
				unsigned int format_count,
				char (*from_format_name_sign)[NAME_SIGN_SIZE],
				char *from_format_name_lei)
{
	const static char (*flag)[NAME_SIGN_SIZE];	/*指向标志数据库*/
	char (*sign)[NAME_SIGN_SIZE];				/*指向符号字符串数组*/
	char *pn;	
	unsigned int e, i = 0;
	float per1, per2;
	
	flag = yarn_flag;
	sign = from_format_name_sign;
	pn = pyname->name;						/*yarn.name*/
	
	initialize_yarn(pyname);				/*	pyname赋初值:空	*/
	
	for(i = 0; i < format_count; i++)
	{             
		if(0 == strcmp(from_format_name_lei, flag))
		{
			e = i;
		}
			flag++;
	}
	printf("order_and_write_name: e: %d\n",e);
	
	switch(e)
	{
		case 0:
			{
				printf("case 0:\n");
			
				if(**sign == 'T' && **(sign + 1) == '\/' && **(sign + 2) == 'C')
				{
					insert_item_to_strarray(pn, sign, format_count, 2, " 65/35 ");
					pyname->proportion[0] = 65;
					pyname->proportion[1] = 35;
				}
				else if(**sign == 'C' && **(sign + 1) == '\/' && **(sign + 2) == 'T')
				{
					insert_item_to_strarray(pn, sign, format_count, 2, " 60/40 ");
					pyname->proportion[0] = 60;
					pyname->proportion[1] = 40;
				}
				else
				{
					/*strcpy(pn, "");*/
					pn = NULL;
					printf("The format name is illegal!\n");
					return;
				}
				strcpy(pyname->material, *sign );
				strcpy( (pyname->material + 1), *(sign + 2) );
				pyname->tex = atof( *(sign + 3));
				pyname->plying = 1;
				strcpy(pyname->use,*(sign + 4));
				pyname->flag[0] = '\0';
				pyname->explain[0] = '\0';					
			}
			break;
		case 1:
			{	
				printf("case 1:\n");
			
				if(**sign == 'T' && **(sign + 2) == 'C')
				{
					per1 = atof( *(sign + 3));
					per2 = atof( *(sign + 5));
					if((per1 + per2) == 100.0)
					{
						if(0)
						pn = NULL;
						printf("The format name is illegal!\n");
						return;
					}
					else
					{
						insert_item_to_strarray(pn, sign, format_count, 2, " 65/35 ");
						pyname->proportion[0] = 65;
						pyname->proportion[1] = 35;
					}
				}
				else if(**sign == 'C' && **(sign + 2) == 'T')
				{
					insert_item_to_strarray(pn, sign, format_count, 2, " 60/40 ");
					pyname->proportion[0] = 60;
					pyname->proportion[1] = 40;
				}
				else
				{
					/*strcpy(pn, "");*/
					pn = NULL;
					printf("The format name is illegal!\n");
					return;
				}
				strcpy(pyname->material, *sign );
				strcpy( (pyname->material + 1), *(sign + 2) );
				pyname->tex = atof( *(sign + 3));
				pyname->plying = 1;
				strcpy(pyname->use,*(sign + 4));
				pyname->flag[0] = '\0';
				pyname->explain[0] = '\0';					
			}
			break;
		default:
			break;
	}
	
	printf("order_and_write_name:name:%s\n",pyname->name);
	
}


void print_yarn(p_Yarn_name p)
{
	int i;
	
	printf("name:\t%s\n", p->name);
	printf("material:\t");
	for(i = 0; i < MATERIAL_COUNT; i++ )
	{
			printf("%s\t", p->material[i]);
	}
	printf("\n");
	
	printf("proportion:\t");
	for(i = 0; i < MATERIAL_COUNT; i++ )
	{
			printf("%g\t", p->proportion[i]);
	}
	printf("\n");
	
	printf("tex:\t%g\n", p->tex);
	printf("plying:\t%d\n", p->plying);
	printf("use:\t%s\n", p->use);
	printf("flag:\t%s\n", p->flag);
	printf("explain:\t%s\n",p->explain);
	printf("print OK!\n");
}

/*把一个名称pyname,	写入	f指向字符串	文件名	代表的文件*/
void write_yarn_to_file(char *f, p_Yarn_name pyname)
{
	FILE *fp;
	
	if((fp = fopen(f, "w")) == NULL)		/*打开文件: yarntxt*/
	{
		printf("file open error!\n");
		return;
	}
	
	if(fwrite(pyname, sizeof(struct Order_name_yarn), 1, fp) != 1)
	{
		printf("file write error!\n");
	}
	
	fclose(fp);
}

void read_file_yarn_to_pyname(p_Yarn_name pyname, char *filename)
{
	FILE *fp;
	if((fp = fopen(filename, "r")) == NULL)	
	{
		printf("file open error!\n");
		return;
	}
	
	if(fread(pyname, sizeof(struct Order_name_yarn), 1, fp) != 1)
	{
		printf("file read error!\n");
	}
	
	fclose(fp);
}

void input()
{
	char buf[INPUT_BUF_SIZE];			/*输入时临时存储的字符串*/
	char *pbuf;
	int i;
	unsigned int count_lei, count_fmt;
	
	char sign[NAME_SIGN_COUNT][NAME_SIGN_SIZE], lei[NAME_SIGN_COUNT];		/*sign用来存符号, lei把符号分类*/
	char formatsign[NAME_SIGN_COUNT][NAME_SIGN_SIZE], formatlei[NAME_SIGN_COUNT];
	
	char (*psign) [NAME_SIGN_COUNT], *plei;
	char (*fmts)[NAME_SIGN_COUNT] ;	
	
	p_Yarn_name pn;
	Yarn_name yarn[2];
	pn = yarn;
	
	plei = lei;
	psign = sign;
	fmts = formatsign;
	pbuf = buf;	
	count_lei = 0;
	count_fmt = 0;
		
	input_string(pbuf);
	count_lei = input_to_name(psign, plei, pbuf);
	count_fmt = format_name(fmts, formatlei, psign, plei);
	
	printf("input: buf is: %s\n", buf);
	
	for(i = 0; i < count_lei; i++)
	{
		printf("input:psign: %d: %s\n", i, psign);
		psign++;
	}
	
	plei = lei;
	fmts = formatsign;
	
	order_and_write_yarn_name(pn, count_fmt, fmts, formatlei);
	
	printf("input:formatlei is:%s\n", formatlei);
	
	printf("input:pn name is:\t%s\n",pn->name);
	
	write_yarn_to_file("D:\\code\\yarn.txt", pn);
	
/**
	read_file_yarn_to_pyname( (pn + 1), "D:\\code\\yarn.txt");

/**/
	printf("your input is:\n\n\n");
	print_yarn(pn);

	
}

int main()
{
	int i;
	for(i = 0; i < 1; i++)
	{
		input();
	}
}
