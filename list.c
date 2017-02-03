#include <stdlib.h>
#include "datastructure.h"
#include "list.h"
#include"calendar.h"


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
      if (cmpDatTim(First, New) >= 0)
      {
         New -> next = First;
         First = First->prev = New;
         return;
      }
      if (cmpDatTim(Last, New) <= 0)
      {
         New -> prev = Last;
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
         tmp = tmp->next;
      }
   }
}
TAppointment *removeFromDList(TAppointment *choice)
{
   TAppointment *tmp = First, *del = NULL;
   if (First == NULL)
      return del; //NULLzeiger;
   if (cmpApp(First, choice) == 0)
   {
      del = First;
      First = First->next;
      if (First == NULL)
         Last = NULL;
      else
         First->prev = NULL;
      return del;
   }
   if (cmpApp(Last, choice) == 0)
   {
      del = Last;
      Last = Last->prev;
      Last->next = NULL;
      return del;
   }
   while (tmp->next)
   {
      if (cmpApp(tmp->next, choice) == 0)
      {
         del = tmp->next;
         tmp->next = del->next;
         tmp->next->prev = tmp;
         return del;
      }
      tmp = tmp->next;
   }
   return del;
}

