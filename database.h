#ifndef DATABASE_H
   #define DATABASE_H DATABASE_H

void saveAppointment (FILE *, TAppointment *);
int loadAppointment (FILE *, char[]);
int saveCalendar ();
void loadCalendar();
void resetAppointment(TAppointment *);

#endif
