#include <stdio.h>
#include <stdarg.h>
/*
type va_arg( va_list argptr, type );
void va_end( va_list argptr );
void va_start( va_list argptr, last_parm );
*/
   
/*接受不定数量count_char 的参数:(字符)连成字符串*/
void connect_variable_char( size_t count_char, char *to, ... )
{	
	va_list argptr;
	va_start( argptr, count_char );

    for( ; count_char > 0; count_char-- )
	{
		*to = va_arg(argptr, const char);
		to++;
	}
	*to = '\0';
		
	va_end( argptr );
}

void connect_variable_string( unsigned int count_char, char *to, ... )
{	
	char *p;
	va_list argptr;
	va_start( argptr, count_char );
	

	p = to;
	
	sprintf(p, "%s", va_arg(argptr, const char* ) );

    for( ; count_char > 1; count_char-- )
	{
		strcat( p, va_arg(argptr, const char* ) );
	}
		
	va_end( argptr );
}

    int main( void )
	{

    char str[100];

    connect_variable_string( 3, str,"fan", "yue", "hui" );

      printf( "The answer is %s\n", str );

      return( 0 );

    }
