/* arc example */ 
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(void)

{
    /* request autodetection */

   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   int stangle = 45, endangle = 135;
   int radius = 100;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();

   if (errorcode != grOk) 
   {  /* an error occurred */



      printf("Graphics error: %s\n", grapherrormsg(errorcode));

      printf("Press any key to halt:");

      getch();

      exit(1);               /* terminate with an error code */

   }



   midx = getmaxx() / 2;

   midy = getmaxy() / 2;

   setcolor(getmaxcolor());



   /* draw arc */

   arc(midx, midy, stangle, endangle, radius);



   /* clean up */

   getch();

   closegraph();

   return 0;

}
