#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define A_B_NAME_LENTH 30
#define A_B_PHONE_LENTH 15
#define A_B_ADDRESS_LENTH 40
#define A_B_ID_CARD_LENTH 20
#define A_B_REMARKS_LENTH 200
#define A_B_ITEMS_COUNT	8

#define FILE_NAME_LEN 225
#define A_B_RESULT_COUNT 5

struct AddressBook
{
    char name[A_B_NAME_LENTH];
    char sex[4];
    char phone[A_B_PHONE_LENTH];
    char other_tel[A_B_PHONE_LENTH];
    char company[A_B_ADDRESS_LENTH];
    char house_address[A_B_ADDRESS_LENTH];
    char identification_card[A_B_ID_CARD_LENTH];
    char remarks[A_B_REMARKS_LENTH];
};

typedef struct AddressBook addressbook;
typedef addressbook *ptr_ad;
typedef unsigned char my_BOOL;

/* get "filename" file length by "mode".
	mode:"r"  or "rb"
	return "0" or "+num": OK!
	"-num": failed! */
double get_file_lenth(const char *filename, \
                        const char *mode)
{
	double flen;
	FILE *fp;

	if( strcmp(mode, "r") == 0 || strcmp(mode, "rb") == 0)
	{
		;
	}
	else
	{
		printf("fanswm_debug: get_file_lenth: error mode!\n");
		return -1;
	}

	if((fp = fopen(filename, mode) ) == NULL)
	{
		printf("fanswm_debug: get_file_lenth: Error: open file failed\n");
		return -1;
	}
	fseek(fp, 0L, SEEK_END);		/* set pos:"file" END */
	flen = ftell(fp);				/* get file bytes */

	fclose(fp);
	return flen;
}

/* get file neirong, save to: str_of_file */
void get_txtfile_to_str(const char *filename, char *str_of_file)
{
	int flen;
	FILE *fp;

	fp = fopen("outbu.txt", "r");
	fseek(fp, 0L, SEEK_END);	/* set pos:"file" END */
	flen = ftell(fp);			/* get file bytes */

	if(str_of_file == NULL)
	{
		fclose(fp);
		printf("fanswm_debug: get_file_to_str: Error: str_of_file == NULL\n");
		return;
	}
	else
	{
		fseek(fp, 0L, SEEK_SET);/* set pos:"file" START */
		fread(str_of_file, flen, 1, fp);	/* read file all by ones */
		str_of_file[flen] = '\0';		/* string END flag */
		fclose(fp);
	}
}

/* 	create "addressBook" by name:filename. if not have:create.
	if OK, return 1;else return 0 */
size_t create_addressbook(const char *filename)
{
    FILE *book;

    if((book = fopen(filename,"r")) == NULL)
    {
        printf("Cannot open addressbook file. now try created!\n");

        if((book = fopen(filename,"w")) == NULL)
        {
            printf("Create addressbook failed! Please contact Administrator.\n");
            return 0;
        }
        else
        {
            printf("Create addressbook OK!\n");
            fclose(book);
            return 1;
        }
    }
    else
    {
        printf("open addressbook OK!\n");
        fclose(book);
        return 1;
    }
}

/* if file length is 0, write table_header */
void init_addressbook(const char *addressbookname)
{
    FILE *fp;
    int len;

    len = get_file_lenth(addressbookname,"r");
    if((fp = fopen(addressbookname,"a")) == NULL)
    {
        printf("open addressbook failed! Please contact Administrator.\n");
    }
    else
    {
        if(len == 0)
        {
        	fprintf(fp,"%s", "Name\tSex\tPhone\tOtherTel\tCompany\tHouseAddress\tID_Card\tRemarks\n");
		}
 		fclose(fp);
    }
}

/* get string And write it to Struct:A_B. */
void write_str_to_struct(ptr_ad pad)
{
    char str[A_B_REMARKS_LENTH] = {'\0'};

    printf("Please input Name:\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_NAME_LENTH - 1)
        {
            strcpy(pad->name, str);
        }
        else
        {
            strncpy(pad->name, str, A_B_NAME_LENTH - 1);    /* if str large A_B_NAME_LENTH, write A_B_NAME_LENTH char */
        }
    }
    else
    {
        strcpy(pad->name, "-");
    }

    printf("Please input Sex:\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < 3)
        {
            strcpy(pad->sex, str);
        }
        else
        {
            strncpy(pad->sex, str, 3);
        }
    }
    else
    {
        strcpy(pad->sex, "-");
    }

    printf("Please input Phone\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_PHONE_LENTH - 1)
        {
            strcpy(pad->phone, str);
        }
        else
        {
            strncpy(pad->phone, str, A_B_PHONE_LENTH - 1);
        }
    }
    else
    {
        strcpy(pad->phone, "-");
    }

    printf("Please input Other_Tel\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_PHONE_LENTH - 1)
        {
            strcpy(pad->other_tel, str);
        }
        else
        {
            strncpy(pad->other_tel, str, A_B_PHONE_LENTH - 1);
        }
    }
    else
    {
        strcpy(pad->other_tel, "-");
    }

    printf("Please input Company\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_ADDRESS_LENTH - 1)
        {
            strcpy(pad->company, str);
        }
        else
        {
            strncpy(pad->company, str, A_B_ADDRESS_LENTH - 1);
        }
    }
    else
    {
        strcpy(pad->company, "-");
    }

    printf("Please input house_address\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_ADDRESS_LENTH - 1)
        {
            strcpy(pad->house_address, str);
        }
        else
        {
            strncpy(pad->house_address, str, A_B_ADDRESS_LENTH - 1);
        }
    }
    else
    {
        strcpy(pad->house_address, "-");
    }

    printf("Please input identification_card:\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_ID_CARD_LENTH - 1)
        {
            strcpy(pad->identification_card, str);
        }
        else
        {
            strncpy(pad->identification_card, str, A_B_ID_CARD_LENTH - 1);
        }
    }
    else
    {
        strcpy(pad->identification_card, "-");
    }

    printf("Please input remarks\n");
    gets(str);
    if(isprint(*str))
    {
        if(strlen(str) < A_B_REMARKS_LENTH - 1)
        {
            strcpy(pad->remarks, str);
        }
        else
        {
            strncpy(pad->remarks, str, A_B_REMARKS_LENTH - 1);
        }
    }
    else
    {
        strcpy(pad->remarks, "-");        /* write '-' */
    }
}

/* search for "item" from addressbook head.
    OK: item count;
    error: -1 */
my_BOOL search_str_of_item_from_addressbook(size_t *row_result, \
                                                size_t *col_result, \
                                                const char *search, \
                                                const char *item, \
                                                const char *addressbookname)
{
    FILE *fp;
    char ch, *p;
    size_t step, row;
    my_BOOL have;
    int i;
    char str[A_B_REMARKS_LENTH] = {'\0'};

    step = 0;
    have = 0;

    p = str;
    if((fp = fopen(addressbookname,"r")) == NULL)
    {
        printf("open addressbook failed! Please contact Administrator.\n");
        *row_result = 0;
        *col_result = 0;
        return 0;
    }

    while( (ch = fgetc(fp)) != '\n')   /* where is the search *item at? */
    {
        while(ch != '\t' && ch != '\n')
        {
            *p = ch;
            p++;
            ch = fgetc(fp);
        }
        *p = '\0';

        if( !strcmp(str, item) )
        {
            have = 1;   /* have *item */
            break;
        }
        else
        {
            step++;     /* how much item */
            p = str;
        }

        if(ch == '\n')      /* avoid '\n' then 'fgetc' */
        {
            break;
        }
    }

    /* if 'item' was not finded */
    if(!have )
    {
        *row_result = 0;
        *col_result = 0;
        return 0;
    }

    if(ch != '\n')
    {
        while( (ch = fgetc(fp)) != '\n' && !feof(fp) )       /* skip this row(0) other char */
            ;
    }

    *col_result = step;

    row = 1;
    have = 0;                   /* search from row: 1 */
    while( !feof(fp) )
    {
        while( (ch = fgetc(fp) ) != '\n' && !feof(fp) )          /*search every row*/
        {
            i = 0;
            while(i < step  && ch != '\n')
            {
                while(ch != '\t' && !feof(fp))    /* skip step-1 of '\t' AT every row */
                {
                    ch = fgetc(fp);
                }
                i++;
                /*counrent char is '\t' */
                ch = fgetc(fp);
            }

            p = str;            /* this pointer init */
            while( ch != '\t' && ch != '\n' && !feof(fp) )
            {
                *p = ch;
                p++;
                ch = fgetc(fp);
            }
            *p = '\0';

            /* skip this row other char */
            while(ch != '\n' && !feof(fp))
            {
                ch = fgetc(fp);
            }

            if(!strcmp(search, str) )
            {
                have = 1;
                break;
            }
            else
            {
                row++;
            }
        }

        if(have)     /* finded */
        {
            break;
        }
    }

    if(!have)
    {
        *row_result = 0;
        *col_result = 0;
        return 0;
    }

    *row_result = row;
    fclose(fp);

    return have;
}



/*  write AddressBook by ptr_ad->struct.item.
    OK:1; ERROR:0 */
my_BOOL write_addressbook_by_struct(ptr_ad from, const char *addressbookname)
{
    FILE *to;
    char name[A_B_NAME_LENTH];
    my_BOOL have = 1;

    if( !strcmp(from->name,"-") )	/* if the Name is null: return */
    	return 0;

    if((to = fopen(addressbookname,"a")) == NULL)
    {
        printf("open addressbook failed! Please contact Administrator.\n");
        return 0;
    }
    else
    {
        fprintf( to, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", \
            from->name, from->sex, \
			from->phone, from->other_tel, \
			from->company, from->house_address, \
			from->identification_card, from->remarks );
        fclose(to);
        return 1;
    }
}

/* return "item" col; OK: col; ERROR: -1 */
int get_item_of_col_from_addressbook_header(const char *item)
{
    int col, i;
    char *str[A_B_ITEMS_COUNT] = {"Name", "Sex", "Phone", "Other_Tel", "Company", "HouseAddress", "ID_Card", "Remarks"};

    col = -1;

    for(i = 0; i < A_B_ITEMS_COUNT; i++)
    {
        if(!strcmp(item, str[i]))
        {
            col = i;
        }
    }

    return col;
}

my_BOOL get_str_from_addressbook_by_row_and_col(char *to, const size_t row, \
                                        const size_t col, const char *addressbookname)
{
    FILE *fp;
    my_BOOL have;
    int i;
    char ch, *p, str[A_B_REMARKS_LENTH] = {'\0'};

    if(col >= A_B_ITEMS_COUNT)
    {
        *to = '\0';
        return 0;
    }

    have = 0;

    p = str;
    if((fp = fopen(addressbookname,"r")) == NULL)
    {
        printf("open addressbook failed! Please contact Administrator.\n");
        *to = '\0';
        return 0;
    }

   fseek(fp, 0L, SEEK_SET);

    i = 0; /* row */
    while(i < row  && (ch = fgetc(fp)) != '\n' && !feof(fp))
    {
        /*printf("%c", ch);*/
        if(ch == '\n')
        {
            i++;
        }
    }

    if(i == (row -1))
    {
    	have = 1;
    }
    else
    {
    	have = 0;
    	return 0;
    }

    i = 0;   /* col */
    while(i < col  && (ch = fgetc(fp)) != '\n' && !feof(fp))
    {
        /*printf("%c", ch);*/
        if(ch == '\t')
        {
            i++;
        }
    }

    ch = fgetc(fp);
    while(ch != '\t' && ch != '\n' && !feof(fp))
    {
    	*p = ch;
    	p++;
        ch = fgetc(fp);
    }
    *p = '\0';

    strcpy(to, str);

    fclose(fp);

    return have;
}

/* 'filename' not include 'panfu C:' */
/* badname: 1; truename: 0 */
my_BOOL have_windows_bad_file_name_char(const char *filename)
{
	const char *p;
	char ch;
    my_BOOL maohao, fanxiegang, dian, have_error;        /* include ':' || '\\' || '.' */
    maohao = 0;
    fanxiegang = 0;
    dian = 0;
    have_error = 0;

	p = filename;
	while(*p)
	{
		ch = *p;
		if(ch == '*' || ch == '?')
		{
			have_error = 1;
		}

        if(ch == ':')
        {
            maohao++;
        }
        if(ch == '\\')
        {
            fanxiegang++;
        }
        if(ch == '.')
        {
            dian++;
        }
		p++;
	}

    if((maohao == 1 && fanxiegang && dian == 1) && !have_error)
    {
        have_error = 0;
    }
    else
    {
    	have_error = 1;
    }

	return have_error;
}

void get_item_of_file_name_windows_path(char *to_path, \
									char *filename, char *extension, \
                                    const char *window_path_name)
{
	char *pos, *p, *pos2;
    char buf[FILE_NAME_LEN];
    my_BOOL ok, bad_char;

    bad_char = have_windows_bad_file_name_char(window_path_name);

    if(bad_char)
    {
        *to_path = '\0';
        *filename = '\0';
        *extension = '\0';
        printf("Error: The file name include bad_char!\n");   /*  windows_path_name include bad char */
        return;
    }

    p = buf;
    strcpy(p, window_path_name);
    pos = strrchr(p, '\\');
    pos++;                          /* skip '\\' */
    *pos = '\0';
    strcpy(to_path, p);         /* to_path compleate */

    p = buf;
    pos = strrchr(window_path_name, '\\');
    pos++;                          /* skip '\\' */
    strcpy(p, pos);
    pos = strrchr(p, '.');
    *pos = '\0';                    /* set '.' to '\0' */
    strcpy(filename, buf);          /* filename compleate */

    pos = strrchr(window_path_name, '.');
    pos++;
    strcpy(extension, pos);       /* extension compleate */
}


/* get addressbookname file rows */
double get_rows_from_addressbook(const char *addressbookname)
{
    FILE *fp;
    double get_rows;
    char ch;

    get_rows = 0;

    if( (fp = fopen(addressbookname,"r")) == NULL)
    {
        printf("open addressbook failed! Please contact Administrator.\n");
        return 0;
    }

    ch = fgetc(fp);
    while(!feof(fp))
    {
        if(ch == '\n')
        {
            get_rows++;
        }
        ch = fgetc(fp);
    }

    fclose(fp);

    return get_rows;
}


my_BOOL get_recorder_from_addressbook_by_row(char *to, size_t row,
                                            const char *addressbookname)
{
    FILE *fp;
    my_BOOL have;
    double rows;
    size_t i;
    char ch;
    char *tmp = to;

    if((fp = fopen(addressbookname,"r")) == NULL)
    {
        printf("get_recorder_from_addressbook_by_row:\n\
            \tError:\n\topen addressbook: %s failed! Please contact Administrator.\n",\
            addressbookname);
        *to = '\0';
        return 0;
    }

    rows = get_rows_from_addressbook(addressbookname);

    if(rows == 0.0 || rows == 1.0 || (row + 1.0) > rows)
    {
        printf("get_recorder_from_addressbook_by_row:\n \
                    \tError:\n\t The A_B: %s is empty or row too large!\n", addressbookname);
        *to = '\0';
        return 0;
    }

    have = 0;
    i = 0;
    ch = fgetc(fp);
    while(i < row && !feof(fp))
    {
        if(ch == '\n')
        {
            i++;
        }
        ch = fgetc(fp);
    }

    while(ch != '\n')
    {
        *to = ch;
        ch = fgetc(fp);
        to++;
    }
    *to = '\0';

    fclose(fp);
    return 1;

}


/* find first 5th result, save to row[A_B_RESULT_COUNT], col[A_B_RESULT_COUNT] */
my_BOOL get_str_row_col_from_addressbook(double row[A_B_RESULT_COUNT],\
                                    size_t col[A_B_RESULT_COUNT], \
                                    const char *search, \
                                    const char *addressbookname)
{
    FILE *fp;
    my_BOOL have;
    double r, *pr;
    size_t c, *pc;
    int i;
    char *p, ch, buf[A_B_REMARKS_LENTH] = {'\0'};

    if((fp = fopen(addressbookname,"r")) == NULL)
    {
        printf("get_str_row_col_from_addressbook:\n\
            \tError:\n\topen addressbook: %s failed! Please contact Administrator.\n",\
            addressbookname);
        *row = 0;
        *col = 0;
        return -1;
    }

    for(i = 0; i < A_B_RESULT_COUNT; i++)
    {
        row[i] = 0;
        col[i] = 0;
    }       /* init */

    pr = row;       /* result */
    pc = col;

    p = buf;
    i = 0;          /* count */
    have = 0;
    r = 0;
    c = 0;
    while(!feof(fp))
    {
        ch = fgetc(fp);
        while(ch != '\t' && ch != '\n' && !feof(fp))
        {
            *p = ch;
            p++;
            ch = fgetc(fp);
        }
        *p = '\0';
        p = buf;

        if(ch == '\t')
        {
            c++;
        }
        if(ch == '\n')
        {
            c = 0;
            r++;
        }

        if(!strcmp(buf, search) )
        {
            have = 1;
            *pr = r;
            pr++;
            *pc = c - 1;
            pc++;
            i++;

            if(i == A_B_RESULT_COUNT)      /* only first 5th result */
            {
                return 1;
            }
        }
    }

    fclose(fp);
    return have;
}

addressbook ad;
ptr_ad ppad;

int main( )
{
    size_t row, col, *prow, *pcol;
    int f, i;
    double r_s[A_B_RESULT_COUNT];
    size_t c_s[A_B_RESULT_COUNT];
    my_BOOL have;
    char buf[1024], str[A_B_REMARKS_LENTH] = {'\0'};

    char mypath[20], myfilename[20], mykuo[20];

	ppad = &ad;
	prow = &row;
    pcol = &col;
/**
    create_addressbook("D:\\addressbook.txt");
    init_addressbook("D:\\addressbook.txt");
    write_str_to_struct(ppad);
    write_addressbook_by_struct(ppad, "D:\\addressbook.txt");

    have = search_str_of_item_from_addressbook(p, pc, "fanswm", "Name", "D:\\addressbook.txt");
    printf("fanswm:have:%d\trow=%d\tcol=%d\n", have, row, col);

    get_item_of_file_name_windows_path(mypath, myfilename, mykuo, "D:\\fan\\f.txt");
    printf("mypath = %s\nmyfilename = %s\nmykuo = %s\n", mypath, myfilename, mykuo);
    **/
    have = search_str_of_item_from_addressbook(prow, pcol, "fandd", "Name", "D:\\addressbook.txt");
    printf("fandd:name: %d\t%d\n", *prow, *pcol);
    if(have)
    {
        get_str_from_addressbook_by_row_and_col(str, 2, 2, "D:\\addressbook.txt");
        printf("search_str:row:2, col:2: \n %s\n",  str);
    }


/**
    have = get_str_row_col_from_addressbook(r_s, c_s, "zd", "D:\\addressbook.txt");
    printf("get_str_row_col_from_addressbook:\nhave = %d\n", have);
    if(have)
    {
        for(i = 0; i < A_B_RESULT_COUNT; i++)
        {
            printf("r: %d\tc: %d\n", r_s[i], c_s[i]);
        }
    }
    */

    r_s[0] = get_rows_from_addressbook("D:\\addressbook.txt");
    printf("fanswm get_rows: %-8.0f\n", r_s[0]);

    have = get_recorder_from_addressbook_by_row(buf, 3, "D:\\addressbook.txt");
    printf("get_recorder:\thave: %d\n", have);
    if(have)
    {
        printf("get recorder: \n%s\n", buf);
    }

    have = get_str_row_col_from_addressbook(r_s, c_s, "fandd", "D:\\addressbook.txt");

    for(i = 0; i < A_B_RESULT_COUNT; i ++)
    {
        printf("r:%f\tc:%d\n", r_s[i], c_s[i]);
    }

}

/**
struct AddressBook;
typedef struct AddressBook addressbook;
typedef addressbook *ptr_ad;

double get_file_lenth(const char *filename, const char *mode);
void get_txtfile_to_str(const char *filename, char *str_of_file);

size_t create_addressbook(const char *filename);
void init_addressbook(const char *addressbookname);
int write_str_to_struct(ptr_ad pad);
my_BOOL write_addressbook_by_struct(ptr_ad from, const char *addressbookname);

my_BOOL search_str_of_item_from_addressbook(size_t *row_result, \
                                                size_t *col_result, \
                                                const char *search, \
                                                const char *item, \
                                                const char *addressbookname);
int get_item_of_col_from_addressbook_header(const char *item);
my_BOOL get_str_from_addressbook_by_row_and_col(char *to, const size_t row, \
                    size_t col, const char *addressbookname);

my_BOOL have_windows_bad_file_name_char(const char *filename);
void get_item_of_file_name_windows_path(char *to_path, \
                                    char *filename, char *extension, \
                                    const char *window_path_name);

**/