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
 
int zhong[2] = { 1, 1 }, xing[2] = { 1, 0 };                                                                                            /* �������״ */
 
int hang, lie;                                                                                                                          /* ������ */
 
int sudu = 600;                                                                                                                         /* ��Ϸ�ٶ� */
 
char leixing[5][10] = { "ĸ����", "Ұ����", "����", "��ɱ��", "���ἶ" };                                                                            /* ��Ϸ���� */
 
int jishu;                                                                                                                              /* ���� */
 
int fenshu;                                                                                                                             /* �÷� */
 
int h[3][3];                                                                                                                            /* �м��� */
 
int s[N][M] = { { 0, 0, 0, 2, 2, 2 }, { 0, 0, 0, 0, 2 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
 
        { 0 },{ 0, 0, 0, 0 }, { 0 } }; /*��ǰ״̬*/
 
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
 
 
void Disp()  /* ��� */
 
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
                printf( "��" );
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
            printf( "            �÷֣�%2d", fenshu );
 
        printf( "\n" );
    }
 
    for ( i = 0; i < 2 * M + 2; i++ )
 
    {
        printf( "%c", 2 );
    }
 
    printf( "\n\n����˵����4���ƣ�6���ƣ�5����, 8����,+�ӷ�����7������9��Esc���˳�\n" );
}
 
 
void xiaohang()
 
{
    int i, j, k;
 
    for ( i = 3; i >= 0; i-- ) /* �ȱ����ж� */
 
    {
        for ( j = 0; j < M; j++ )
 
        {
            if ( s[hang + i][j] == 0 )
 
            {
                break;                          /* �жϵ�i���Ƿ��пո� */
            }
        }
 
        if ( j == M )                                   /*����i��û�ո���ȥ��i��*/
 
        {
            fenshu++;
 
            for ( k = hang + i - 1; k >= 0; k-- )   /* �����ֵ����Ϊ����Ҫ�жϸ��� */
 
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
 
 
int Down()                      /* �����������һ�ǵ��±߽磬����2�����治Ϊ�ջ�Ϊ2�����Ǽ������� */
 
{
    int i, j;
 
    if ( hang + 3 == N )    /*���������±߽��򽫷�����2��1*//*�ж��Ƿ����±߽�*/
 
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
 
        xiaohang();             /* �ж��Ƿ�������� */
 
        return(0);              /* ע�� */
    }
 
/*========================================*/
 
    for ( i = 0; i < 3; i++ )       /* �����²�Ϊ0��2 */
 
    {
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 && s[hang + i + 1][lie + j] == 1 )
 
            {
                break;          /*�����·������˳���ѭ��*/
            }
        }
 
        if ( j < 3 )
 
        {
            break;                  /*�����·������˳���ѭ��*/
        }
    }
 
    if ( i < 3 || j < 3 )                   /* ���Ѵ����򽫷�����2��1* / */
 
    {
        for ( i = 0; i < 3; i++ )       /* ��1 */
 
        {
            for ( j = 0; j < 3; j++ )
 
            {
                if ( s[hang + i][lie + j] == 2 )
 
                {
                    s[hang + i][lie + j] = 1;
                }
            }
        }
 
        xiaohang();             /* �ж��Ƿ�������� */
 
        return(0);              /* ע�� */
    }
 
/*=====================================*/
 
    hang++;                         /* ������ */
 
    for ( i = N - 1; i >= 0; i-- )  /* �������� */
 
    {
        for ( j = 0; j < M; j++ )
 
        {
            if ( s[i][j] == 2 )
 
            {
                s[i + 1][j] = s[i][j];
 
                s[i][j] = 0; /*��������*/
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
 
 
void Right()  /* �����������һ�ǵ��ҽ��˳������Ƿ����ҷ������˳�������ǰ���ֲ��������� */
 
{
    int i, j;
 
    for ( i = 0; i < N; i++ )
 
    {
        if ( s[i][M - 1] == 2 )
 
        {
            return; /* �Ѿ����ұ߽��˳� */
        }
    }
 
    for ( i = 0; i < 3; i++ )
 
    {
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 )
 
            {
                if ( s[hang + i][lie + j + 1] == 1 )    /* ����2���ұ߲���Ϊ1 */
 
                {
                    return;                         /* �����ҷ������˳� */
                }
            }
        }
    }
 
    lie++;                                                          /* ������ */
 
    for ( j = 2; j >= 0; j-- )
 
    {
        for ( i = 0; i < 3; i++ )
 
        {
            if ( s[hang + i][lie - 1 + j] == 2 )
 
            {
                s[hang + i][lie + j] = s[hang + i][lie + j - 1];
 
                s[hang + i][lie + j - 1] = 0;   /* �������� */
            }
        }
    }
}
 
 
void Left()                                                     /* �����������һ�ǵ�����˳������Ƿ����󷽲����˳�������ǰ���ֲ��������� */
 
{
    int i, j;
 
    for ( i = 0; i < N; i++ )
 
    {
        if ( s[i][0] == 2 )
 
        {
            return; /* �Ѿ�����߽��˳� */
        }
    }
 
    for ( i = 0; i < 3; i++ )
 
    {
        for ( j = 0; j < 3; j++ )
 
        {
            if ( s[hang + i][lie + j] == 2 )
 
            {
                if ( s[hang + i][lie + j - 1] == 1 )    /* ����2����߲���Ϊ1 */
 
                {
                    return;                         /* �����󷽲����˳� */
                }
            }
        }
    }
 
    lie--;                                                          /* ����- */
 
    for ( j = 0; j < 3; j++ )
 
    {
        for ( i = 0; i < 3; i++ )
 
        {
            if ( s[hang + i][lie + j + 1] == 2 )
 
            {
                s[hang + i][lie + j] = s[hang + i][lie + j + 1];
 
                s[hang + i][lie + j + 1] = 0;   /* �������� ,�ѵ���2��ֵ����ߣ���λ���ٵ�0*/
            }
        }
    }
}
 
 
void Bian()                                                     /* ���� */
 
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
        return; /* �߽�ע���еĲ���ת����ͼ��֪ */
    }
 
    for ( i = hang; i < hang + 3; i++ )
 
    {
        for ( j = lie; j < lie + 3; j++ )
 
        {
            if ( s[i][j] == 1 && a[zhong[0]][xing[0]][i - hang][j - lie] == 2 )     /* ��ײ��������ת */
 
            {
                return;
            }
 
            if ( s[i][j] != 1 )                                                     /* ����1�ı�Ϊ0 */
 
            {
                s[i][j] = a[zhong[0]][xing[0]][i - hang][j - lie];
            }
        }
    }
}
 
 
int jie()
 
{
    int i;
 
    for ( i = 0; i < M; i++ ) /* ������Ϸ */
 
    {
        if ( s[3][i] == 1 )
 
        {
            printf( "geams over !%c\n", 2 );
 
            return(1);
        }
    }
 
    return(0);
}
 
 
void chushi() /* ��ʼ�� */
 
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
 
 
void shezhi()  /* ���ü��� */
 
{
    fenshu = 0;
 
    printf( "\t\t\t������Ϸ==��\n" );
 
    do
 
    {
        printf( "������ս(��1��2��3��4,5��)��" );
 
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
 
 
int Have() /*�ж��Ƿ��п��ƶ�����,û�з���1�����򷵻�0��ľ��������������ɷ���*/
 
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
 
 
void Add()                      /*������ɷ���*/
 
{
    int i, j;
 
    srand( (unsigned) time( NULL ) );
 
    zhong[1] = random( K ); /* ��ʼ�� */
 
    xing[1] = random( T );  /* ��ʼ�� */
 
    for ( i = 0; i < 3; i++ )
 
        for ( j = 3; j < 3 + 3; j++ )
 
        {
            h[i][j - 3] = a[zhong[1]][xing[1]][i][j - 3];
        }
 
    return;
}
 
 
void suiji()  /* ��������ɵķ�������� */
 
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
            s[i][j] = h[i][j - 3]; /* ���ɷ���,j-3���Ǵ�0��ʼ�� */
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
 
        char c = 'A';   /* ��ʼ����ɶ��ľ��ϵ */
 
        char ch = 'b';  /* ��ʼ����ɶ��ľ��ϵ */
 
        while ( 1 )     /*�ж��Ƿ��а�����û��ѭ�����i,����ͣ,conio.h*/
 
        {
            if ( !kbhit() )
 
            {
                c = '2';
            }else  {
                c = getch();
            }
 
            if ( c == ' ' )
 
            {
                ch = getch(); /* ��ͣ��Ҫ��ͬ */
 
                while ( ch != ' ' )
 
                {
                    ch = getch();
                }
            }
 
/* system("CLS");/ *������TC��clrscr();��VC��system("CLS");* / */
 
            switch ( c )
 
            {
            case '7': shezhi();             /* ���� */
 
            case '4': Left(); break;        /*����*/
 
            case '6': Right(); break;       /*����*/
 
            case '9': case 27: return(0);   /*��9��Esc(=27)���˳�*/
 
            case '8': Bian(); break;        /* ��ת */
 
            case '5': kuaisu(); break;      /* �������� */
 
            case '+':
 
            {
                fenshu++;
 
                break;
            }
 
            case '2': Down(); break; /*����*/
            }
 
            if ( fenshu > F )
 
            {
                jishu++;
 
                if ( jishu > 5 )
 
                {
                    printf( "��Ӯ�ˣ�\n" );
 
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
 
            Disp(); /* ���Ӱ�� */
 
            if ( c == '5' )
 
            {
                Sleep( 0 );
            }else  {
                Sleep( sudu );
            }
        }
 
        printf( "�Ƿ������N / n �˳�������������:\n" );
 
        x = getch();
    }
 
    getch();
 
    return(0);
}