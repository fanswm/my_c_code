#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INPUT_BUF_SIZE	200				/*��������ʱ����󳤶��ַ���*/

#define YARN_NAME_SIZE	100				/*ɴ��Ʒ�����Ƴ���*/
#define CLOTH_NAME_SIZE	200				/*�޲�Ʒ�����Ƴ���*/

#define NAME_SIGN_SIZE	20				/*��ÿһ��Ʒ�����Ʒֽ��sign,sign�ĳ���*/
#define	NAME_SIGN_COUNT	20				/*��ÿһ��Ʒ�����Ʒֽ��sign�ĸ���*/

#define MATERIAL_NAME_SIZE	10			/*ԭ�����Ƴ���*/
#define MATERIAL_COUNT		5			/*ÿһ��ɴ�е�ԭ��������*/
#define CLOTH_YARN_COUNT	5			/*��ɴ/γɴ�е�ɴ��������*/

const static char yarn_flag [][NAME_SIGN_SIZE] = {
	{'1','3','1','2','1','\0'},						/*T/C29T*/
	{'1','3','1','2','3','2','1','\0'	},			/*T/C65/35 29T*/
	{'1','2','3','1','2','2','1','\0'},				/*T65/C35 29T*/
	{'1','2','1','\0'},								/*C29T*/
	{'1','3','1','2','8','2','1','\0'},				/*T/C29+20D*/
	{'1','3','1','2','7','2','1','\0'},				/* T/C18X2D */
	{'1','3','1','2','3','2','2','7','2','1','\0'}	/*C/T60/40 18X2D*/

};

/*ɴ��*/
struct Order_name_yarn
{
	char name[YARN_NAME_SIZE];			/*Ʒ������ȫ��*/
	char material[MATERIAL_COUNT][MATERIAL_NAME_SIZE];		/*ԭ�ϴ���,����Ϊ:MATERIAL_NAME_SIZE,һ����	MATERIAL_COUNT��ԭ��*/
	
	float proportion[MATERIAL_COUNT];		/*ԭ�ϻ�ȱ���:����2λС��,���MATERIAL_CONUT��ԭ��,�ܺ� = 100*/
	
	float tex;				/*����*/
	unsigned int plying;	/*����*/
	
	char use[6]; 			/*��;*/
	char flag[2];			/*��־*/
	char explain[20];		/*˵��*/
};

typedef struct Order_name_yarn Yarn_name;
typedef Yarn_name * p_Yarn_name;

/*�޲�*/
struct Order_name_cloth
{
	char name[CLOTH_NAME_SIZE];					/*Ʒ������ȫ��*/
	
	Yarn_name tex_t[CLOTH_YARN_COUNT];			/*��ɴ,���YARN_COUNT��*/	
	Yarn_name tex_w[CLOTH_YARN_COUNT];			/*γɴ*/

	
	float density_t;		/*��ɴ�ܶ�*/
	float density_w;		/*γɴ�ܶ�*/
	
	float  width;			/*����*/
	
	char texture[6];		/*֯����֯: 3/1;2/1;1/1;*/
	char texture_name[20]; 	/*֯����֯����:��,��,ƽ,˫��˫γ,�仯б��*/
	char flag[2];			/*��־*/
	char explain[20];		/*˵��*/ 
};

/****************************************************
1,�ü�������һ����ʾƷ�����Ƶ��ַ���,���浽str��,���ַ�����
2,���ó���INPUT_BUF_SIZE - 1 
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
1,�� from ��ʾ���ַ����е������ַ�����,��ǵ�*to_sign:

2,�ѷ��ŵ����ͱ�ǵ�*to_lei:

��ĸ:1;	����:2;	б��	/:3;	�ո�:	4; ������:	5;
������:	6;�˺�x X *:	7;�Ӻ�:	8;���ţ�	9�������ǿո�Ŀɴ�ӡ�ַ�:	a;

����ǣ�Xx,���滻��	*	�� 

3,�����������ַ�:Error,����-1; 
4,����ʱ,���ط������͵�����:count_lei
5,��ĸ,�Ͱ���������Сд�ı�ɴ�д��
******************************************************/
unsigned int input_to_name(	char (*to_sign)[NAME_SIGN_SIZE], 
					char *to_lei, 
					const char *from)
{
	int i;
	unsigned int count_lei;
	
	const char *pfrom = from;	
	char (*ptosign) [NAME_SIGN_SIZE], *ptolei;	/*sign���������, lei�ѷ��ŷ���*/ 
	
	char tmp[NAME_SIGN_SIZE];					/*tmp��ʱ��ŷ��Ŵ�*/
	char *ptmp;
	
	ptosign = to_sign;
	ptolei = to_lei;

	count_lei = 0;

	while(isspace(*pfrom))			/*ȥ���׿ո�*/
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
		  )		/*�������ĸ��X����'x',ͬʱ�ұ�һ�������֣�ͬʱcount_lei > 0.���������������ų���*/
					/*��ĸ:	1*/
		{
			ptmp = tmp;
			while(isalpha(*pfrom))
			{
				*ptmp++ = toupper(*pfrom);			/*ֻҪ����ĸ,�Ͱ���������Сд�ı�ɴ�д��*/
				pfrom++;
			}
			*ptmp = '\0';
			
			*ptolei++ = '1';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(isdigit(*pfrom) || *pfrom == '.')		/*���ֻ�С����:	2*/
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
		else if(isspace(*pfrom))			/* �ո�:	4*/
		{
			ptmp = tmp;
			while(isspace(*pfrom))
			{
				*pfrom++;					/*���пո�ֻҪ����ֻ��һ���ո�*/
			}
			*ptmp++ = ' ';
			*ptmp = '\0';
			
			*ptolei++ = '4';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '(' || *pfrom == '[' )		/*������:	5*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '5';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == ')' || *pfrom == ']')			/*������:	6*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '6';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == 'X' || *pfrom == 'x' || *pfrom == '*')	/*�޲����ָ���:X	x	*  : 7.����ʽ��Ϊ:�Ǻ�	*/
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
		else if(*pfrom == '+')			/*	�Ӻ�:	8*/
		{
			ptmp = tmp;
			*ptmp++ = *pfrom++;
			*ptmp = '\0';
			
			*ptolei++ = '8';
			strcpy(ptosign, tmp);
			ptosign++;
			count_lei++;
		}
		else if(*pfrom == '-')			/*	����:	9*/
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
				)			/*������֮��Ŀɴ�ӡ�ַ�*/ 
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
	
	return count_lei;		/*���ط������͵�����*/
}


/*******************************************************
1,�ѷֺ���ı��sign:	from_name_sign�еĿո�ȥ��,
2,��ȥ���ո����ַ������浽	formatstr;
3,����Ӧ�ķ����ű��浽	leiformat; 
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
���ַ���from�����ҵ�n���ַ������1���ո񣬷��ؼ���ո��������ַ���ͷָ�� from. 
��1��(n = 1)�ַ��ǵ�һ���� 
**************************************************************/
char *insert_n_blank_to_str(char *from, unsigned int n)
{
	char *t1, *t2, to[100];
	int i = 0;
	
	t1 = from;
	t2 = to;

	for(i = 1; i <= n; i++)
	{
		if( !(*t1) )			/*����ǿ��ַ�,��ֹͣ*/
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
1����	insert_str������ַ���,���뵽to��	��end���,(��1��)�ǵ�һ����:from_name_sign[0]. 
2,��from_name_sign[NAME_SIGN_SIZE]�����е�ÿһ���ַ���������һ���ַ���������ɲ��빤���� 
ǰ����NAME_SIGN_SIZE�㹻�� 
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
	
	for(i = 1; i <= sign_count; i++)
	{
		if(i == end)					/*�������end���ѵ�end�����Ӻ�Ȼ��������insert_str��*/
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

/**/
void order_and_write_name(	p_Yarn_name pyname,
				unsigned int format_count,
				char (*from_format_name_sign)[NAME_SIGN_SIZE],
				char *from_format_name_lei)
{
	const static char (*flag)[NAME_SIGN_SIZE];
	char (*sign)[NAME_SIGN_SIZE];
	char *pn;	
	int e, i = 0;
	
	flag = yarn_flag;
	sign = from_format_name_sign;
	pn = pyname->name;
	
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
					insert_item_to_strarray(pn, sign, format_count, 3, " 65/35 ");
					pyname->proportion[0] = 65;
					pyname->proportion[1] = 35;
				}
				else if(**sign == 'C' && **(sign + 1) == '\/' && **(sign + 2) == 'T')
				{
					insert_item_to_strarray(pn, sign, format_count, 3, " 60/40 ");
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

void write_yarn_to_file(p_Yarn_name pyname)
{
	FILE *fp;
	
	if((fp = fopen("yarntxt", "w")) == NULL)		/*���ļ�: yarntxt*/
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
void read_file_yarn_to_pointer(p_Yarn_name pyname, FILE *fp)
{	
	if((fp = fopen("yarntxt", "r")) == NULL)		/*���ļ�: yarntxt*/
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
	char buf[INPUT_BUF_SIZE];			/*����ʱ��ʱ�洢���ַ���*/
	char *pbuf;
	int i;
	unsigned int count_lei, count_fmt;
	
	char sign[NAME_SIGN_COUNT][NAME_SIGN_SIZE], lei[NAME_SIGN_COUNT];		/*sign���������, lei�ѷ��ŷ���*/
	char formatsign[NAME_SIGN_COUNT][NAME_SIGN_SIZE], formatlei[NAME_SIGN_COUNT];
	
	char (*psign) [NAME_SIGN_COUNT], *plei;
	char (*fmts)[NAME_SIGN_COUNT] ;	
	
	p_Yarn_name pn;
	Yarn_name yarn[1];
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
		printf("input:lei: %c :\t", lei[i]);
		printf("input:psign: %d: %s\n", i, psign);
		psign++;
	}
	
	plei = lei;
	fmts = formatsign;
	
	order_and_write_name(pn, count_fmt, fmts, formatlei);
	
	printf("input:lei is:%s\n", plei);
	printf("input:formatlei is:%s\n", formatlei);
	printf("input:format sign is:\n");
	
	for(i = 0; i < count_fmt; i++)
	{
		printf("input:%s",fmts);
		fmts++;		
	}
	printf("\n");
	
	printf("input:pn name is:\t%s\n",pn->name);
	
	
	print_yarn(pn);
	
	write_yarn_to_file(pn);
	
}

int main()
{
	int i;
	for(i = 0; i < 1; i++)
	{
		input();
	}
}
