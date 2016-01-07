#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define INPUT_BUF_SIZE	200				/*��������ʱ����󳤶��ַ���*/

#define YARN_NAME_SIZE	100				/*ɴ��Ʒ�����Ƴ���*/
#define CLOTH_NAME_SIZE	200				/*�޲�Ʒ�����Ƴ���*/

#define NAME_SIGN_SIZE	20				/*��ÿһ��Ʒ�����Ʒֽ��sign,sign�ĳ���*/
#define	NAME_SIGN_COUNT	20				/*��ÿһ��Ʒ�����Ʒֽ��sign�ĸ���*/

#define MATERIAL_NAME_SIZE	10			/*ԭ�����Ƴ���*/
#define MATERIAL_CONUT		5			/*ÿһ��ɴ�е�ԭ��������*/
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
	char material[MATERIAL_CONUT][MATERIAL_NAME_SIZE];		/*ԭ�ϴ���,����Ϊ:MATERIAL_NAME_SIZE,һ����	MATERIAL_COUNT��ԭ��*/
	
	float proportion[MATERIAL_CONUT];		/*ԭ�ϻ�ȱ���:����2λС��,���MATERIAL_CONUT��ԭ��*/
	
	float tex;				/*����*/
	unsigned int plying;	/*����*/
	
	char use[6]; 			/*��;*/
	char flag[2];			/*��־*/
	char explain[20];		/*˵��*/
	
	
	
	
	int test;
	char t[20];
};

typedef struct Order_name_yarn Yarn_name;
typedef Yarn_name * p_Yarn_name;

int main()
{
	Yarn_name n[1];
	p_Yarn_name p;
	
	char *pt;

	p = n;
	pt = p->t;
	
	strcpy(pt,"fanswmtest");	
	p->test = 8;
	printf("name.test = %d\n",p->test);
	printf("pt=%s\n",pt);
	
}
