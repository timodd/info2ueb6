#include "datastructure.h"
#include "calendar.h"

/*
funktionen:


partit(int *, int, int, int(*)(int*, int*), int(*)(int *, int *))
qsortt(int *,int, int(*)(int*, int*), int(*)(int *, int *))
Quicksort(int *,int, int(*)(int*, int*), int(*)(int *, int *))

*/


int partit(TAppointment *A, int ui, int oi, int(*compare)(TAppointment*, TAppointment*), int(*swp)(TAppointment *, TAppointment *))
{
   int i = ui + 1, j = oi;
   TAppointment *comp = A + ui;
   while(i <= j)
   {
      while(i <= j && (compare(A + i, comp) <= 0))
         i++;
      while(j >= i && (compare(A + j, comp) >= 0))
         j--;
      if(i < j)
      {
         swp(A + i, A + j);
         i++;
         j--;
      }
   }
   i--;
   swp(A + i, comp);
   return i;
}

void qsortt(TAppointment *A, int ui, int oi, int(*compare)(TAppointment*, TAppointment*), int(*swp)(TAppointment *, TAppointment *))
{
   int idx; // Schranke einer Zerlegung
   if (ui >= oi)
      return;
   else
   {
      idx = partit(A, ui, oi, compare, swp);
      qsortt(A, ui, idx - 1, compare, swp); // linken Teil rekursiv sortieren
      qsortt(A, idx + 1, oi, compare, swp); //rechten Teil rekursiv sortieren
   }
}

void Quicksort(TAppointment *A, int num, int(*compare)(TAppointment*, TAppointment*), int(*swp)(TAppointment *, TAppointment *))
{
   qsortt(A, 0, num - 1, compare, swp);
}
