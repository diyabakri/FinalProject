#ifndef STRPARCE_H_
#define STRPARCE_H_

#include <stdio.h>
#include <string.h>
#include <math.h>

/*

    converts string to int value

    @params char* str the string to convert  int n the length of the string 
    @return int the value of the number inside the string
*/
int parceInt(char* str ,  int n);


/*

    converts string to long value

    @params char* str the string to convert  int n the length of the string 
    @return long the value of the number inside the string
*/
long parceLong(char* str, int n);


/*

    converts string to short value

    @params char* str the string to convert  int n the length of the string 
    @return short the value of the number inside the string
*/
short parceShort(char* str , int n);


/*

    converts string to float value the function can also convert the numbers of the format (1.0E-19)

    @params char* str the string to convert  int n the length of the string 
    @return float the value of the number inside the string
*/
float parceFloat(char* str ,  int n);


/*

    converts string to float value the function can also convert the numbers of the format (1.0E-19)

    @params char* str the string to convert  int n the length of the string 
    @return double the value of the number inside the string
*/
double parceDouble(char* str , int n);

#endif // STRPARCE_H_