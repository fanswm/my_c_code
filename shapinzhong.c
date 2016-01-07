#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/*
 �����������ã�
 ��Դ�ļ���D:\code\sha.txt�ж�ȡƷ�����ƣ�
 ʶ�����ȣ�д�뵽 D:\code\outsha.txt�С� 
*/

#define NUMBER	1
#define ZIMU	2
#define ZUOXIE	3
#define BUFSIZE 100

void getstr_from_file(char *to, FILE *fp)
/*��Դ�����ж�ȡһ�У����뵽�ַ���to��.������bufsize���ַ�*/
{
	char ch;
	int i = 0;
    ch = getc(fp);	
	while(ch != '\n' && ch != EOF && i < BUFSIZE )
	{
    	*to++ = ch;
    	ch = getc(fp);
		i++;	
    }
    *to = '\0';
}

void write_str_to_outfile(char *str, FILE *fp)
/*��strָ����ַ�����д�뵽fpָ����ļ��У�D:\\code\\outsha.txt*/ 
{
	if((fp = fopen("D:\\code\\outsha.txt","a")) == NULL)
    {
        fprintf(stderr,"Cannot open output file.\n");
        return;
    }
    fwrite(str, strlen(str), 1, fp);
    fwrite("\n", 1, 1, fp);
    fclose(fp);
}

void get_peibi_from_str(char *peibi, char *from)
/*�����磺T/C 65/35 29T���ַ��������Ʒ�������У���ȡ���Ʒ�ֵ���ȣ����뵽peibi��*/ 
{
	char *pp, *pf, *ppp, tmp1[20], tmp2[20];
	int flag = 0;
	pf = from;
	pp = peibi;
	
	while( isalpha(*pf) || *pf == '/')
	{
		*pp = *pf;
		pf++;
		pp++;
	}
	
	ppp = pp;
	*pp = '\0';
	strcpy(tmp1, peibi);
	
	while(*pf == ' ')
	{
		pf++;
	}
	while( isdigit(*pf) || *pf == '/' || *pf == '.')
	{
		if(*pf == '/')
		{
			flag = 1;
		}
		*pp = *pf;
		pf++;
		pp++;
	}

	*pp = '\0';
	strcpy(tmp2, ppp);
	
	if(	(
		(!(strcmp(tmp1, "T/C")) || !(strcmp(tmp1, "t/c"))   )
		&&
		!(strcmp(tmp2, "65/35"))
		)
		||
		(
		(!(strcmp(tmp1, "C/T")) || !(strcmp(tmp1, "c/t"))   )
		&&
		!(strcmp(tmp2, "60/40"))
		)
	  )
	{
		*ppp = '\0';
	}
	else
	{
		if(!flag)
		{
			*ppp = '\0';
		}
	}
}

int main(void)
{
    FILE *stream, *fp;  
    char buf[BUFSIZE], *p, *pb, peibi[30];
    
    p = buf;
    pb = peibi;
    
    if((stream = fopen("D:\\code\\sha.txt","r+")) == NULL)
    {
        fprintf(stderr,"Cannot open output file.\n");
        return 0;
    }
    
	getstr_from_file(p, stream);
    
    while(strcmp(p,"eof") != 0)
    {
    	printf("%s\n",buf);
    	get_peibi_from_str(pb,buf);
    	printf("pb:%s\n", pb);
    	write_str_to_outfile(pb,fp);
    	getstr_from_file(p, stream);
    }

    fclose(stream);
    
    return 0;
}


