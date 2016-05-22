#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_
 
#include "config.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "DirectionExt.h"
#include "StepAndDirection.h"
#include "configuration.h"
#include <list>

using namespace std;
#define BUFF_SIZE 1024

void gotoxy(int x, int y);
void hideCursor();
void clear_screen();

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
void _itoa_s(unsigned int, char s[], unsigned int, int);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif

#endif