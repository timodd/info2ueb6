#ifndef DATETIME_H
   #define DATETIME_H DATETIME_H

   TDate Date;
   TTime Time;
   void getDate(char [], TDate *);
   void getTime(char [], TTime *);
   void getDuration(char [], TTime *);
   int isLeapYear(int);
   int isDateValid(TDate);
   int isTimeValid(TTime);
   int getDateFromString(char [], TDate *);
   int getTimeFromString(char [], TTime *);
   void printDate(TDate);
   void printTime(TTime);
   TTime addTime(TAppointment *);
#endif // DATETIME_H_INCLUDED
