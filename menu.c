#include <stdio.h>
#include "datastructure.h"
#include "escapesequenzen.h"
#include "tools.h"

int getMenu(char *mt, char *mp[], int n) //menuetitle, menuepoints, number of points
{
   int c = 0, p = 0;
   //print menue on empty screen
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

void getSubMenu(char *title/*, char *point[], int i*/)
{
//   int p = 0, valid = 0;
   //print submenue on empty screen
      clearScreen();
      printf("%s\n",title);
      printLine('=', Strlen(title));
//      do
//      {
//         printf("\n%s", point[p]);
//         p++;
//      } while(p < i);
}
