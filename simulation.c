#include "simulation.h"

void logItration(FILE *result_f ,simItr* itr){
    
    fprintf(result_f, "t= %E\t", T(itr) );
    fprintf(result_f, "r= %E\t", R(itr) );
    fprintf(result_f, "r'= %E\t", R_DOT(itr) );
    fprintf(result_f, "r''= %E\t", R_DOT_DOT(itr) );
    fprintf(result_f, "th= %E\t", THETA(itr) );
    fprintf(result_f, "th'= %E\n", THETA_DOT(itr));

}

void sim_ele(FILE **result_files, sim_init *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    double l_sqr = calc_l_sqr(MASS,CHARGE,BOHR_R);
   
    for (int i = 0 ; i <ORBITS ; i++){

        FILE* res_f = result_files[i];
        double H_mult = (ORBITS-i);
        double curr_l = L*H_mult;
        H_mult*=H_mult;

        double* rMinMax = clac_rmin_rmax(ORBITS,i);

        double simulation_matrix[6];
        
        T(curr_itr) = 0;
        R(curr_itr) = R_MIN;
        R_DOT(curr_itr) = 0;
        R_DOT_DOT(curr_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE, H_mult*l_sqr);
        THETA(curr_itr) = 0;
        THETA_DOT(curr_itr) = calc_theta_dot(curr_l, MASS, R(curr_itr));

        for (int j = 1; j < config->itrs; j++){
                
            T(next_itr) += T_INTERVAL;
            R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
            R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
            THETA(next_itr) = THETA(curr_itr) + (THETA_DOT(curr_itr)* T_INTERVAL);
            R_DOT_DOT(next_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE,H_mult* l_sqr);
            THETA_DOT(next_itr) = calc_theta_dot(curr_l, MASS, R(curr_itr));

            if (THETA(curr_itr) > 2 * PI)
            {
                THETA(curr_itr) = THETA(curr_itr) - 2 * PI;
            }
            if(j % LOG_P == 0){
                logItration(res_f,curr_itr);
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }
        logItration(res_f,curr_itr);

        free(rMinMax);
    }

    free(curr_itr);
    free(next_itr);

}
