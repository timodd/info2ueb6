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
   } while (dummy != '\n');
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
//use function system from stdlib.h eg. system("CLS") ****NUR WINDOWS??
}

//user input j/n if program restarts
int askYesOrNo(char question[])
{
   int i = 0;
   char sel;
   void printQuestion()
   {
      do
      {
         printf("%c",question[i]);
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
      if (sel == 'j' || sel =='J')
      {
         return 1;
      }
   return 0;
}

// prints i times c.
void printLine(char c,int i)
{
   do
   {
      printf("%c",c);
      i--;
   }while (i);
   printf("\n");
}

void exitProg()
{
   clearScreen();
   printf("exit\n");
}
// Code from info1. Maybe obsolete, but don't throw away, yet.

int Strlen(char *str)
{
    int len = 0;

    while (*str++ != '\0')
        {
            len++;
        }
    return len;
}

//Text einlesen //meine Version
//void getText(char *prompt, TAppointment *txt, int maxlen, int forceinput)
//{
//    char input[maxlen];
//    do
//    {
//        printf("%s",prompt);
//        scanf("%100[^\n]", input);
//        clearBuffer();
//        if (forceinput == 1)
//         txt -> Description = input;
//        else
//         txt -> Location = input;
//    }while (Strlen(input) == 0);
//}
//


int getText(char *prompt,  char **ptxt , int Maxlen, int isForceInput)
{
    char *Input = NULL;
    char Format[100];
    int ScanErg;
    int Len;

    if(Maxlen <= 0) // falls die eingegeben Maxlen kleiner gleich Null ist : false
        return 0;
    if(ptxt == NULL)
        return 0;

    *ptxt = NULL;
    Input = calloc( Maxlen + 1, sizeof(Input));
    if(Input) // if Input != Null => Speicher wurde reserviert
    {
        sprintf(Format, "%%%i[^\n]", Maxlen); // Format[20] = "%Maxlen[^\n]",  %% = %, %i = Maxlen
        do
        {
            STORE_POS;
            printf("%s",prompt); // Ausgabe der Eingabeaufforderung
            ScanErg = scanf(Format, Input); // scanf("%Maxlen[^\n]", Input)
            clearBuffer();
            if(ScanErg == 1) // Falls der Benutzer etwas gültiges eingegeben hat
            {
                Len = (unsigned)strlen(Input); // die Textlänge wird gezählt
                if(Len > 0)
                {
                    *ptxt = calloc (Len + 1, sizeof(ptxt) ); // Speicher für genau der Eingegebene Text reservieren
                    if(*ptxt) // Speicher wurde reserviert
                    {
                        strcpy(*ptxt, Input);
                    }
                    else // der Speicher auf den der Pointer zeigt wurde nicht reserviert
                    {
                        free(Input);
                        return 0;
                    }
                }
                else if(isForceInput) //prüft ob es sich um eine Pflichteingabe handelt
                {
                    break; // man könnte auch free(Input) und return 1 schreiben
                }
                else
                    ScanErg = 0;
            }// Ende von ****Abfrage****
            else if(!isForceInput) // Location can be empty
            {
                break;
            }
            else
            {
               POSITION(10,0);
               printf("Feld kann nicht leer sein");
               RESTORE_POS;
            }
        } while( ScanErg == 0); // solange keine Eingabe

        free(Input); //reservierter Speicher muss immer am Ende freigegeben werden
        return 1;
    }
    return 0;
}

