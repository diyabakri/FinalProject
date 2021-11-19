#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../config/Config.h"
#include "../calculations/Calc.h"
#include "../util/macros.h"


typedef struct {
    double t;
    double r;
    double r_dot;
    double r_dot_dot;
    double theta;
    double theta_dot;
}simItr;

void logItration(FILE *result_f ,simItr* itr);

void sim_ele(FILE **result_files, sim_init *config);


#endif //SIMULATION_H_