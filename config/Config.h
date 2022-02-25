#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "../util/Reads.h"
#include "../util/strParce.h"
#define CONFIG_PATH "config/config.ini" // url of where the values are saved


typedef struct Config{

    int itrs; // number of iteration to run
    double init_r; // statring value of R in cm
    double electron_charge; // electron charge value = 4.803e-10 esu
    double electron_mass;  // electron maxx value = 9.109383e-28 g
    double time_intervolt; // time elapsed between each iteration  
    double Hbar; // inital value of l if needes to be changed
    int n; //the eneregy level to simulate.
    int*k_list; //the spific energy_levels to simulate if set to 0 all energy_levels will be simulated format ex: 1,2,3
    int k_size; // number of the energy_levels to simulate
    int*m_list;
    int m_size;
    int reltive; // idicator to the type of equations to use 0 use regular 1 use reletivity 
    int spherical; // idicator to the type of equations to use 0 use polar 1 use spherical
    int log_p; // the number of ittrations to skip before logging 
    char* results_path; // url for the results to saved in

}Config;
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
