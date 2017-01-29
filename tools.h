#ifndef TOOLS_H
   #define TOOLS_H TOOLS_H
#include "datastructure.h"

void clearScreen();
int askYesOrNo(char[]);
void clearBuffer();
void waitForEnter();
void printLine(char, int);
void exitProg();
int Strlen(char *str);
int getText(char *, char **, int, int);

#endif
