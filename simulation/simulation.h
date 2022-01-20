#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../config/Config.h"
#include "../calculations/Calc.h"
#include "../calculations/CalcRel.h"
#include "../util/macros.h"

typedef struct {// struct simItr (simulation itration) to hold the current and next itration values
    double t;// itration time
    double r;// itration distance
    double r_dot;// itration movment speed
    double r_dot_dot;// itration movment acceleration
    double theta;// itration angle
    double theta_dot;// itration angleular speed
}simItr;
/**

    runs the simualtion using the nonrelativistic equations in Calc.h

    @param FILE** array of files to to store the results , Config* the setting of the simualtion
    @return void


*/
void sim_ele(FILE **result_files, Config *config);
/**

    runs the simualtion using the relativistic equations in CalcRel.h

    @param FILE** array of files to to store the results , Config* the setting of the simualtion
    @return void


*/
void sim_rel_ele(FILE **result_files , Config *config);
/**

    writes the current values from a given simItr to a given FILE*

    @param FILE** array of files to to store the results , Config* the setting of the simualtion
    @return void


*/
void logItration(FILE *result_f ,simItr* itr ,double gamma , double deltaPhi);

#endif //SIMULATION_H_