#ifndef ITERATOR_H_
#define ITERATOR_H_ 


#include "types.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initItrations(simItr* itr , simType type);

void iterate(simItr* curr_itr , simItr* next_itr , Config* config);

void logItration(FILE* result_f ,simItr* itr);

#endif//ITERATOR_H_