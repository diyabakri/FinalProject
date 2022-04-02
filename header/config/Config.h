#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "../util/types.h"
#include "../util/Reads.h"
#include "../util/strParce.h"
#define CONFIG_PATH "config.ini" // url of where the values are saved


/**
 * @brief Reads the inital configration values from the config.ini file and stores them in Config var
 * 
 * @return Config* with the config values
 */
Config* getInitVals();
/**
 * @brief Create the results diroctarioes 
 * 
 * @param path = "file path format"
 * @param energy_levels  = number of files to create
 * @return int 0 if succesful -1 if faild
 */
int createResultPath(char* path , int energy_levels);

#endif // CONFIG_H_