#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "tools.h"
#include "calendar.h"
#include "datetime.h"
#include "menu.h"
#include "escapesequenzen.h"
#include "database.h"
#include "sort.h"

/*
calendar

Funktionen:

   void createAppointment()
   void editAppointment()
   void deleteAppointment()
   void searchAppointment()
   void sortCalendar()
   void listCalendar()
   void printAppointment (TAppointment *)
   void freeCalendar()
   void freeAppointment (TAppointment *)
   int cmpDat(TAppointment *, TAppointment *);
   int cmpTim(TAppointment *, TAppointment *);
   int cmpDur(TAppointment *, TAppointment *);
   int cmpDes(TAppointment *, TAppointment *);
   int cmpLoc(TAppointment *, TAppointment *);
   int cmpDatTim(TAppointment *, TAppointment *);

   swp(int *,int*)
*/

//int countAppointments = 0;
const int maxlen_description = 100, maxlen_place = 15;

TAppointment *First = NULL;
TAppointment *Last = NULL;

void createAppointment()
{
   TAppointment *App = First;
   App->Description = calloc(101, sizeof(char));
   App->Location = calloc(16, sizeof(char));
   App->Duration = calloc(1, sizeof(TTime));
   App->Time.Hour = -1;
   App->Time.Minute = -1;
   App->Date.Day = -1;
   App->Date.Month = -1;
   App->Date.Year = -1;
   App->next = NULL;
   App->prev = NULL;

   char *title = "Erfassung eines neuen Termins";
   char *points[5] = {  "Datum        : ",
                        "Uhrzeit      : ",
                        "Beschreibung : ",
                        "Ort          : ",
                        "Dauer        : "
                     };
   getSubMenu(title);

   POSITION(4, 0);
   getDate(points[0], &App->Date);

   POSITION(5, 0);
   CLEAR_LINE;
   getTime(points[1], &App->Time);

   POSITION(6, 0);
   CLEAR_LINE;
   getText(points[2], &App -> Description, maxlen_description, 1);
   UP(1);
   CLEAR_LINE;
   printf("%s%s", points[2], App->Description);
   POSITION(7, 0);
   CLEAR_LINE;
   getText(points[3], &App -> Location, maxlen_place, 0);
   UP(1);
   CLEAR_LINE;
   if (App->Location)
   printf("%s%s", points[3], App->Location);
   else
   printf("%s ", points[3]);
   POSITION(8, 0);
   CLEAR_LINE;
   getDuration(points[4], App->Duration);
   App->idx++;
   POSITION(10, 0);
   CLEAR_LINE;
   printf("Termin wurde gespeichert");
   waitForEnter();
}

void editAppointment()
{
   printf("Termin bearbeiten");
   waitForEnter();
}

void deleteAppointment()
{
   printf("Termin löschen");
   waitForEnter();
}

void searchAppointment()
{
   printf("Termin suchen");
   waitForEnter();
}




/* **********************************************
printAppointment gibt einen einzelnen Termin aus.

wird übergeben: TAppointment aus Calendar[]
aufgerufen von: listCalendar
ruft auf: printDate, printTime

************************************************* */
void printAppointment(TAppointment *App)
{
   char *wday[7] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
   int i, index = App -> Date.Weekday;
   int fillspace = maxlen_place;
   if (App->Location)
      fillspace= maxlen_place - strlen(App->Location);
   if ((App - 1) -> Date.Day) //if not first Appointment
   {
      TDate tmp = (App - 1) -> Date;
      if (tmp.Day != App -> Date.Day || tmp.Month != App -> Date.Month || tmp.Year != App -> Date.Year) //if new date
      {
         printf("\n");
         printLine('=', 80);
         printf("%s, ", wday[index]);
         printDate(App -> Date);
      }
   }
   else // if first date
   {
      printf("\n");
      printLine('=', 80);
      printf("%s, ", wday[index]);
      printDate(App -> Date);
   }
   printTime(App -> Time);
   if (App->Duration && (App->Duration->Hour || App->Duration->Minute))
   {
      printf(" - ");
      printTime(addTime(App));
   }
   else
      printf("        ");
   printf(" -> ");
   if (App->Location)
      printf("%s", App -> Location);
   for (i = 0; i < fillspace; i++)
   {
      printf(" ");
   }
   if (strlen(App->Description) < 46)
      printf(" | %s\n", App -> Description);
   else
   {
      char tmp[44] = {' '};
      strncpy(tmp,App->Description, 43);
      printf(" | %s...\n", tmp);
   }
}

void listCalendar()
{
   int i;
   char *title = "Termine auflisten";
   CLEAR;
   getSubMenu(title);
   if (First->idx == 0)
      printf("\n\nnoch keine Termine vorhanden\n");
   for (i = 0; i < First->idx; i++)
   {
      printAppointment(First->next);
   }
   waitForEnter();
}

void freeAppointment(TAppointment *App)
{
   free((App)->Duration);
   free((App)->Location);
   free((App)->Description);
}

void freeCalendar()
{
   int i;
   for (i = 0; i < First->idx; i++)
   {
      freeAppointment(First->next);
   }
}

int cmpDat(TAppointment *A1, TAppointment *A2)
{
   int erg = 0;
   erg = A1->Date.Year - A2->Date.Year;
   if (erg == 0)
      erg = A1->Date.Month - A2->Date.Month;
   if (erg == 0)
      erg = A1->Date.Day - A2->Date.Day;
   return erg;
}

int cmpTim(TAppointment *A1, TAppointment *A2)
{
   int erg = 0;
   erg = A1->Time.Hour - A2->Time.Hour;
   if (erg == 0)
      erg = A1->Time.Minute - A2->Time.Minute;
   return erg;
}

int cmpDatTim(TAppointment *A1, TAppointment *A2)
{
   int erg = 0;
   erg = cmpDat(A1, A2);
   if (erg == 0)
      erg = cmpTim(A1, A2);
   return erg;
}

int cmpDur(TAppointment *A1, TAppointment *A2)
{
   int erg = 0;
   if (A1->Duration)
      erg = 1;
   if (A2->Duration)
      erg = -1;
   if (A1->Duration && A2->Duration)
   {
      erg = A1->Duration->Hour - A2->Duration->Hour;
      if (erg == 0)
         erg = A1->Duration->Minute - A2->Duration->Minute;
   }
      return erg;
}

int cmpDes(TAppointment *A1, TAppointment *A2)
{
   int erg = 0;
   if (A1->Description)
      erg = strcmp(A1->Description,"");
   if (A2->Description)
      erg = -1*(strcmp(A2->Description,""));
   if (A1->Description && A2->Description)
   {
      erg = strcmp(A1->Description, A2->Description);
   }
   return erg;
}

int cmpLoc(TAppointment *A1, TAppointment *A2)
{
   int erg = 0;
   if (A1->Location)
      erg = strcmp(A1->Location,"");
   if (A2->Location)
      erg = -1*(strcmp(A2->Location,""));
   if (A1->Location && A2->Location)
   {
      erg = strcmp(A1->Location, A2->Location);
   }
   return erg;
}

void swp(TAppointment *A1, TAppointment *A2)
{
   TAppointment tmp = *A1;
   *A1 = *A2;
   *A2 = tmp;
}
