#include "simulation.h"

#include <float.h>


void logItration(FILE *result_f ,simItr* itr){
    
    fprintf(result_f, "t= %E\t", T(itr) );

    fprintf(result_f, "r= %E\t", R(itr) );
    fprintf(result_f, "r'= %E\t", R_DOT(itr) );
    fprintf(result_f, "r''= %E\t", R_DOT_DOT(itr) );
    
    fprintf(result_f, "th= %E\t", THETA(itr) );
    fprintf(result_f, "th'= %E\t", THETA_DOT(itr));
    
    if (GAMMA(itr) != -1.0){ 
        fprintf(result_f, "gamma= %E\t", GAMMA(itr));
    }
    if(DELTAPHI(itr) != -1.0){
        fprintf(result_f, "deltaPhi= %E\t", DELTAPHI(itr));
    }

    fprintf(result_f, "\n");
}

void sim_ele(FILE **result_files, Config *config){
    
    double _2_PI =  2 * PI;

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    double Hbar_sqr = calc_Hbar_sqr(MASS,CHARGE,BOHR_R);
    
    for (int i = 0 ; i <N ; i++){
        if(K_LIST[0]!= 0 || K_SIZE !=1){
        
            bool isSimulated = false;
            
            for(int j = 0 ; j < K_SIZE ; j++){
                if(K_LIST[j] == i+1 ){
                    isSimulated = true;
                    break;
                }
            }
            if(isSimulated==false){
                continue;
            }
        }
        
        FILE* res_f = result_files[i];
        double K = (N-i);
        double curr_l = HBAR*K;
        K*=K;

        double* rMinMax = calc_rmin_rmax(N,i);

        
        T(curr_itr) = 0;
        R(curr_itr) = R_MIN;
        R_DOT(curr_itr) = 0;
        R_DOT_DOT(curr_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE, K*Hbar_sqr);
        THETA(curr_itr) = 0;
        THETA_DOT(curr_itr) = calc_theta_dot(curr_l, MASS, R(curr_itr));
        GAMMA(curr_itr) = -1;
        DELTAPHI(curr_itr)= -1;

        for (int j = 1; j < config->itrs; j++){
                
            T(next_itr) += T_INTERVAL;
            R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
            R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
            THETA(next_itr) = THETA(curr_itr) + (THETA_DOT(curr_itr)* T_INTERVAL);
            R_DOT_DOT(next_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE,K* Hbar_sqr);
            THETA_DOT(next_itr) = calc_theta_dot(curr_l, MASS, R(curr_itr));

            if (THETA(curr_itr) > _2_PI)
            {
                THETA(curr_itr) = THETA(curr_itr) - _2_PI;
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

void sim_rel_ele(FILE **result_files , Config *config){

    double _2_PI =  2 * PI;
    
    simItr *curr_itr , *next_itr;
    // keep track of vars for itration i adn a i+1
    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));
    // Hbar_sqr is the value of hbar squared
    double Hbar_sqr = calc_Hbar_sqr(MASS,CHARGE,BOHR_R);
    printf("calc HBAR_sqr = %.*E",sqrt(Hbar_sqr),DECIMAL_DIG);
    Hbar_sqr = HBAR*HBAR;
    printf("\tHbar_sqr^2 = %.*E\n",sqrt(Hbar_sqr),DECIMAL_DIG);

    // reached peak of the eclipse
    bool at_max = true;
    // start calculationg
    for (int i = 0 ; i <N ; i++){
        
        if(K_LIST[0]!= 0 || K_SIZE !=1){
        
            bool isSimulated = false;
            
            for(int j = 0 ; j < K_SIZE ; j++){
                if(K_LIST[j] == i+1 ){
                    isSimulated = true;
                    break;
                }
            }
            if(isSimulated==false){
                continue;
            }
        }
        
        FILE* res_f = result_files[i];
        // The multiplier of H_BAR
        double K = (N-i);
        // L is the value of H_Bar
        double curr_l = HBAR*K;
        double alpha = calc_alpha(CHARGE,HBAR);
        double w = calc_rel_w(N,K,MASS,alpha);

        K*=K;
        // K^2 for Hbar_sqr
        double* rMinMax = calc_rmin_rmax(N,i);


        double a = calc_rel_A(MASS,w);

        double b = calc_rel_B(MASS,CHARGE,w);

        double c = calc_rel_C(K*Hbar_sqr,CHARGE);

        double rel_rmin = calc_rel_rmin(a,b,c);

        // printf("relativistic rmin = %E ,non relativistic rmin = %E\n\n",rel_rmin,R_MIN);

        // return;
        

        double prevTh = 0;
        double prevMaxTh= PI;
        double prevR = 0;
        
        // if (i == 0){
        //     prevTh =-1;
        // }
        
        T(curr_itr) = 0;
        R(curr_itr) = rel_rmin;
        R_DOT(curr_itr) = 0;
        GAMMA(curr_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));
        R_DOT_DOT(curr_itr) = calc_rel_r_dot_dot(K*Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));
        THETA(curr_itr) = 0;
        THETA_DOT(curr_itr) = calc_rel_theta_dot(curr_l,GAMMA(curr_itr),R(curr_itr),MASS);
        DELTAPHI(curr_itr) = 0;

        for (int j = 1; j < config->itrs; j++){
                
            T(next_itr) += T_INTERVAL;
            R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
            R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
            THETA(next_itr) = THETA(curr_itr) + (THETA_DOT(curr_itr)* T_INTERVAL);
            if (THETA(next_itr) > _2_PI){
                THETA(next_itr) = THETA(next_itr) - _2_PI;
            }
            R_DOT_DOT(next_itr) = calc_rel_r_dot_dot(K*Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));
            THETA_DOT(next_itr) = calc_rel_theta_dot(curr_l,GAMMA(curr_itr),R(curr_itr),MASS);
            
            if(i >= 0){

                if (R_DOT(curr_itr)*R_DOT(next_itr) <= 0){
                    at_max = !(at_max);
                    if(at_max){
                        
                        double  chi = calc_rel_chi(HBAR,CHARGE,R(curr_itr),(double)(N-i));
                        // double test += ((2*PI)/chi)-2*PI;
                        
                        if (THETA(curr_itr) > _2_PI)
                        {
                            THETA(curr_itr) = THETA(curr_itr) - _2_PI;
                        }
                        if(prevTh != 0){
                            DELTAPHI(curr_itr) += THETA(curr_itr) - prevMaxTh;
                            // printf("curr THeta = %.*E , prev Theta  = %.*E \t",THETA(curr_itr),DECIMAL_DIG,prevTh,DECIMAL_DIG);
                            // printf(" currMaxth - prevMAxth  %E, acurrate %E \n",DELTAPHI(curr_itr), (((2*PI)/chi)-2*PI));
                        }
                                                    
                        prevR = R(curr_itr);
                        prevMaxTh = THETA(curr_itr);

                    }

                }

            }
            prevTh = THETA(curr_itr);
            
            GAMMA(next_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

            if (THETA(curr_itr) > _2_PI)
            {
                THETA(curr_itr) = THETA(curr_itr) - _2_PI;
            }
            if(j % LOG_P == 0){
                logItration(res_f,curr_itr);
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        free(rMinMax);
        logItration(res_f,curr_itr);

    }

    free(curr_itr);
    free(next_itr);

}