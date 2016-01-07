#include <winsock2.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>


/*���ݿ������ú�*/
#define HOST "localhost"
#define USERNAME "fanswm"
#define PASSWORD "123456fan"

#define USER_ROOT "root"
#define PASSWORD_ROOT "123456:mysql"

#define DATABASE "test"
#define DB_TB_NAME_LENTH 255
#define SQL_LENTH 1024

char tmp_sql[SQL_LENTH];

int main()
{
    void fan_create_db_at_localhost_by_user(char * dbname, char *username, char *password);
    void fan_create_table_at_db_by_user(char *, char *, char *, char *, char *);
    void fan_create_table_at_DBNAME_BASE(char *tablename);
    void fan_empty_query_by_root(char *sql);
    void fan_get_counttables_from_db(my_ulonglong *pcounttables, char *dbname, char *username, char *password);
    void fan_get_id_from_DBNAME_BASE(my_ulonglong *id);
    void fan_get_rows_from_table_at_db(my_ulonglong *rows, char *tablename, char *dbname, char *username, char *password);
    void fan_get_local_time_format_to_mysql(char *datetime);
    void fan_write_db_to_DBNAME_BASE(my_ulonglong newid, char *dbname, char *createtime, my_ulonglong counttables);
    void fan_write_table_to_DBNAME_BASE(my_ulonglong newid, char *tablename, char *createtime);
    void fan_insert_into_table_ADDRESS_of_TEL(char *name, char *phonenum, char *remark,
                                         char *username, char *password);
    void fan_insert_into_table_ADDRESS_of_TEL_by_key(char *username, char *password);
    void query_sql(char* sql);

/*
    fan_empty_query_by_root("create database dbname_base");



    fan_create_table_at_db_by_user("databasename",
                                   "id INT(4) NOT NULL,name VARCHAR(40),createtime DATETIME,counttables INT(4) DEFAULT '0'",
                                   "dbname_base",
                                   USER_ROOT,
                                   PASSWORD_ROOT);

    fan_create_db_at_localhost_by_user("tel", USER_ROOT, PASSWORD_ROOT);
    fan_create_table_at_db_by_user("family", "id INT(4) NOT NULL, name VARCHAR(40),createtime DATETIME,counttables INT(4) DEFAULT '0'","tel", USER_ROOT, PASSWORD_ROOT);
    fan_create_table_at_db_by_user("phone", "id INT(4) NOT NULL, name VARCHAR(40) NOT NULL,phoneNUM VARCHAR(21)","tel", USER_ROOT, PASSWORD_ROOT);
    fan_create_table_at_db_by_user("address", "Id INT(4) NOT NULL, Name VARCHAR(40) NOT NULL, PhoneNUM VARCHAR(21), Remarks VARCHAR(1024)", "tel", USER_ROOT, PASSWORD_ROOT);
    fan_insert_into_table_ADDRESS_of_TEL("fanyuehui", "15031164531", "good", "fanswm", "123456fan");
    */


    fan_insert_into_table_ADDRESS_of_TEL_by_key("fanswm", "123456fan");
    return 0;
}

/*��ȡ��ʱ�ı���ʱ��*/
void fan_get_local_time_format_to_mysql(char *datetime)
{
    time_t timer;
    struct tm *gmt;

    timer=time(NULL);
    gmt=localtime(&timer);
    if(gmt->tm_year + 1900 < 9999)
    {
        strftime(datetime,21,"%Y-%m-%d %H:%M:%S",gmt);
        printf("%s\n",datetime);
    }
    return;
}


/*��ȡ�����ݿ⣺dbname_base�еı�databasename�У�������*/
void fan_get_id_from_DBNAME_BASE(my_ulonglong *id)
{
    MYSQL my_conn;
    int res;
    MYSQL_RES *res_ptr;
    mysql_init(&my_conn);
    if (NULL != mysql_real_connect( &my_conn, "localhost", USER_ROOT, PASSWORD_ROOT,
                                   "dbname_base", 0, NULL, 0) )
    {
        res = mysql_query(&my_conn, "select * from databasename");
        if( !res)
        {
            res_ptr = mysql_store_result(&my_conn);
            if (res_ptr)
            {
                *id = mysql_num_rows(res_ptr);
            }
        }
        mysql_close(&my_conn);
    }
}

/*δ��: һ�㺯��*/
/*��ȡ�����ݿ⣺dbname_base�еı�databasename�У�������(id), ����id*/
void fan_get_rows_from_table_at_db(my_ulonglong *rows, char *tablename, char *dbname, char *username, char *password)
{
    MYSQL my_conn;
    int res;
    MYSQL_RES *res_ptr;

    char *sql;
    sql = tmp_sql;

    mysql_init(&my_conn);
    if (NULL != mysql_real_connect( &my_conn, "localhost", username, password,
                                   dbname, 0, NULL, 0) )
    {
        strcpy(sql, "select * from ");
        strcat(sql, tablename);
        res = mysql_query(&my_conn, sql);
        if( !res)
        {
            res_ptr = mysql_store_result(&my_conn);
            if (res_ptr)
            {
                *rows = mysql_num_rows(res_ptr);
            }
        }
        mysql_close(&my_conn);
    }
}

/*һ�㺯��*/
/*��ȡĳһ�����ݿ⣺dbname�еı��������������д�뵽pcounttables*/
void fan_get_counttables_from_db(my_ulonglong *pcounttables, char *dbname, char *username, char *password)
{
    MYSQL my_conn;
    int res;
    MYSQL_RES *res_ptr;

    mysql_init(&my_conn);
    if (NULL != mysql_real_connect( &my_conn, "localhost", username, password,
                                   dbname, 0, NULL, 0) )
    {
        res = mysql_query(&my_conn, "show tables");
        if( !res)
        {
            res_ptr = mysql_store_result(&my_conn);
            if (res_ptr)
            {
                *pcounttables = mysql_num_rows(res_ptr);
            }
        }
        mysql_close(&my_conn);
    }
}


void fan_write_table_of_db_to_DBNAME_BASE(my_ulonglong newid, char *tablename, char *createtime, char *dbname)
{
    MYSQL my_conn;
    int res;
    MYSQL_RES *res_ptr;
    MYSQL_ROW result_row;

    char *sql = tmp_sql;
    my_ulonglong counttables;
    char str[100];

    mysql_init(&my_conn);
    if (NULL != mysql_real_connect(&my_conn,
                                   "localhost",
                                   USER_ROOT,
                                   PASSWORD_ROOT,
                                   "dbname_base",
                                   0,
                                   NULL,
                                   0))
    {
        printf("fan_write_table_of_db_to_DBNAME_BASE:\n\tConnect DB OK!\n\n");

        /*INSERT INTO dbname(id,name,createtime) VALUES(newid,tablename,createtime)*/
        sprintf(str, "%d", newid);
        strcpy(sql, "INSERT INTO ");
        strcat(sql, dbname);
        strcat(sql, "(id, name, createtime) VALUES(");
        strcat(sql, str);
        strcat(sql, ",'");
        strcat(sql, tablename);
        strcat(sql, "','");
        strcat(sql, createtime);
        strcat(sql, "')");

        res = mysql_query(&my_conn, sql);
        if(res)
        {
            printf("fan_write_table_of_db_to_DBNAME_BASE:\n\tError:INSERT VALUES!\n\n");
        }
        else   /*��ѯ�ɹ�*/
        {
            printf("fan_write_table_of_db_to_DBNAME_BASE:\n\tSQL OK!\n");
        }

		/*UPDATE databasename SET counttables = counttables + 1 WHERE name = 'dbname'*/
        strcpy(sql, "UPDATE databasename SET counttables = counttables + 1 WHERE name = '");
        strcat(sql, dbname);
        strcat(sql, "'");
        res = mysql_query(&my_conn, sql);
        if(!res)
        {
            printf("fan_write_table_of_db_to_DBNAME_BASE:\n\tOK!\n\n");
        }
        mysql_close(&my_conn);
    }
    else
    {
        printf("fan_write_table_of_db_to_DBNAME_BASE:\n\tConnect DB ERROR!\n\n");
    }
}



/*�Ѵ��������ݿ�ID, ���ƣ�����ʱ�䣬���б�ĸ�����д�뵽���ݿ⣺dbname_base */
void fan_write_db_to_DBNAME_BASE(my_ulonglong newid, char *dbname, char *createtime, my_ulonglong counttables)
{
    MYSQL my_conn;
    int res;
    MYSQL_RES *res_ptr;

    char *sql = tmp_sql;
    char str[100];

    mysql_init(&my_conn);
    if (NULL != mysql_real_connect(&my_conn,
                                   "localhost",
                                   USER_ROOT,
                                   PASSWORD_ROOT,
                                   "dbname_base",
                                   0,
                                   NULL,
                                   0))
    {
        printf("write_dbname_to_DBNAME_BASE:\n\tConnect DB OK!\n\n");


        sprintf(str, "%d", newid);
        strcpy(sql, "INSERT INTO databasename(id,name,createtime,counttables) VALUES(");
        strcat(sql, str);
        strcat(sql, ",'");
        strcat(sql, dbname);
        strcat(sql, "','");
        strcat(sql, createtime);
        strcat(sql, "',");
        sprintf(str, "%d", counttables);
        strcat(sql, str);
        strcat(sql, ")");

        res = mysql_query(&my_conn, sql);
        if(res)
        {
            printf("write_dbname_to_DBNAME_BASE:\n\tError:INSERT VALUES!\n\n");
        }
        else   /*��ѯ�ɹ�*/
        {
            printf("write_dbname_to_DBNAME_BASE:\n\tSQL OK!\n");
        }
        mysql_close(&my_conn);
    }
    else
    {
        printf("fan_write_db_to_DBNAME_BASE:\n\tConnect DB ERROR!\n\n");
    }
}


void fan_create_table_at_DBNAME_BASE(char *tablename)
{
    MYSQL my_connection;
    int res;

    char *sql = tmp_sql;

    strcpy(sql,tablename);
    if(strlen(sql) - 1 > 255 )
    {
        printf("Error:The tablename:%s is too long!\n\n", tablename);
        return;
    }

    mysql_init(&my_connection);
    if (NULL != mysql_real_connect(&my_connection,
                                   "localhost",
                                   USER_ROOT,
                                   PASSWORD_ROOT,
                                   "dbname_base",
                                   0,
                                   NULL,
                                   0))
    {
        printf("fan_create_table_at_DBNAME_BASE\n\tSQL conn OK!\n\n");

        /*CREATE TABLE IF NOT EXISTS (id INT(4) NOT NULL, name VARCHAR(40), createtime DATETIME)*/
        strcpy(sql,"CREATE TABLE IF NOT EXISTS ");
        strcat(sql, tablename);
        strcat(sql, "(");
        strcat(sql, "id INT(4) NOT NULL,name VARCHAR(40),createtime DATETIME");
        strcat(sql, ")");
        res = mysql_query(&my_connection, sql);
        if(!res)
        {
            printf("fan_create_table_at_DBNAME_BASE:\n\tCREATE TABLE %s at DBNAME_BASE is OK!\n",tablename);
        }
            mysql_close(&my_connection);
    }
    else
    {
        printf("fan_create_table_at_DBNAME_BASE:\n\tconn DB error!\n\n");
    }
}

/*һ�㺯��*/
/*(1),��dbname���ݿ��д����±�:tablename;
**(2),��dbname_base���ݿ�:databasename���е�:name = dbnameһ�е�counttables���Լ�1;
**(3),��dbname_base���ݿ�:dbname����:д��ID,name:tablename,createtime,counttables�Լ�1.
***/
void fan_create_table_at_db_by_user(char *tablename,
                                      char *tablefield,
                                      char *dbname,
                                      char *username,
                                      char *password)
{
    MYSQL my_connection;
    MYSQL_RES *res_ptr;
    MYSQL_ROW result_row;
    int res, row, i, have, change;
    my_ulonglong newid;
    have = 0;		/*���ݿ�dbname���Ƿ���tablename�������*/
    change = 0;

    char *sql = tmp_sql;
    char createtime[21];

    strcpy(sql,tablename);
    if(strlen(sql) > DB_TB_NAME_LENTH )
    {
        printf("fan_create_table_at_db_by_user:\n\tError:The tablename:%s is too long!\n\n", tablename);
        return;
    }

    mysql_init(&my_connection);
    if (NULL != mysql_real_connect(&my_connection,
                                   "localhost",
                                   username,
                                   password,
                                   dbname,
                                   0,
                                   NULL,
                                   0))
    {
        printf("fan_create_table_at_db_by_user:\n\tSQL conn OK!\n\n");

        res = mysql_query(&my_connection, "SHOW TABLES");
        if(res)
        {
            printf("fan_create_db_at_localhost_by_user:\n\tselect *from SCHEMATA error!\n\n");
            mysql_close(&my_connection);
        }
        else   /*��ѯ�ɹ�*/
        {
            res_ptr = mysql_store_result(&my_connection);
            if (res_ptr)
            {
                row = mysql_num_rows(res_ptr);
                for (i = 0; i < row; i++)
                {
                    result_row = mysql_fetch_row(res_ptr);
                    if(0 == strcmp(tablename,result_row[0]))
                    {
                        have = 1;       /*��Ҫ�����ı������У��뻻�µ�*/
                        break;
                    }
                }

                if(have)
                {
                    printf("fan_create_table_at_db_by_user:\n\tThe tablename:\"%s\" is old!\nPlease choose other NAME.\n\n",tablename);
                    mysql_close(&my_connection);
                    return;
                }
                else
                {
                    strcpy(sql,"CREATE TABLE IF NOT EXISTS ");
                    strcat(sql,tablename);
                    strcat(sql,"(");
                    strcat(sql,tablefield);
                    strcat(sql,")");
                    res = mysql_query(&my_connection, sql);
                    if(res)
                    {
                        printf("fan_create_table_at_db_by_user:\n\tcreate table:query error!\n\n");
                    }
                    else
                    {
            			printf("fan_create_table_at_db_by_user:\n\tCREATE TABLE %s at %s is OK!\n",tablename, dbname);
                    }
            		mysql_close(&my_connection);
            		change = 1;
                }/*if(have) end*/
            }/*if(res_ptr) end*/
        }/*else res end*/
    }/*if conn*/
    else
    {
        printf("fan_create_table_at_db_by_user:\n\tconn DB error!\n\n");
    }

    if(change)
    {
	    fan_get_local_time_format_to_mysql(createtime);
	    fan_get_counttables_from_db(&newid, dbname, username, password);
	    fan_write_table_of_db_to_DBNAME_BASE(newid, tablename, createtime, dbname);
    }
}

void fan_empty_query_by_root(char *sql)
{
    MYSQL my_connection;
    int res;

    mysql_init(&my_connection);
    if (NULL != mysql_real_connect(&my_connection,
                                   "localhost",
                                   USER_ROOT,
                                   PASSWORD_ROOT,
                                   NULL,
                                   0,
                                   NULL,
                                   0))
    {
        printf("fan_empty_query:\n\t%sSQL conn OK!\n\n",sql);
        res = mysql_query(&my_connection, sql);
        if(res)
        {
            printf("fan_empty_query:\n\t%sSQL DB error!!\n\n",sql);
            mysql_close(&my_connection);
        }
        else   /*��ѯ�ɹ�*/
        {
            mysql_close(&my_connection);
        }
    }
    else
    {
        printf("fan_empty_query:%s\n\tconn DB error!\n\n",sql);
    }
}

/*(1),�������ݿ�:���ݿ���dbname;
**(2),�����ݿ�dbname_base�е�databasename����д��:ID,name,createtime.counttablesд��0;
**(3),�����ݿ�dbname_base�н���:����Ϊdbname,����Ҫ�����������ݿ�����ݿ�����Ϊ����;��д��fields:ID,name,create,counttables;
*/
void fan_create_db_at_localhost_by_user(char * dbname, char *username, char *password)
{
    MYSQL my_connection; /*����һ�����ݿ�����*/
    MYSQL_RES *res_ptr;
    int res;
    MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
    int row; /*��ѯ���ص�����*/
    my_ulonglong newid;
    char createtime[21];
    int i, j, have, change;
    have = 0;
    change = 0;

    char *sql = tmp_sql;

    if(strlen(dbname) > DB_TB_NAME_LENTH )
    {
        printf("fan_create_db_at_localhost_by_user:\n\tError:The dbname is too long!\n\n");
        return;
    }

    mysql_init(&my_connection);
    /*����mysql����,��ѯ��û��������ݿ���*/
    if (NULL != mysql_real_connect(&my_connection,
                                   "localhost",
                                   username,
                                   password,
                                   "information_schema",
                                   0,
                                   NULL,
                                   0))
    {
        printf("fan_create_db_at_localhost_by_user:\n\tSQL conn OK!\n\n");
        res = mysql_query(&my_connection, "select * from schemata"); /*��ѯinformation_schema.schemata��*/
        if(res)
        {
            printf("fan_create_db_at_localhost_by_user:\n\tselect *from SCHEMATA error!\n\n");
            mysql_close(&my_connection);
        }
        else   /*��ѯ�ɹ�*/
        {
            res_ptr = mysql_store_result(&my_connection);
            if (res_ptr)
            {
                row = mysql_num_rows(res_ptr);
                for (i = 1; i < row+1; i++)
                {
                    result_row = mysql_fetch_row(res_ptr);
                    printf("result_row %s: %d have%d:\n",result_row[1], i, have);

                    if( strcmp(dbname, result_row[1]) == 0)
                    {

                        have = 1;       /*��Ҫ���������ݿ������У��뻻�µ�*/
                        break;
                    }
                    printf("have chu zhi:%d\n", have);
                }

                printf("have:%d\n", have);
                if(have)
                {
                    printf("fan_create_db_at_localhost_by_user:\n\tThe dbname:\"%s\" is old!\nPlease choose other NAME.\n\n",dbname);
                    mysql_close(&my_connection);
                    return;
                }
                else
                {
                    strcpy(sql,"create database ");
                    strcat(sql,dbname);
                    res = mysql_query(&my_connection, sql);
                    if(res)
                    {
                        printf("fan_create_db_at_localhost_by_user:\n\tCREATE DATABASE %s Error!\n\n",sql);
                        mysql_close(&my_connection);
                    }
                    else
                    {
                        /* ��dbname�������ݿ�ɹ� */
                        fan_get_local_time_format_to_mysql(createtime);  /*��ȡ�������ݿ��ʱ��*/
                        printf("fan_create_db_at_localhost_by_user:\n\tThe dbname:%s was created!\n\n",dbname);
                    }
                    change = 1;
                }
            }
            mysql_close(&my_connection);
        }
    }
    else
    {
        printf("fan_create_db_at_localhost_by_user:\n\tconn DB error!\n\n");
    }

    if(change)
    {
        printf("wei shen me hui zou dao zhe er?\n");
        fan_get_id_from_DBNAME_BASE(&newid);
        newid++;
        fan_write_db_to_DBNAME_BASE(newid, dbname, createtime, 0);      /*��dbname���ݿ����Ϣд��dbname_base���ݿ��е�databasename��*/
        sql = "id INT(4) NOT NULL,name VARCHAR(40),createtime DATETIME,counttables INT(4) DEFAULT '0'";
        fan_create_table_at_DBNAME_BASE(dbname);    /*��dbname_base���ݿ��д���dbname��*/
    }
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
    mysql_init(&my_connection);
    /*����mysql����*/
    if (NULL != mysql_real_connect(&my_connection, HOST, USER_ROOT, PASSWORD_ROOT,
                                   NULL, 0, NULL, CLIENT_FOUND_ROWS))
    /*���ӳɹ�*/
    {
        printf("query_sql:\n\tSQL conn OK!\n\n");
        /*���ò�ѯ����Ϊgbk����֧������*/
        mysql_query(&my_connection, "set names gbk");
        res = mysql_query(&my_connection, sql);
        if (res)   /*ִ��ʧ��*/
        {
            printf("query_sql:\n\tSQL:%s Error!\n\n",sql);
            /*�ر�����*/
            mysql_close(&my_connection);
        }
        else/*���ھʹ���ִ�гɹ���*/
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
                    printf("%15s ", field->name);
                printf("\n");
                /*��������Y��*/
                for (i = 1; i < row+1; i++)
                {
                    result_row = mysql_fetch_row(res_ptr);
                    for (j = 0; j < column; j++)
                        printf("%15s ", result_row[j]);
                    printf("\n");
                }
            }
	   /*mysql_free_result(&my_connection);*/
            /*��Ҫ���˹ر�����*/
            mysql_close(&my_connection);
        }
    }
    else
    {
        printf("query_sql:\n\tconn DB error!\n\n");
    }
}


void fan_insert_into_table_ADDRESS_of_TEL(char *name, char *phonenum, char *remark,
                                         char *username, char *password)
{
    MYSQL my_conn;
    int res;
    MYSQL_RES *res_ptr;

    my_ulonglong *pid, id;
    char *sql = tmp_sql;
    char tmp[10];
    pid = &id;

    fan_get_rows_from_table_at_db(&id, "address", "tel", username, password);
    id++;

    mysql_init(&my_conn);
    if (NULL != mysql_real_connect( &my_conn, "localhost", username, password,
                                   "tel", 0, NULL, 0) )
    {
        /*INSERT INTO dbname(id,name,createtime) VALUES(newid,tablename,createtime)
        "Id INT(4) NOT NULL, Name VARCHAR(40) NOT NULL, PhoneNUM VARCHAR(21), Remarks VARCHAR(1024)"*/
        strcpy(sql, "INSERT INTO address(Id, Name, PhoneNUM, Remarks) VALUES(");
        sprintf(tmp, "%d", id);
        strcat(sql, tmp);
            strcat(sql,",'");
        strcat(sql, name);
            strcat(sql,"','");
        strcat(sql, phonenum);
            strcat(sql,"','");
        strcat(sql, remark);
        strcat(sql, "')");
        printf("sql:%s\n", sql);

        res = mysql_query(&my_conn, sql);
        if( !res)
        {
            printf("fan_insert_into_table_ADDRESS_of_TEL:\n\tinsert OK!\n");
        }
        else
        {
            printf("fan_insert_into_table_ADDRESS_of_TEL:\n\tinsert ERROR!\n");
        }
        mysql_close(&my_conn);
    }
}

 void fan_insert_into_table_ADDRESS_of_TEL_by_key(char *username, char *password)
 {
     char c;
     char name[30], phone[30],remarks[30];

     while((c = getchar()) != 'E')
     {
         gets(name);
         gets(phone);
         gets(remarks);
         fan_insert_into_table_ADDRESS_of_TEL(name, phone, remarks, username, password);
     }
 }
