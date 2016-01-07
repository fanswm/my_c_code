#include <stdio.h>
#include <winsock2.h>
#include <mysql.h>
/*���ݿ������ú�*/

#define HOST "localhost"
#define USERNAME "fanswm"
#define PASSWORD "123456fan"
#define DATABASE "mysql"

int main()
{
    char *query;
    query="select * from event";
    query_sql(query);
    return 0;
}

void query_sql(char* sql)
{
    MYSQL my_connection; /*����һ�����ݿ�����*/
    int res; /*ִ��sql�Z���ķ��ر�־*/
    MYSQL_RES *res_ptr; /*ָ���ѯ�����ָ��*/
    MYSQL_FIELD *field; /*�ֶνṹָ��*/
    MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
    int row, column; /*��ѯ���ص�����������*/
    int i, j;

    /*��ʼ��mysql����my_connection*/
    mysql_init(&my_connection); /*����mysql����*/
    if (NULL != mysql_real_connect(&my_connection,
                                   HOST,
                                   USERNAME,
                                   PASSWORD,
                                   DATABASE,
                                   0,
                                   NULL,
                                   CLIENT_FOUND_ROWS)
        ) /*���ӳɹ�*/
    {
        printf("���ݿ��ѯquery_sql���ӳɹ���\n"); /*���ò�ѯ����Ϊgbk����֧������*/
        mysql_query(&my_connection, "set names gbk");
        res = mysql_query(&my_connection, sql);
        if (res) /*ִ��ʧ��*/
        {
            printf("Error�� mysql_query !\n");
            /*�ر�����*/
            mysql_close(&my_connection);
        }
        else
            /*���ھʹ���ִ�гɹ���*/
        {
            /*����ѯ�ĽY����res_ptr*/
            res_ptr = mysql_store_result(&my_connection);
            /*��������Ϊ�գ��Ͱѽ��print*/
            if (res_ptr)
            {
                /*ȡ�ýY����������*/
                column = mysql_num_fields(res_ptr);
                row = mysql_num_rows(res_ptr);
                printf("��ѯ�� %d �� \n", row);

                /*����Y�����ֶ���*/
                for (i = 0; field = mysql_fetch_field(res_ptr); i++)
                    printf("%10s ", field->name);
                printf("\n");

                /*��������Y��*/
                for (i = 1; i < row+1; i++)
                {
                    result_row = mysql_fetch_row(res_ptr);
                    for (j = 0; j < column; j++)
                        printf("%10s ", result_row[j]);
                    printf("\n");
                }
            }
            /*��Ҫ���˹ر�����*/
            mysql_close(&my_connection);
        }
    }
    else
    {
        printf("���ݿ�����ʧ��");
    }
}
