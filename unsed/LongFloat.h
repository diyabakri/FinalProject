#ifndef LONGF_H_
#define LONGF_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct lfloat {
    long digits;
    int pft;
}lfloat;

lfloat dtolf(double num,int pft);

double lftod(lfloat num);

lfloat multilf(lfloat arg1 , lfloat arg2);

lfloat devidlf(lfloat arg1 , lfloat arg2);

lfloat sublf(lfloat arg1 , lfloat arg2);

lfloat addlf(lfloat arg1 , lfloat arg2);

#endif // LONGF_H_