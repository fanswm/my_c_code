#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum {NAME,PARENS,BRACKETS};

void dcl(void);
void dirdcl(void);
int gettoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];


char  buf[BUFSIZE];  
int  bufp = 0;   


int main()
{
	while(gettoken() != EOF) /*该行的第一个记号是数据类型*/
	{
		strcpy(datatype, token);
		out[0] = '\0';
		dcl(); /*分析该行的其余部分*/
		if(tokentype != '\n')
		{
			printf("syntax error\n");
		}
		printf("%s: %s %s\n",name,out,datatype);
	}
	return 0;
}

/*对一个声明符进行语法分析*/
void dcl(void)
{
	int ns;
 
	for(ns = 0;gettoken() == '*';) /*统计字符*的个数*/
	{
		ns++;
	}
	dirdcl();
	while(ns-- > 0)
	{
		strcat(out," pointer to");
	}
}

/*分析一个直接声明*/
void dirdcl(void)
{
	int type;

	if(tokentype == '(' ) /*形式为(dcl)*/
	{
		dcl();
		if(tokentype != ')' )
		{
			printf("error: missing )\n");
		}
	}
	else if(tokentype == NAME) /*变量名*/
	{
		strcpy(name,token);
	}
	else
	{
		printf("error: expected name or (dcl)\n");
	}
 
	while((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if(type == PARENS)
		{
			strcat(out," function returning");
		}
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}


/*返回一个标记*/
int gettoken(void)
{
	int c,getch(void);
	void ungetch(int);
	char *p = token;
 
	while((c = getch()) == ' ' || c == '\t')
	;
	if(c == '(' )
	{
		if((c = getch()) == ')' )
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if(c == '[' )
	{
		for(*p++ = c; (*p++ = getch()) != ']'; )
		;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if(isalpha(c))
	{
		for(*p++ = c; isalnum(c = getch());)
		{
			*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
	{
		return tokentype = c;
	}
}


int getch(void)  
/*缓冲区不为空则getch从缓冲区读出字符，否则用getchar函数直接从输入读取  */
/*常用*/
{  
	return(bufp > 0) ? buf[--bufp] : getchar();  
}  
  
void ungetch(int c)  
/*把要压回的字符放到缓冲区  */
/*常用*/
{  
	if (bufp >= BUFSIZE)  
	{  
		printf("ungetch:too many characters\n");  
	}  
	else  
        buf[bufp++] = c;  
}

/*---------------------20130811 END---------------------------*/
/*将声明转换为文字描述:
*不能处理函数中的参数类型或类似于const这样的限定符,带有不必要空格,无效的声明,都不能处理*/
