#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reads.h"
#include "strParce.h"
#define CONFIG_PATH "config.ini"


typedef struct sim_init{

    int itrs;
    double init_r;
    double electron_charge;
    double electron_mass;
    double time_intervolt;
    double l;
    char* results_path; 

}sim_init;

sim_init* getInitVals();

#endif // CONFIG_H_
