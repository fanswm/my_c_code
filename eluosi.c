#include "stdio.h"
 
#include "conio.h"
 
#include "stdlib.h"
 
#include "windows.h"
 
#include "time.h"
 
#define random( x ) (rand() % x)
 
#define N 20
 
#define M 10
 
#define K 7
 
#define T 4
 
#define F 10
 
int zhong[2] = { 1, 1 }, xing[2] = { 1, 0 };                                                                                            /* 种类和形状 */
 
int hang, lie;                                                                                                                          /* 行行列 */
 
int sudu = 600;                                                                                                                         /* 游戏速度 */
 
char leixing[5][10] = { "母鸡级", "野鸡级", "飞鸟级", "绝杀级", "纠结级" };                                                                            /* 游戏类型 */
 
int jishu;                                                                                                                              /* 级数 */
 
int fenshu;                                                                                                                             /* 得分 */
 
int h[3][3];                                                                                                                            /* 中间量 */
 
int s[N][M] = { { 0, 0, 0, 2, 2, 2 }, { 0, 0, 0, 0, 2 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
 
        { 0 },{ 0, 0, 0, 0 }, { 0 } }; /*当前状态*/
 
int a[K][T][3][3] =
 
{
    { { 0, 0, 0, 0, 2, 2, 0, 2, 2 }, { 0, 0, 0, 0, 2, 2, 0, 2, 2 }, { 0, 0, 0, 0, 2, 2, 0, 2, 2 }, { 0, 0, 0, 0, 2, 2, 0, 2, 2 } }, /* 0 */
 
    { { 0, 0, 0, 0, 2, 0, 2, 2, 2 }, { 0, 2, 0, 0, 2, 2, 0, 2, 0 }, { 0, 0, 0, 2, 2, 2, 0, 2, 0 }, { 0, 2, 0, 2, 2, 0, 0, 2, 0 } }, /* +| */
 
    { { 0, 0, 0, 0, 0, 2, 2, 2, 2 }, { 0, 2, 0, 0, 2, 0, 0, 2, 2 }, { 0, 0, 0, 2, 2, 2, 2, 0, 0 }, { 0, 2, 2, 0, 0, 2, 0, 0, 2 } }, /* 7 */
 
    { { 0, 0, 0, 2, 2, 2, 0, 0, 2 }, { 0, 2, 0, 0, 2, 0, 2, 2, 0 }, { 0, 0, 0, 2, 0, 0, 2, 2, 2 }, { 0, 2, 2, 0, 2, 0, 0, 2, 0 } }, /* L */
 
    { { 0, 2, 0, 0, 2, 0, 0, 2, 0 }, { 0, 0, 0, 0, 0, 0, 2, 2, 2 }, { 0, 2, 0, 0, 2, 0, 0, 2, 0 }, { 0, 0, 0, 0, 0, 0, 2, 2, 2 } }, /* 1 */
 
    { { 0, 0, 0, 0, 2, 2, 2, 2, 0 }, { 0, 2, 0, 0, 2, 2, 0, 0, 2 }, { 0, 0, 0, 0, 2, 2, 2, 2, 0 }, { 0, 2, 0, 0, 2, 2, 0, 0, 2 } }, /* 5 */
 
    { { 0, 0, 0, 2, 2, 0, 0, 2, 2 }, { 0, 0, 2, 0, 2, 2, 0, 2, 0 }, { 0, 0, 0, 2, 2, 0, 0, 2, 2 }, { 0, 0, 2, 0, 2, 2, 0, 2, 0 } }, /* z */
};
 
void gotoxy( int x, int y )
 
{
    COORD c;
 
    c.X = x - 1; c.Y = y - 1;
 
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
}
 
 
void Disp()  /* 输出 */
 
{
    int i, j;
 
    for ( i = 2; i < N; i++ )
 
    {
        printf( "%c", 3 );
 
        for ( j = 0; j < M; j++ )
 
        {
            if ( s[i][j] == 0 )
 
            {
                printf( "  " );
            }else  {
                printf( "■" );
            }
        }
 
        printf( "%c", 3 );
 
        if ( i == 6 )
            printf( "            %s", leixing[jishu - 1] );
 
        if ( i == 8 )
            printf( "            %c%c%c", h[0][0], h[0][1], h[0][2] );
 
        if ( i == 9 )
            printf( "            %c%c%c", h[1][0], h[1][1], h[1][2] );
 
        if ( i == 10 )
            printf( "            %c%c%c", h[2][0], h[2][1], h[2][2] );
 
        if ( i == 12 )
            printf( "            得分：%2d", fenshu );
 
        printf( "\n" );
    }
 
    for ( i = 0; i < 2 * M + 2; i++ )
 
    {
        printf( "%c", 2 );
    }
 
    printf( "\n\n操作说明：4左移，6右移，5下移, 8变形,+加分数，7重来，9或Esc后退出\n" );
}
 
 
void xiaohang()
 
{
    int i, j, k;
 
    for ( i = 3; i >= 0; i-- ) /* 先变再判断 */
 
    {
        for ( j = 0; j < M; j++ )
 
        {
            if ( s[hang + i][j] == 0 )
 
            {
                break;                          /* 判断第i行是否有空格 */
            }
        }
 
        if ( j == M )                                   /*若第i行没空格消去第i行*/
 
        {
            fenshu++;
 
            for ( k = hang + i - 1; k >= 0; k-- )   /* 这里，赋值，因为还是要判断该行 */
 
            {
                for ( j = 0; j < M; j++ )
 
                {
                    s[k + 1][j] = s[k][j];
                }
            }
 
            i++;
        }
    }
}
 
 
int Down()                      /* 分三种情况，一是到下边界，二是2的下面不为空或不为2，三是继续下落 */
 
{
    int i, j;
 
    if ( hang + 3 == N )    /*若方块在下边界则将方块由2变1*//*判断是否在下边界*/
 
    {
        for ( i = 0; i < 3; i++ )
 
        {
            for ( j = 0; j < 3; j++ )
 
            {
                if ( s[hang + i][lie + j] == 2 )
 
                {
                    s[hang + i][lie + j] = 1;
                }
            }
        }
 
        xiaohang();             /* 判断是否可以消行 */
 
        return(0);              /* 注意 */
    }
 
/*========================================*/
 
    for ( i = 0; i < 3; i++ )       /* 方块下不为0，2 */
 
    {
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 && s[hang + i + 1][lie + j] == 1 )
 
            {
                break;          /*方块下方不空退出内循环*/
            }
        }
 
        if ( j < 3 )
 
        {
            break;                  /*方块下方不空退出外循环*/
        }
    }
 
    if ( i < 3 || j < 3 )                   /* 若已触到则将方块由2变1* / */
 
    {
        for ( i = 0; i < 3; i++ )       /* 变1 */
 
        {
            for ( j = 0; j < 3; j++ )
 
            {
                if ( s[hang + i][lie + j] == 2 )
 
                {
                    s[hang + i][lie + j] = 1;
                }
            }
        }
 
        xiaohang();             /* 判断是否可以消行 */
 
        return(0);              /* 注意 */
    }
 
/*=====================================*/
 
    hang++;                         /* 行自增 */
 
    for ( i = N - 1; i >= 0; i-- )  /* 继续下落 */
 
    {
        for ( j = 0; j < M; j++ )
 
        {
            if ( s[i][j] == 2 )
 
            {
                s[i + 1][j] = s[i][j];
 
                s[i][j] = 0; /*方块下移*/
            }
        }
    }
 
    return(1);
}
 
 
void kuaisu()
 
{
    int k = 1;
 
    while ( k != 0 )
 
    {
        k = Down();
    }
}
 
 
void Right()  /* 分三种情况，一是到右界退出，二是方块右方不空退出，三是前两种不符，右移 */
 
{
    int i, j;
 
    for ( i = 0; i < N; i++ )
 
    {
        if ( s[i][M - 1] == 2 )
 
        {
            return; /* 已经在右边界退出 */
        }
    }
 
    for ( i = 0; i < 3; i++ )
 
    {
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 )
 
            {
                if ( s[hang + i][lie + j + 1] == 1 )    /* 等于2的右边不能为1 */
 
                {
                    return;                         /* 方块右方不空退出 */
                }
            }
        }
    }
 
    lie++;                                                          /* 列自增 */
 
    for ( j = 2; j >= 0; j-- )
 
    {
        for ( i = 0; i < 3; i++ )
 
        {
            if ( s[hang + i][lie - 1 + j] == 2 )
 
            {
                s[hang + i][lie + j] = s[hang + i][lie + j - 1];
 
                s[hang + i][lie + j - 1] = 0;   /* 方块右移 */
            }
        }
    }
}
 
 
void Left()                                                     /* 分三种情况，一是到左界退出，二是方块左方不空退出，三是前两种不符，左移 */
 
{
    int i, j;
 
    for ( i = 0; i < N; i++ )
 
    {
        if ( s[i][0] == 2 )
 
        {
            return; /* 已经在左边界退出 */
        }
    }
 
    for ( i = 0; i < 3; i++ )
 
    {
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 )
 
            {
                if ( s[hang + i][lie + j - 1] == 1 )    /* 等于2的左边不能为1 */
 
                {
                    return;                         /* 方块左方不空退出 */
                }
            }
        }
    }
 
    lie--;                                                          /* 列自- */
 
    for ( j = 0; j < 3; j++ )
 
    {
        for ( i = 0; i < 3; i++ )
 
        {
            if ( s[hang + i][lie + j + 1] == 2 )
 
            {
                s[hang + i][lie + j] = s[hang + i][lie + j + 1];
 
                s[hang + i][lie + j + 1] = 0;   /* 方块左移 ,把等于2的值给左边，该位置再等0*/
            }
        }
    }
}
 
 
void Bian()                                                     /* 变形 */
 
{
    int i, j;
 
    if ( xing[0] >= 3 )
 
    {
        xing[0] = 0;
    }else  {
        xing[0]++;
    }
 
    if ( hang + 3 > N || lie + 3 > M || lie < 0 )
 
    {
        return; /* 边界注意有的不能转，画图即知 */
    }
 
    for ( i = hang; i < hang + 3; i++ )
 
    {
        for ( j = lie; j < lie + 3; j++ )
 
        {
            if ( s[i][j] == 1 && a[zhong[0]][xing[0]][i - hang][j - lie] == 2 )     /* 碰撞即不能旋转 */
 
            {
                return;
            }
 
            if ( s[i][j] != 1 )                                                     /* 等于1的变为0 */
 
            {
                s[i][j] = a[zhong[0]][xing[0]][i - hang][j - lie];
            }
        }
    }
}
 
 
int jie()
 
{
    int i;
 
    for ( i = 0; i < M; i++ ) /* 结束游戏 */
 
    {
        if ( s[3][i] == 1 )
 
        {
            printf( "geams over !%c\n", 2 );
 
            return(1);
        }
    }
 
    return(0);
}
 
 
void chushi() /* 初始化 */
 
{
    int i;
 
    int j;
 
    int k;
 
    srand( (unsigned) time( NULL ) );
 
    k = random( 2 );
 
    if ( jishu == 1 )
 
    {
        for ( i = 0; i < N; i++ )
 
        {
            for ( j = 0; j < M; j++ )
 
            {
                s[i][j] = 0;
            }
        }
 
        return;
    }
 
    for ( i = 0; i < N; i++ )
 
    {
        if ( i >= N - jishu - 1 )
 
        {
            for ( j = 0; j < M; j++ )
 
            {
                k = random( 2 );
 
                s[i][j] = k;
            }
        }else  {
            for ( j = 0; j < M; j++ )
 
            {
                s[i][j] = 0;
            }
        }
    }
}
 
 
void shezhi()  /* 设置级别 */
 
{
    fenshu = 0;
 
    printf( "\t\t\t打酱油游戏==！\n" );
 
    do
 
    {
        printf( "你想挑战(有1，2，3，4,5级)：" );
 
        scanf( "%d", &jishu );
    }
    while ( jishu <= 0 || jishu > 5 );
 
    switch ( jishu )
 
    {
    case 5: sudu = 10; chushi(); break;
 
    case 4: sudu = 100; chushi(); break;
 
    case 3: sudu = 200; chushi(); break;
 
    case 2: sudu = 400; chushi(); break;
 
    case 1: chushi();
 
    default: sudu = 600;
    }
 
    system( "CLS" );
 
/* chushi(); */
}
 
 
int Have() /*判断是否有可移动方块,没有返回1，否则返回0，木有则重新随机生成方块*/
 
{
    int i, j;
 
    for ( i = 0; i < 3; i++ )
 
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 )
 
            {
                return(0);
            }
        }
 
    return(1);
}
 
 
void Add()                      /*随机生成方块*/
 
{
    int i, j;
 
    srand( (unsigned) time( NULL ) );
 
    zhong[1] = random( K ); /* 初始化 */
 
    xing[1] = random( T );  /* 初始化 */
 
    for ( i = 0; i < 3; i++ )
 
        for ( j = 3; j < 3 + 3; j++ )
 
        {
            h[i][j - 3] = a[zhong[1]][xing[1]][i][j - 3];
        }
 
    return;
}
 
 
void suiji()  /* 把随机生成的方块给数组 */
 
{
    hang = 0;
 
    lie = 3;
 
    zhong[0] = zhong[1];
 
    xing[0] = xing[1];
 
    int i, j;
 
    for ( i = 0; i < 3; i++ )
 
    {
        for ( j = 3; j < 3 + 3; j++ )
 
        {
            s[i][j] = h[i][j - 3]; /* 生成方块,j-3就是从0开始了 */
        }
    }
 
    return;
}
 
 
int main()
 
{
    char x = '0';
 
    while ( x != 'n' && x != 'N' )
 
    {
        shezhi();
 
        Add();
 
        suiji();
 
        char c = 'A';   /* 初始化，啥都木关系 */
 
        char ch = 'b';  /* 初始化，啥都木关系 */
 
        while ( 1 )     /*判断是否有按键，没有循环输出i,否则停,conio.h*/
 
        {
            if ( !kbhit() )
 
            {
                c = '2';
            }else  {
                c = getch();
            }
 
            if ( c == ' ' )
 
            {
                ch = getch(); /* 暂停键要相同 */
 
                while ( ch != ' ' )
 
                {
                    ch = getch();
                }
            }
 
/* system("CLS");/ *清屏，TC用clrscr();，VC用system("CLS");* / */
 
            switch ( c )
 
            {
            case '7': shezhi();             /* 重来 */
 
            case '4': Left(); break;        /*左移*/
 
            case '6': Right(); break;       /*右移*/
 
            case '9': case 27: return(0);   /*按9或Esc(=27)后退出*/
 
            case '8': Bian(); break;        /* 旋转 */
 
            case '5': kuaisu(); break;      /* 快速下移 */
 
            case '+':
 
            {
                fenshu++;
 
                break;
            }
 
            case '2': Down(); break; /*下移*/
            }
 
            if ( fenshu > F )
 
            {
                jishu++;
 
                if ( jishu > 5 )
 
                {
                    printf( "你赢了！\n" );
 
                    return(0);
                }
 
                switch ( jishu )
 
                {
                case 5: sudu = 10; break;
 
                case 4: sudu = 100; break;
 
                case 3: sudu = 200; break;
 
                case 2: sudu = 400; break;
 
                case 1:;
 
                default: sudu = 600;
                }
 
                chushi();
 
                fenshu = 0;
            }
 
            if ( Have() )
 
            {
                suiji();
 
                Add();
            }
 
            if ( jie() )
 
            {
                break;
            }
 
/* system("CLS"); */
 
            gotoxy( 1, 1 );
 
            Disp(); /* 输出影像 */
 
            if ( c == '5' )
 
            {
                Sleep( 0 );
            }else  {
                Sleep( sudu );
            }
        }
 
        printf( "是否继续（N / n 退出，其他继续）:\n" );
 
        x = getch();
    }
 
    getch();
 
    return(0);
}