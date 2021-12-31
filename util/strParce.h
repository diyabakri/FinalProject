#ifndef STRPARCE_H_
#define STRPARCE_H_

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*

    converts string to int value

    @params char* str the string to convert  int n the length of the string 
    @return int the value of the number inside the string
*/
int parceInt(char* str);


/*

    converts string to long value

    @params char* str the string to convert  int n the length of the string 
    @return long the value of the number inside the string
*/
long parceLong(char* str);


/*

    converts string to short value

    @params char* str the string to convert  int n the length of the string 
    @return short the value of the number inside the string
*/
short parceShort(char* str);


/*

    converts string to float value the function can also convert the numbers of the format (1.0E-19)

    @params char* str the string to convert  int n the length of the string 
    @return float the value of the number inside the string
*/
float parceFloat(char* str);


/*

    converts string to float value the function can also convert the numbers of the format (1.0E-19)

    @params char* str the string to convert  int n the length of the string 
    @return double the value of the number inside the string
*/
double parceDouble(char* str);

int* parceIntArray(char* str);

double* parceDoubleArray(char* str);


#endif // STRPARCE_H_