#ifndef FILTER_H_
#define FILTER_H_

#include <stdio.h>
#include <stdlib.h>
#include "../utility/linkedList.h"
#include "../utility/types.h"

#define FILTER_PATH "filter.ini"

LinkedList* getFilterList(simType type);

#endif//FILTER_H_