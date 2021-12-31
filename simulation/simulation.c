#include "simulation.h"


void logItration(FILE *result_f ,simItr* itr ,double gamma , double deltaPhi){
    
    fprintf(result_f, "t= %E\t", T(itr) );

    fprintf(result_f, "r= %E\t", R(itr) );
    fprintf(result_f, "r'= %E\t", R_DOT(itr) );
    fprintf(result_f, "r''= %E\t", R_DOT_DOT(itr) );
    
    fprintf(result_f, "th= %E\t", THETA(itr) );
    fprintf(result_f, "th'= %E\t", THETA_DOT(itr));
    
    if (gamma != -1.0){ 
        fprintf(result_f, "gamma= %E\t", gamma);
    }
    if(deltaPhi != -1.0){
        fprintf(result_f, "deltaPhi= %E\t", deltaPhi);
    }
    fprintf(result_f, "\n");
}

void sim_ele(FILE **result_files, sim_init *config){
    
    double _2_PI =  2 * PI;

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    double l_sqr = calc_l_sqr(MASS,CHARGE,BOHR_R);
    
    for (int i = SUBORBIT-1 ; i <ORBITS ; i++){
        
        if(i == -1){
            continue;
        }
        
        FILE* res_f = result_files[i];
        double H_mult = (ORBITS-i);
        double curr_l = L*H_mult;
        H_mult*=H_mult;

        double* rMinMax = calc_rmin_rmax(ORBITS,i);

        
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

            if (THETA(curr_itr) > _2_PI)
            {
                THETA(curr_itr) = THETA(curr_itr) - _2_PI;
            }
            if(j % LOG_P == 0){
                logItration(res_f,curr_itr,-1.0,-1.0);
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        logItration(res_f,curr_itr,-1.0,-1.0);

        free(rMinMax);

        if(SUBORBIT != 0){
            break;
        }
    }

    free(curr_itr);
    free(next_itr);

}

void sim_rel_ele(FILE **result_files , sim_init *config){

    double _2_PI =  2 * PI;
    
    simItr *curr_itr , *next_itr;
    // keep track of vars for itration i adn a i+1
    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));
    // l_sqr is the value of hbar squared
    double l_sqr = calc_l_sqr(MASS,CHARGE,BOHR_R);
    // reached peak of the eclipse
    bool at_max = true;
    // start calculationg
    for (int i = SUBORBIT-1 ; i <ORBITS ; i++){
        
        if(i == -1){
            continue;
        }
        
        FILE* res_f = result_files[i];
        // The multiplier of H_BAR
        double H_mult = (ORBITS-i);
        // L is the value of H_Bar
        double curr_l = L*H_mult;
        H_mult*=H_mult;
        // Hmult^2 for l_sqr
        double* rMinMax = calc_rmin_rmax(ORBITS,i);
        
        double d = 0;

        double prevTh = 0;
        double prevR = 0;
        
        if (i == 0){
            prevTh =-1;
        }
        
        T(curr_itr) = 0;
        R(curr_itr) = R_MIN;
        R_DOT(curr_itr) = 0;
        double gamma = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));
        R_DOT_DOT(curr_itr) = calc_rel_r_dot_dot(H_mult*l_sqr,MASS,gamma,R(curr_itr),CHARGE,R_DOT(curr_itr));
        THETA(curr_itr) = 0;
        THETA_DOT(curr_itr) = calc_rel_thetat_dot(curr_l,gamma,R(curr_itr),MASS);

        for (int j = 1; j < config->itrs; j++){
                
            T(next_itr) += T_INTERVAL;
            R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
            R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
            THETA(next_itr) = THETA(curr_itr) + (THETA_DOT(curr_itr)* T_INTERVAL);
            if (THETA(next_itr) > _2_PI){
                THETA(next_itr) = THETA(next_itr) - _2_PI;
            }
            R_DOT_DOT(next_itr) = calc_rel_r_dot_dot(H_mult*l_sqr,MASS,gamma,R(curr_itr),CHARGE,R_DOT(curr_itr));
            THETA_DOT(next_itr) = calc_rel_thetat_dot(curr_l,gamma,R(curr_itr),MASS);
            
            if(i > 0){

                if (R_DOT(curr_itr)*R_DOT(next_itr) <= 0){
                    at_max = !(at_max);
                    if(at_max){
                        double  psi = calc_rel_psi(L,CHARGE,R(curr_itr),(double)(ORBITS-i));
                        // prevR += ((2*PI)/psi)-2*PI;
                        
                        if (THETA(curr_itr) > _2_PI)
                        {
                            THETA(curr_itr) = THETA(curr_itr) - _2_PI;
                        }
                        if(prevTh != 0){
                            d = calc_polar_distance(R(curr_itr),prevR,prevTh,THETA(curr_itr));
                        }
                                                    
                        prevR = R(curr_itr);
                        prevTh = THETA(curr_itr);
                    }

                }

            }
            
            gamma = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

            if (THETA(curr_itr) > _2_PI)
            {
                THETA(curr_itr) = THETA(curr_itr) - _2_PI;
            }
            if(j % LOG_P == 0){
                logItration(res_f,curr_itr,gamma,d);
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        free(rMinMax);
        logItration(res_f,curr_itr,gamma,d);

        if(SUBORBIT != 0){
            break;
        }

    }

    free(curr_itr);
    free(next_itr);

}