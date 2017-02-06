#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datastructure.h"
#include "calendar.h"
#include "datetime.h"

char filename[] = "calend.xml";
void saveAppointment(FILE *d, TAppointment *App)
{
   fprintf (d, " <Appointment>\n");
   fprintf (d, "  <Date>%02d.%02d.%04d</Date>\n", App->Date.Day, App->Date.Month, App->Date.Year);
   fprintf (d, "  <Time>%02d:%02d</Time>\n", App->Time.Hour, App->Time.Minute);
   fprintf (d, "  <Description>%s</Description>\n", App->Description);
   if (App->Location)
      fprintf (d, "  <Location>%s</Location>\n", App->Location);
   if (App->Duration && (App->Duration->Hour || App->Duration->Minute))
      fprintf (d, "  <Duration>%02d:%02d</Duration>\n", App->Duration->Hour, App->Duration->Minute);
   fprintf (d, " </Appointment>\n");
}

void resetAppointment(TAppointment *App)
{
   App->Date.Day   = 0;
   App->Date.Month = 0;
   App->Date.Year  = 0;
   App->Date.Weekday = NotADay;
   App->Description = NULL;
   App->Location = NULL;
   App->Duration = NULL;
   App->next = NULL;
   App->prev = NULL;
}

void loadAppointment(FILE *d, char l[])
{
   int len = 0;
   char *pos;
   TAppointment *New = calloc(1, sizeof(TAppointment));
   resetAppointment(New);
   do
   {
      fgets (l, 100, d);
      pos = l;
      while ((*pos == ' ') || (*pos == 9))
      {
         pos++;
      }
      if(strncmp (pos, "<Date>", 6) == 0)
      {
         getDateFromString (pos + 6, &(New->Date));
      }
      else if(strncmp (pos, "<Time>", 6) == 0)
      {
         getTimeFromString (pos + 6, &(New->Time));
      }
      else if (strncmp (pos, "<Duration>", 10) == 0)
      {
         free (New->Duration);
         New->Duration = calloc (1, sizeof(TTime));
         if (New->Duration)
            getTimeFromString (pos + 10, New->Duration);
      }

      else if (strncmp (pos, "<Description>", 13) == 0)
      {
         free (New->Description);
         len = strlen(pos + 13) - 15;
         if (strncmp (pos + 13 + len, "</Description>", 14) == 0)
         {
            New->Description = calloc(len + 1, sizeof(char));
            if (New->Description)
               strncpy(New->Description, pos + 13, len);
         }
      }
      else if (strncmp (pos, "<Location>", 10) == 0)
      {
         free (New->Location);
         len = strlen(pos + 10) - 12;
         if (strncmp (pos + 10 + len, "</Location>", 11) == 0)
         {
            New->Location = calloc(len + 1, sizeof(char));
            if (New->Location)
               strncpy(New->Location, pos + 10, len);
         }
      }
      if(feof (d))
         break;
   }
   while(strncmp (l, " </Appointment>", 15) != 0);
   insertInDList(New);
}
int saveCalendar() /**TODO fuehrt zu speicherzugriffsfehlern **/
{
   FILE *dat = fopen (filename, "wt");
   if (dat == NULL)
   {
      printf ("\nDatei konnte nicht erzeugt oder geöffnet werden\n");
      return 0;
   }
   else
   {
      TAppointment *tmp = First;
      if (tmp)
      {
         while(tmp)
         {
            fprintf (dat, "<Calendar>\n");
            saveAppointment (dat, First);
            tmp = tmp->next;
            fprintf (dat, "</Calendar>\n");
            fclose (dat);
            printf ("\nTermine gespeichert \n");
         }
      }
      else
         printf("\nkeine Termine zum Speichern vorhanden\n");
   }
   return 1;
}
int loadCalendar()
{
   char line[101];
   char *pos;

   FILE *dat = fopen (filename, "rt");
   if (dat)
   {
      do
      {
         fgets (line, 100, dat);
         pos = line;
         while ((*pos == ' ') || (*pos == 9))
         {
            pos++;
         }
         if (feof (dat) )
            break;
         else if (strncmp (pos, "<Appointment>", 13) == 0)
         {
            loadAppointment (dat, line);
         }
      }
      while (strncmp (line, "</Calendar>", 11) != 0);
      printf("\n\nTermine geladen\n");
      return 1;
   }
   else
   {
      printf ("\nDatei konnte nicht geöffnet werden");
      return 0;
   }
   fclose (dat);
}
