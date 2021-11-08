#ifndef STRPARCE_H_
#define STRPARCE_H_

#include <stdio.h>
#include <string.h>
#include <math.h>

int parceInt(char* str ,  int n);
long parceLong(char* str, int n);
short parceShort(char* str , int n);
float parceFloat(char* str ,  int n);
double parceDouble(char* str , int n);

#endif // STRPARCE_H_