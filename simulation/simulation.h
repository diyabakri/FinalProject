#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
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


void sim_ele(FILE **result_files, sim_init *config);

void sim_rel_ele(FILE **result_files , sim_init *config);

void logItration(FILE *result_f ,simItr* itr ,double gamma , double deltaPhi);

#endif //SIMULATION_H_