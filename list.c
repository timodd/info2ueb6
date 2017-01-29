#include <stdlib.h>
#include "datastructure.h"
#include "list.h"
#include"calendar.h"

TAppointment *First, *Last;
void insertInDList(TAppointment *New)
{
   TAppointment *tmp = First;
   if (New)
   {
      New -> next = New -> prev = NULL;
      if (First == NULL)
      {
         First = Last = New;
         return;
      }
   }
   if (cmpDatTim(First, New) >= 0)
   {
      New -> prev = Last;
      First = First->prev = New;
      return;
   }
   if (cmpDatTim(Last, New) >= 0)
   {
      New -> next = First;
      Last = Last->next = New;
      return;
   }
   while (tmp->next)
   {
      if (cmpDatTim(tmp->next, New) >= 0)
      {
         New->next = tmp->next;
         New->prev = tmp;
         tmp->next->prev = New;
         tmp->next = New;
         return;
      }
      tmp=tmp->next;
   }
}
void removeFromDList(TAppointment *App)
{

}
