#ifndef DATASTRUCTURE_H
   #define DATASTRUCTURE_H DATASTRUCTURE_H
   #define NUMPOINTS 9


typedef enum { NotADay = 0, Mo, Tu, We, Th, Fr, Sa, Su } TDayOfTheWeek;

typedef struct
{
    int Day, Month, Year;
    TDayOfTheWeek Weekday;
} TDate;

typedef struct
{
   int Hour, Minute;
} TTime;

typedef struct sLE
{
//   int idx;
   TDate Date;
   TTime Time;
   char *Description;
   char *Location;
   TTime *Duration;
   struct sLE *next;
   struct sLE *prev;
} TAppointment;

extern int countAppointments;
extern TAppointment *First, *Last;

#endif
