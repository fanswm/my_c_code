#include <stdio.h>
#include <stdlib.h>
int main()
{
    int a,b,c;
    char *p = "0925";

    c = atoi(p);
    a = c/100;
    b = c%100;

    printf("a:%d\nb:%d\n",a,b);
}
