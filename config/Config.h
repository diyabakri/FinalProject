#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/Reads.h"
#include "../util/strParce.h"
#define CONFIG_PATH "config/config.ini" // url of where the values are saved


typedef struct sim_init{

    int itrs; // number of iteration to run
    double init_r; // statring value of R in cm
    double electron_charge; // electron charge value = 4.803e-10 esu
    double electron_mass;  // electron maxx value = 9.109383e-28 g
    double time_intervolt; // time elapsed between each iteration  
    double l; // inital value of l if needes to be changed
    int n; //the number of orbits to simulate.
    int log_p; // the number of ittrations to skip before logging 
    char* results_path; // url for the results to saved in

}sim_init;
/*

    Reads the inital configration values from the config.ini file and stores them in sim_init var 

    @params ()
    @return sim_init* config which contains all the base values to start the simulation 


*/
sim_init* getInitVals();

#endif // CONFIG_H_
