

#if !defined(READS_H_)
#define READS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_filepath(char* str);

char* readLine(FILE* fd);

char** readLines(FILE* fd, int* n);


#endif // READS_H_
