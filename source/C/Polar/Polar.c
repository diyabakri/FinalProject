#include "../../../header/Polar/polar.h"
#include <stdio.h>
#include <float.h>

void polar_sim_ele(Config *config){
    

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
   int listSize = L_Size(FILTTER);
    
    for (int i = 0 ; i < listSize ; i++){
        
        Orbit* currOrbit = L_Pop(FILTTER);

        double N = currOrbit->n;
        double K = currOrbit->k;
        
        FILE* res_f = (FILE*)L_Pop(LOG_FILES);

        double* rMinMax = calc_rmin_rmax(N,K);
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        initItrations(curr_itr,TYPE);
        initItrations(next_itr,TYPE);
        
        R(curr_itr) = R_MIN;
        R_DOT_DOT(curr_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE, K_sqr , Hbar_sqr);
        PHI_DOT(curr_itr) = calc_phi_dot(curr_l, MASS, R(curr_itr));

        for (int j = 1; j < config->itrs; j++){
                
            iterate(curr_itr,next_itr,config);

            R_DOT_DOT(next_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE,K_sqr , Hbar_sqr);
            PHI_DOT(next_itr) = calc_phi_dot(curr_l, MASS, R(curr_itr));

            if(j % LOG_P == 0){
                logItration(res_f,curr_itr);
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        logItration(res_f,curr_itr);

        free(rMinMax);
        fclose(res_f);

        free(currOrbit);


    }

    free(curr_itr);
    free(next_itr);

}

void polar_sim_rel_ele(Config *config){
    
    
    simItr *curr_itr , *next_itr;
    // keep track of vars for itration i adn a i+1
    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));
    // Hbar_sqr is the value of hbar squared
    double Hbar_sqr = HBAR*HBAR;
    // reached peak of the eclipse
    bool at_max = true;
    // start calculationg
    int listSize = L_Size(FILTTER);

    for (int i = 0 ; i < listSize ; i++){
        
        Orbit* currOrbit = L_Pop(FILTTER);

        double N = currOrbit->n;
        double K = currOrbit->k;
        
        FILE* res_f = (FILE*)L_Pop(LOG_FILES);

        // printf(" n-i = %d\n",(N-i));


        // The multiplier of H_BAR
        double* rMinMax = calc_rmin_rmax(N,K);
        // L is the value of H_Bar
        double curr_l = HBAR*K;
        double alpha = calc_alpha(CHARGE,HBAR);
        double w = calc_rel_w(N,K,MASS,alpha);

        double K_sqr=K*K;
        // K^2 for Hbar_sqr


        double a = calc_rel_A(MASS,w);

        double b = calc_rel_B(MASS,CHARGE,w);

        double c = calc_rel_C(K_sqr*Hbar_sqr,CHARGE);

        double rel_rmin = calc_rel_rmin(a,b,c);
        // printf("relativistic rmin = %E ,non relativistic rmin = %E\n\n",rel_rmin,R_MIN);

        // return;
        

        double prevPhi = 0;
        double prevMaxVec= 0;
        double prevR = 0;
        
        initItrations(curr_itr,TYPE);
        initItrations(next_itr,TYPE);

        R(curr_itr) = R_MIN;

        GAMMA(curr_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

        R_DOT_DOT(curr_itr) = calc_rel_r_dot_dot(K_sqr*Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));

        PHI_DOT(curr_itr) = calc_rel_phi_dot(curr_l,GAMMA(curr_itr),R(curr_itr),MASS);

        for (int j = 1; j < config->itrs; j++){
                
            iterate(curr_itr,next_itr,config);

            R_DOT_DOT(next_itr) = calc_rel_r_dot_dot(K_sqr*Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));
            PHI_DOT(next_itr) = calc_rel_phi_dot(curr_l,GAMMA(curr_itr),R(curr_itr),MASS);
            

            if (R_DOT(curr_itr)*R_DOT(next_itr) <= 0){
                at_max = !(at_max);
                if(at_max){
                    
                    double  chi = calc_rel_chi(HBAR,CHARGE,(double)(K));
                    // double test += ((2*PI)/chi)-2*PI;
                    
                    if (PHI(curr_itr) > _2_PI)
                    {
                        PHI(curr_itr) = PHI(curr_itr) - _2_PI;
                    }
                    if(prevMaxVec != 0){

                        DELTAPHI(curr_itr) = PHI(curr_itr) - prevMaxVec;
                        // printf("curr PHI = %.*E , prev PHI  = %.*E \t",PHI(curr_itr),DECIMAL_DIG,prevPhi,DECIMAL_DIG);
                        printf(" currMaxth - prevMaxVec  %E, acurrate %E \n",DELTAPHI(curr_itr), (((2*PI)/chi)-2*PI));
                    }
                                                
                    prevR = R(curr_itr);
                    prevMaxVec = PHI(curr_itr);

                }

            }

            prevPhi = PHI(curr_itr);
            
            GAMMA(next_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

            DELTAPHI(next_itr) = DELTAPHI(curr_itr);

            
            if(j % LOG_P == 0){
                logItration(res_f,curr_itr);

            } 
            
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        free(rMinMax);

        logItration(res_f,curr_itr);

        fclose(res_f);

        free(currOrbit);
    }

    free(curr_itr);
    free(next_itr);

}