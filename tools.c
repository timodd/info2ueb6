#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "escapesequenzen.h"
#include "tools.h"

/*
Funktionen:

void clear buffer()
void waitForEnter()
void clearScreen()
int askYesOrNo(char)
void printLine(char, int)
void exitProg()
int getText(char *,  char **, int, int)

*/

//clear the input buffer
void clearBuffer()
{
   char dummy;
   do
   {
      scanf("%c", &dummy);
   }
   while (dummy != '\n');
}


void waitForEnter()
{
   unsigned char w;
   printf("\n\nBitte Eingabetaste druecken... ");
   while(w != '\n')
   {
      w = getchar();
   }
}


void clearScreen()
{
   HOME;
   CLEAR;
}

//output question to terminal. Valid inputs: j,J,n,N
int askYesOrNo(char question[])
{
   int i = 0;
   char sel;
   void printQuestion()
   {
      do
      {
         printf("%c", question[i]);
         i++;
      } while(question[i]);
   }

   printQuestion();

   while (!scanf("%[jJnN]", &sel))
   {
      i = 0;
      UP_LINE;
      CLEAR_LINE;
      printQuestion();
      clearBuffer();
   }
   if (sel == 'j' || sel == 'J')
   {
      return 1;
   }
   return 0;
}

// output i times c to terminal
void printLine(char c, int i)
{
   do
   {
      printf("%c", c);
      i--;
   } while (i);
   printf("\n");
}

void exitProg()
{
   clearScreen();
   printf("exit\n");
}

int Strlen (char *str)
{
   int len = 0;

   while (*str++ != '\0')
   {
      len++;
   }
   return len;
}


int getText (char *prompt,  char **txt , int Maxlen, int isForceInput)
{
   char *Input = NULL;
   char Format[100];
   int isInputValid;
   int Len;

   if(Maxlen <= 0)
      return 0;
   if(txt == NULL)
      return 0;

   *txt = NULL;
   Input = calloc( Maxlen + 1, sizeof(Input));
   if(Input) // only continue if memory has been allocated
   {
      sprintf(Format, "%%%i[^\n]", Maxlen);
      do
      {
         STORE_POS;
         printf("%s", prompt); // output prompt to terminal
         isInputValid = scanf(Format, Input); // user input
         clearBuffer();
         if (isInputValid)
         {
            Len = (unsigned)strlen(Input); // count length of input
            if (Len > 0)
            {
               *txt = calloc (Len + 1, sizeof(txt) ); // alloc mem for size of input
               if(*txt) // if mem alloc
               {
                  strcpy(*txt, Input);
               }
               else // mem to where pointer points to has not been allocated
               {
                  free(Input);
                  return 0;
               }
            }
            else if(isForceInput) // input is a must?
            {
               break; // man könnte auch free(Input) und return 1 schreiben
            }
            else
               isInputValid = 0;
         }// Ende von ****Abfrage****
         else if(!isForceInput) // Location can be empty
         {
            break;
         }
         else
         {
            POSITION(10, 0);
            printf("Feld kann nicht leer sein");
            RESTORE_POS;
         }
      } while (isInputValid == 0);     // as long as no input

      free(Input); //free allocated memory
      return 1;
   }
   return 0;
}
