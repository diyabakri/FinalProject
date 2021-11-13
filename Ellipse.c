#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Calc.h"
#include "Config.h"
// -------------MACROS--------------------
    //--------matrix macros--------
    #define T           (simulation_matrix[0])
    #define R           (simulation_matrix[1])
    #define R_DOT       (simulation_matrix[2])
    #define R_DOT_DOT   (simulation_matrix[3])
    #define THETA       (simulation_matrix[4])
    #define THETA_DOT   (simulation_matrix[5])
    //--------config macros--------
    #define MASS        (config->electron_mass) 
    #define CHARGE      (config->electron_charge)
    #define T_INTERVAL  (config->time_intervolt)
    #define L           (config->l)
    #define INIT_R      (config->init_r)
    #define RES_PATH    (config->results_path)
    #define ORBITS      (config->n)
    #define LOG_P       (config->log_p)
    //---------Result mactros------
    #define R_MIN       (rMinMax[0])
    #define R_MAX       (rMinMax[1])
//----------------------------------------

void sim_ele(FILE **result_files, double l, sim_init *config);

int main()
{

    sim_init *config = getInitVals();

    FILE *results_f[ORBITS]; 

    for(int i = 0 ; i < ORBITS ; i++){
        char str[20];
        sprintf(str,"%s%d.txt",RES_PATH,i);
        results_f[i] = fopen(str,"w");
    }

    double l_sqr = calc_l_sqr(MASS, CHARGE, BOHR_R);

    long begin_time = clock();

    sim_ele(results_f, l_sqr, config);  

    long end_time = clock();

    // close results.txt file
    for(int i  = 0 ; i < ORBITS ; i++){
        fclose(results_f[i]);
    }

    printf("program output is saved in ./result.txt \ncalculation time = %f s \n", (double)(end_time - begin_time) / CLOCKS_PER_SEC);

    free(RES_PATH);

    free(config);

    return 0;
}

void sim_ele(FILE **result_files, double l_sqr, sim_init *config)
{
    
    for (int i = 0 ; i <ORBITS ; i++){

        FILE* res_f = result_files[i];
        double H_mult = (ORBITS-i);
        double curr_l = L*H_mult;
        H_mult*=H_mult;

        double* rMinMax = clac_rmin_rmax(ORBITS,i);

        double simulation_matrix[6];
        T = 0;
        R = R_MIN;
        R_DOT = 0;
        R_DOT_DOT = calc_R_dot_dot(MASS, R, CHARGE, H_mult*l_sqr);
        THETA = 0;
        THETA_DOT = calc_theta_dot(curr_l, MASS, R);


        fprintf(res_f, "t= %E\t", T);
        fprintf(res_f, "r= %E\t", R);
        fprintf(res_f, "r'= %E\t", R_DOT);
        fprintf(res_f, "r''= %E\t", R_DOT_DOT);
        fprintf(res_f, "th= %E\t", THETA);
        fprintf(res_f, "th'= %E\n", THETA_DOT);

        for (int j = 1; j < config->itrs; j++)
        {
            T += T_INTERVAL;
            R = R+(R_DOT* T_INTERVAL);
            R_DOT = R_DOT + (R_DOT_DOT * T_INTERVAL);
            THETA = THETA + (THETA_DOT* T_INTERVAL);
            R_DOT_DOT = calc_R_dot_dot(MASS, R, CHARGE,H_mult* l_sqr);
            THETA_DOT = calc_theta_dot(curr_l, MASS, R);

            if (THETA > 2 * PI)
            {
                THETA = THETA - 2 * PI;
            }
            if(j % LOG_P == 0){
            fprintf(res_f, "t= %E\t", T);
            fprintf(res_f, "r= %E\t", R);
            fprintf(res_f, "r'= %E\t", R_DOT);
            fprintf(res_f, "r''= %E\t", R_DOT_DOT);
            fprintf(res_f, "th= %E\t", THETA);
            fprintf(res_f, "th'= %E\n", THETA_DOT);
            }
        }
        free(rMinMax);
    }
}