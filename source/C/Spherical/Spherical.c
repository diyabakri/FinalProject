#include "../../../header/Spherical/Spherical.h"
#include <stdio.h>
#include <float.h>

void spherical_sim_ele(Config *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
    int listSize = L_Size(FILTTER);
    
    for (int i = 0 ; i < listSize ; i++){
        
        Orbit* currOrbit = L_Pop(FILTTER);

        double N = currOrbit->n;
        double K = currOrbit->k;
        double m = currOrbit->m;
       
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        double* rMinMax = calc_rmin_rmax(N,K);

        int sign = 1;
        bool theta_flag = false;
    
        double Nphi = K-m;

        double thetamin= sphere_calc_theta_min(Nphi,K);
        
        FILE* res_f = (FILE*)L_Pop(LOG_FILES);
                
        initItrations(curr_itr,TYPE);
        initItrations(next_itr,TYPE);

        R(curr_itr) = R_MIN;
        THETA(curr_itr) = thetamin;
        
        if(m == K){
        
            PHI(next_itr) = PI/2;
            PHI(curr_itr) = PI/2;
            THETA_DOT(curr_itr) = sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr));
            THETA_DOT(next_itr) = THETA_DOT(curr_itr);
            
            PHI_DOT(curr_itr) = 0;
            THETA_DOT_DOT(curr_itr) = 0;


        }else{

            PHI_DOT(curr_itr) = sphere_calc_phi_dot(Nphi,HBAR,THETA(curr_itr),MASS,R(curr_itr));
            THETA_DOT_DOT(curr_itr) = sphere_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT(curr_itr)); 

        }
            R_DOT_DOT(next_itr) = sphere_calc_r_dot_dot(MASS, R(curr_itr), CHARGE, K_sqr , Hbar_sqr);



        
        logItration(res_f,curr_itr);
        for (int it = 1; it < config->itrs; it++){
                
            iterate(curr_itr,next_itr,config);

            if(m == K){
                THETA_DOT(curr_itr) = (sign)*sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr));
                THETA_DOT(next_itr) = THETA_DOT(curr_itr);

                if (THETA(curr_itr)>= PI && !(theta_flag)){
                    theta_flag = true;
                    sign = -1;
                    PHI(curr_itr) = -PHI(curr_itr);
                    PHI(next_itr) = -PHI(next_itr);
                }else if(THETA(curr_itr) <= 0 && theta_flag){
                    theta_flag = false;
                    sign = 1;
                    PHI(curr_itr) = -PHI(curr_itr);
                    PHI(next_itr) = -PHI(next_itr);
                }
            }else{
                PHI_DOT(next_itr) = sphere_calc_phi_dot(Nphi,HBAR,THETA(curr_itr),MASS,R(curr_itr));
                THETA_DOT_DOT(next_itr) = sphere_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT(curr_itr)); 
            }
                R_DOT_DOT(next_itr) = sphere_calc_r_dot_dot(MASS, R(curr_itr), CHARGE, K_sqr , Hbar_sqr);

            if(it % LOG_P == 0){
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

void rel_spherical_sim_ele(Config *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;

    int listSize = L_Size(FILTTER);
    
    for (int i = 0 ; i < listSize ; i++){
        
        Orbit* currOrbit = L_Pop(FILTTER);

        double N = currOrbit->n;
        double K = currOrbit->k;
        double m = currOrbit->m;
        
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        double alpha = calc_alpha(CHARGE,HBAR);
        
        double w = calc_rel_w(N,K,MASS,alpha);

        double a = calc_rel_A(MASS,w);

        double b = calc_rel_B(MASS,CHARGE,w);

        double c = calc_rel_C(K_sqr*Hbar_sqr,CHARGE);

        double rel_rmin = calc_rel_rmin(a,b,c);

        double* rMinMax = calc_rmin_rmax(N,K);

        double  chi = calc_rel_chi(HBAR,CHARGE,(double)(K));

        int sign = 1;
        bool theta_flag = false;
    
        double prevPhi = 0;
        double* prevMaxVec= NULL;
        double* currMaxVec= NULL;
        double prevR = 0;
        bool at_max = true;
        
        double Nphi = K-m;

        double thetamin= rel_sphere_calc_theta_min(Nphi,K);
        
        FILE* res_f = (FILE*)L_Pop(LOG_FILES);
        
        initItrations(curr_itr,TYPE);
        initItrations(next_itr,TYPE);

        R(curr_itr) = R_MIN;

        GAMMA(curr_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

        THETA(curr_itr) = thetamin;

        if(m == K){
            
            PHI(next_itr) = PI/2;
            PHI(curr_itr) = PI/2;
            
            THETA_DOT(curr_itr) = (sign)*rel_sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr),GAMMA(curr_itr));
            THETA_DOT(next_itr) = THETA_DOT(curr_itr);
            
            if (THETA(curr_itr)>= PI && !(theta_flag)){
                sign = -1;
            }else if(THETA(curr_itr) <= 0 && theta_flag){
                sign = 1;
            }

            PHI_DOT(curr_itr) = 0;
            THETA_DOT_DOT(curr_itr) = 0;


        }else{

            PHI_DOT(curr_itr) = rel_sphere_calc_phi_dot(Nphi,HBAR,THETA(curr_itr),MASS,R(curr_itr),GAMMA(curr_itr));
            THETA_DOT_DOT(curr_itr) = rel_sphere_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT(curr_itr),CHARGE,MASS,GAMMA(curr_itr)); 

        }

        R_DOT_DOT(curr_itr) = rel_sphere_calc_r_dot_dot(K_sqr,Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));

        logItration(res_f,curr_itr);
        
        for (int it = 1; it < config->itrs; it++){

            iterate(curr_itr,next_itr,config);

            if(m == K){

                THETA_DOT(next_itr) = (sign)*rel_sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr),GAMMA(curr_itr));
                // THETA_DOT(next_itr) = THETA_DOT(curr_itr);

                if (THETA(next_itr)>= PI && !(theta_flag)){
                    
                    double overValue = (THETA(next_itr) - PI);
                    THETA(next_itr) = PI-overValue; 

                    theta_flag = true;
                    sign = -1;
                    PHI(next_itr) = -PHI(next_itr);
                
                }else if(THETA(next_itr) <= 0 && theta_flag){

                    THETA(next_itr) = 0-THETA(next_itr);

                    theta_flag = false;
                    sign = 1;
                    PHI(next_itr) = -PHI(next_itr);
                }

            }else{ 
                PHI_DOT(next_itr) = rel_sphere_calc_phi_dot(Nphi,HBAR,THETA(curr_itr),MASS,R(curr_itr),GAMMA(curr_itr));
                THETA_DOT_DOT(next_itr) = rel_sphere_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT(curr_itr),CHARGE,MASS,GAMMA(curr_itr));                    
            }

            R_DOT_DOT(next_itr) = rel_sphere_calc_r_dot_dot(K_sqr,Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));

            if (R_DOT(curr_itr)*R_DOT(next_itr) <= 0){
                at_max = !(at_max);
                if(at_max){
                    
                    currMaxVec = stoc(R(curr_itr),PHI(curr_itr),THETA(curr_itr));
                    // printf("r = %e  ,theta = %e, phi = %.*e \n",R(curr_itr),THETA(curr_itr),PHI(curr_itr),DECIMAL_DIG);
                    // printf("x = %.*e , y = %.*e , z = %.*e atan(y/x) = %.*e\n",currMaxVec[0],DECIMAL_DIG,currMaxVec[1],DECIMAL_DIG,currMaxVec[2],DECIMAL_DIG,atan2(currMaxVec[1],currMaxVec[0])+_2_PI,DECIMAL_DIG);
                    printf("N= %e ,K = %e, M = %e \n",N,K,m);
                    if(prevMaxVec != NULL){
                        
                        DELTAPHI(curr_itr) = rel_sphere_calc_deltaPhi(currMaxVec,prevMaxVec,R_MAX);
                        // printf("Rmax = %.*e\n",R(curr_itr),DECIMAL_DIG);
                        DELTAPHI(next_itr) = DELTAPHI(curr_itr);

                        free(prevMaxVec);
                        // printf("curr PHI = %.*E , prev PHI  = %.*E \t",PHI(curr_itr),DECIMAL_DIG,prevPhi,DECIMAL_DIG);
                        printf(" currMaxth - prevMaxVec  %E, acurrate %E \n",DELTAPHI(curr_itr), (((2*PI)/chi)-2*PI));
                    }
                                                
                    prevR = R(curr_itr);

                    prevMaxVec = currMaxVec;

                }

            }
            if(m == 0){
                prevPhi = PHI(curr_itr);
            }else if(m == K){
                prevPhi = THETA(curr_itr);
            }

            GAMMA(next_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));


            if(it % LOG_P == 0){
                logItration(res_f,next_itr);
            }
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        logItration(res_f,next_itr);


        free(currMaxVec);
    

        free(rMinMax);
        fclose(res_f);
        free(currOrbit);

    }
    
    free(curr_itr);
    free(next_itr);

}

//---------------------------------------------
