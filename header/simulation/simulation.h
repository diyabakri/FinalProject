#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../config/Config.h"
#include "../calculations/Calc.h"
#include "../calculations/CalcRel.h"
#include "../calculations/SphericalCalc.h"
#include "../util/macros.h"

typedef struct {// struct simItr (simulation itration) to hold the current and next itration values
    double t;// itration time
    double r;// itration distance
    double r_dot;// itration movment speed
    double r_dot_dot;// itration movment acceleration
    double phi;// itration angle
    double phi_dot;// itration angleular speed
    double gamma;//itration rel mass mult
    double delataphi;//itration angle of the perahelion
    double theta;
    double theta_dot;
}simItr;

/**
 * @brief runs the simualtion using the non-relativistic equations in Calc.h
 * 
 * @param result_files array of files to to store the results
 * @param config the settings of the simualtion
 */
void polar_sim_ele(FILE **result_files, Config *config);
/**
 * @brief runs the simualtion using the relativistic equations in CalcRel.h
 * 
 * @param result_files array of files to to store the results
 * @param config the settings of the simualtion
 */
void polar_sim_rel_ele(FILE **result_files , Config *config);
/**
 * @brief runs the simualtion using the non-relativistic equations in SphericalCalc.h
 * 
 * @param result_files array of files to to store the results
 * @param config the settings of the simualtion
 */
void spherical_sim_ele(FILE **result_files , Config *config);
/**
 * @brief writes the current values from a given simItr to a given FILE*
 * 
 * @param result_f 
 * @param itr 
 */
void logItration(FILE *result_f ,simItr* itr);

#endif //SIMULATION_H_