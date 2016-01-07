#include <stdio.h>
#include <grp.h>
#include <math.h>

#define PI 3.14159265


void putblock(int x,int y,int color,int width)
/*��Ҫ���ķ�������Ͻǵ��������Ϊx,y,��ɫ������*/
{
	int i,j;
	for(i=0;i<width;i++)
		for(j=0;j<width;j++)
			putpixel(x+i,y+j,color);	
}

void putlftline(int x,int y,int color,int width)
/*��Ҫ���ķ�������Ͻǵ��������Ϊx,y,��ɫ������(ָˮƽͶӰ�Ŀ���)*/
{
	int i;
	for(i=0;i<width;i++)	
		putpixel(x+i,y+i,color);
}

void putrtline(int x,int y,int color,int width)
/*��Ҫ���ķ�������Ͻǵ��������Ϊx,y,��ɫ������(ָˮƽͶӰ�Ŀ���)*/
{
	int i;
	for(i=0;i<width;i++)
		putpixel(x+i,y-i,color);
}

void yuan(int x0,int y0,int r,int du,int color)
/*��Բ��Բ�ģ�x0,y0��;�뾶r;�����Ķ���0-360����ɫcolor;*/
{
	int i;
	double x,y;
	double fen;
	for(i=0;i<=du*4;i++)
	{
		fen=PI/720*i;
		x=x0+r*sin(fen);
		y=y0+r*cos(fen);
		putpixel(x,y,color);
	}
}

void main()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");

	putblock(0,0,BLUE,100); 		
	/*����Ļ���Ͻǻ���һ����ɫ�ķ���*/
	putlftline(0,0,RED,100); 		
	/*���������黭һ����ɫ�ĶԽ���*/
	putrtline(0,100,WHITE,100);

	putblock(100,100,GREEN,100);	
	/*���Žǻ�һ����ɫ�ķ���*/
	putlftline(100,100,RED,100);
	putrtline(100,200,WHITE,100);

	putblock(200,200,YELLOW,100);
	putlftline(200,200,RED,100);
	putrtline(200,300,RED,100);

	putblock(300,300,WHITE,100);
	putlftline(300,300,RED,100);
	putrtline(300,400,BLACK,100);

	putblock(400,400,BLUE,100);
	putlftline(400,400,RED,100);
	putrtline(400,500,GREEN,100);

	yuan(250,250,100*sin(PI/4),360,RED);
	
	putlftline(100,0,RED,500);
	getch();
}