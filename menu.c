#include <stdio.h>
#include "datastructure.h"
#include "escapesequenzen.h"
#include "tools.h"

int printMenu(char *mt, char *mp[], int n) //menuetitle, menuepoints, number of points
{
   int c = 0, p = 0;
   do
   {
      c = 0;
      p = 0;
      clearScreen();
      printf("%s\n",mt);
      printLine('=', Strlen(mt));
      POSITION(3,0);
      do
      {
         printf("\n%d. %s",p + 1, mp[p]);
         p++;
      } while(p < n);
      printf("\n\nIhre Wahl: ");
      scanf("%d", &c);
      clearBuffer();
   } while(c < 1 || c > n);
   return c;
}

void printSubMenu(char *title)
{
      clearScreen();
      printf("%s\n",title);
      printLine('=', Strlen(title));
}
