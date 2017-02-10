#include <stdio.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"
#include "menu.h"
#include "calendar.h"
#include "escapesequenzen.h"
#include <string.h>
#include "database.h"

int main()
{
   int choice = -1;
   char *menuTitle = "Terminverwaltung V 0.2";
   char *menuPoints[NUMPOINTS] = { "Neuen Termin anlegen",
                                   "Termin bearbeiten",
                                   "Termin löschen",
                                   "Termin suchen",
                                   "Termine auflisten",
                                   "Kalender laden",
                                   "Kalender speichern",
                                   "Programm beenden"
                                 };

   do
   {
      clearScreen();
      choice = printMenu(menuTitle, menuPoints, NUMPOINTS);
      switch (choice)
      {
         case 1: createAppointment();              break;
         case 2: editAppointment();                break;
         case 3: deleteAppointment();              break;
         case 4: searchAppointment();              break;
         case 5: listCalendar();                   break;
         case 6: loadCalendar();                   break;
         case 7: saveCalendar();                   break;
         case 8: freeCalendar()   ;exitProg();     break;
      }
   } while (choice != NUMPOINTS);
   return 0;
}
