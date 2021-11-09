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
    //---------Result mactros------
    #define R_MIN       (rMinMax[0])
    #define R_MAX       (rMinMax[1])
//----------------------------------------

void sim_ele(FILE *res_f, double l, sim_init *config);

int main()
{

    sim_init *config = getInitVals();

    FILE *results_f = fopen(RES_PATH, "w");

    double l_sqr = calc_l_sqr(MASS, CHARGE, BOHR_R); //~1.1117*10^-54

    long begin_time = clock();

    sim_ele(results_f, l_sqr, config);  

    long end_time = clock();

    // close results.txt file

    fclose(results_f);

    printf("program output is saved in ./result.txt \ncalculation time = %f s \n", (double)(end_time - begin_time) / CLOCKS_PER_SEC);

    free(RES_PATH);

    free(config);

    return 0;
}

void sim_ele(FILE *res_f, double l_sqr, sim_init *config)
{
    double n = 2;
    double i = 0;

    double H_mult = (n-i);// n = 2 i = 1 loc = 1 loc => L coeff
    L*=H_mult;
    H_mult*=H_mult;// 1*1 = 1

    double* rMinMax = clac_rmin_rmax(n,i);


    double simulation_matrix[6];
    T = 0;
    R = R_MAX;
    R_DOT = 0;
    R_DOT_DOT = calc_R_dot_dot(MASS, R, CHARGE, H_mult*l_sqr) * T_INTERVAL;
    THETA = 0;
    THETA_DOT = calc_theta_dot(L, MASS, R) * T_INTERVAL;


    fprintf(res_f, "t= %E\t", T);
    fprintf(res_f, "r= %E\t", R);
    fprintf(res_f, "r'= %E\t", R_DOT);
    fprintf(res_f, "r''= %E\t", R_DOT_DOT);
    fprintf(res_f, "th= %E\t", THETA);
    fprintf(res_f, "th'= %E\n", THETA_DOT);

    for (int i = 1; i < config->itrs; i++)
    {
        T += T_INTERVAL;
        R_DOT = R_DOT + R_DOT_DOT;
        R_DOT*=T_INTERVAL;
        R = R+R_DOT;
        THETA = THETA + THETA_DOT;
        R_DOT_DOT = calc_R_dot_dot(MASS, R, CHARGE,H_mult* l_sqr) * T_INTERVAL;
        THETA_DOT = calc_theta_dot(L, MASS, R) * T_INTERVAL ;

        if (THETA > 2 * PI)
        {
            THETA = THETA - 2 * PI;
        }

        fprintf(res_f, "t= %E\t", T);
        fprintf(res_f, "r= %E\t", R);
        fprintf(res_f, "r'= %E\t", R_DOT);
        fprintf(res_f, "r''= %E\t", R_DOT_DOT);
        fprintf(res_f, "th= %E\t", THETA);
        fprintf(res_f, "th'= %E\n", THETA_DOT);

    }
    
    free(rMinMax);
}
