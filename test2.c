#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define INPUT_BUF_SIZE	200				/*键盘输入时的最大长度字符数*/

#define YARN_NAME_SIZE	100				/*纱线品种名称长度*/
#define CLOTH_NAME_SIZE	200				/*棉布品种名称长度*/

#define NAME_SIGN_SIZE	20				/*把每一个品种名称分解成sign,sign的长度*/
#define	NAME_SIGN_COUNT	20				/*把每一个品种名称分解成sign的个数*/

#define MATERIAL_NAME_SIZE	10			/*原料名称长度*/
#define MATERIAL_CONUT		5			/*每一种纱中的原料种类数*/
#define CLOTH_YARN_COUNT	5			/*经纱/纬纱中的纱线种类数*/

const static char yarn_flag [][NAME_SIGN_SIZE] = {
	{'1','3','1','2','1','\0'},						/*T/C29T*/
	{'1','3','1','2','3','2','1','\0'	},			/*T/C65/35 29T*/
	{'1','2','3','1','2','2','1','\0'},				/*T65/C35 29T*/
	{'1','2','1','\0'},								/*C29T*/
	{'1','3','1','2','8','2','1','\0'},				/*T/C29+20D*/
	{'1','3','1','2','7','2','1','\0'},				/* T/C18X2D */
	{'1','3','1','2','3','2','2','7','2','1','\0'}	/*C/T60/40 18X2D*/

};

/*纱线*/
struct Order_name_yarn
{
	char name[YARN_NAME_SIZE];			/*品种名称全称*/
	char material[MATERIAL_CONUT][MATERIAL_NAME_SIZE];		/*原料代号,长度为:MATERIAL_NAME_SIZE,一共有	MATERIAL_COUNT个原料*/
	
	float proportion[MATERIAL_CONUT];		/*原料混比比例:保留2位小数,最多MATERIAL_CONUT个原料*/
	
	float tex;				/*号数*/
	unsigned int plying;	/*股数*/
	
	char use[6]; 			/*用途*/
	char flag[2];			/*标志*/
	char explain[20];		/*说明*/
	
	
	
	
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
