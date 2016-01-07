#include <stdio.h>
#include <grp.h>
#include <math.h>

#define PI 3.14159265


void putblock(int x,int y,int color,int width)
/*以要画的方块的左上角的起点坐标为x,y,颜色，宽度*/
{
	int i,j;
	for(i=0;i<width;i++)
		for(j=0;j<width;j++)
			putpixel(x+i,y+j,color);	
}

void putlftline(int x,int y,int color,int width)
/*以要画的方块的左上角的起点坐标为x,y,颜色，宽度(指水平投影的宽度)*/
{
	int i;
	for(i=0;i<width;i++)	
		putpixel(x+i,y+i,color);
}

void putrtline(int x,int y,int color,int width)
/*以要画的方块的左上角的起点坐标为x,y,颜色，宽度(指水平投影的宽度)*/
{
	int i;
	for(i=0;i<width;i++)
		putpixel(x+i,y-i,color);
}

void yuan(int x0,int y0,int r,int du,int color)
/*画圆，圆心（x0,y0）;半径r;画过的度数0-360；颜色color;*/
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
	/*在屏幕左上角画出一个蓝色的方块*/
	putlftline(0,0,RED,100); 		
	/*在上述方块画一条红色的对角线*/
	putrtline(0,100,WHITE,100);

	putblock(100,100,GREEN,100);	
	/*接着角画一个绿色的方块*/
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
