#ifndef SORT_H
   #define SORT_H SORT_H

int partit(TAppointment *, int, int);
void qsortt(TAppointment *, int, int);
void Quicksort(TAppointment *, int, int(*compare)(TAppointment *, TAppointment *), void(*swp)(TAppointment *, TAppointment *));

#endif
