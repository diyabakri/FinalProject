#include "../../../header/simulation/simulation.h"
#include <stdio.h>
#include <float.h>

/*
*************************************
**                                 **
**   repeatative code functions    **
**                                 **
*************************************
*/

//---------------------------------------------

bool skip(Config* config , int k , int m){
    
    if(TYPE == SPHERICAL || TYPE == REL_SPHERICAL || TYPE == SPIN || TYPE == REL_SPIN){
        if(M_LIST[0]!= -1 || M_SIZE !=1){
            for(int j = 0 ; j < M_SIZE ; j++){
                if(M_LIST[j] == m ){
                    return false;
                }
            }
        }else{
            return false;
        }
    }
        
    if(K_LIST[0]!= 0 || K_SIZE !=1){
        for(int j = 0 ; j < K_SIZE ; j++){
            if(K_LIST[j] == k ){
                return false;
            }
        }
    }else{

        return false;
    
    }

    return true;
}

void iterate(simItr* curr_itr , simItr* next_itr , Config* config){

    T(next_itr) += T_INTERVAL;
    R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
    R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
    PHI(next_itr) = PHI(curr_itr) + (PHI_DOT(curr_itr)* T_INTERVAL);
    if (PHI(curr_itr) > _2_PI)
    {
        PHI(curr_itr) = PHI(curr_itr) - _2_PI;
    }
    if (PHI(next_itr) > _2_PI)
    {
        PHI(next_itr) = PHI(next_itr) - _2_PI;
    }
    if (TYPE == SPHERICAL || TYPE == REL_SPHERICAL || TYPE == SPIN)
    {

        THETA(next_itr) = THETA(curr_itr)+ (THETA_DOT(curr_itr)*T_INTERVAL);
        THETA_DOT(next_itr) = THETA_DOT(curr_itr)+(THETA_DOT_DOT(curr_itr)*T_INTERVAL);
        
        if (THETA(curr_itr) > _2_PI)
        {
            THETA(curr_itr) = THETA(curr_itr) - _2_PI;
        }
        if (THETA(next_itr) > _2_PI)
        {
            THETA(next_itr) = THETA(next_itr) - _2_PI;
        }
    
    }

}

void initItrations(simItr* itr , simType type){
    
    T(itr) = 0;
    R(itr) = 0;
    R_DOT(itr) = 0;
    R_DOT_DOT(itr) = 0;
    PHI(itr) = 0;
    PHI_DOT(itr) = 0;
    GAMMA(itr) = -1.0;
    DELTAPHI(itr)= -1.0;
    THETA(itr) = -1.0;
    THETA_DOT(itr)=-1.0;
    THETA_DOT_DOT(itr)=-1.0;
    EPSILON(itr) = -1.0;
    PHI_DOT_0(itr) = -1.0;

    
    if(type == REL_POLAR || type == REL_SPHERICAL || type == REL_SPIN){
    
        GAMMA(itr) = 0;
        DELTAPHI(itr) = 0;
    
    }

    if(type == SPHERICAL || type == REL_SPHERICAL || type == SPIN){
    
        THETA(itr) = 0;
        THETA_DOT(itr) = 0;
        THETA_DOT_DOT(itr) = 0;
    
    }

    if(type == SPIN || type == REL_SPIN){

        EPSILON(itr) = 0;
        PHI_DOT_0(itr) = 0;

    }
    
}

void logItration(FILE *result_f ,simItr* itr){
    
    fprintf(result_f, "t= %E\t", T(itr) );

    fprintf(result_f, "r= %E\t", R(itr) );

    fprintf(result_f, "r'= %E\t", R_DOT(itr) );
    fprintf(result_f, "r''= %E\t", R_DOT_DOT(itr) );
    
    fprintf(result_f, "phi= %E\t", PHI(itr) );
    fprintf(result_f, "phi'= %E\t", PHI_DOT(itr));
    
    if(PHI_DOT_0(itr) != -1.0){ 
        fprintf(result_f, "phi'_0= %E\t", PHI_DOT_0(itr));
        
    }
    if(THETA(itr) != -1.0){
        fprintf(result_f,"theta= %E\t",THETA(itr));
    }
    if(THETA_DOT(itr) != -1.0){
        fprintf(result_f,"theta'= %E\t",THETA_DOT(itr));
    }
    if(THETA_DOT_DOT(itr) != -1.0){
        fprintf(result_f,"theta''= %E\t",THETA_DOT_DOT(itr));
    }
    if(GAMMA(itr) != -1.0){ 
        fprintf(result_f, "gamma= %E\t", GAMMA(itr));
    }
    if(DELTAPHI(itr) != -1.0){
        fprintf(result_f, "deltaPhi= %E\t", DELTAPHI(itr));
    }
    if(EPSILON(itr) != -1.0){
        fprintf(result_f, "epsilon= %E\t", EPSILON(itr));
    }

    fprintf(result_f, "\n");
    
}

//---------------------------------------------

/*
*************************************
**                                 **
**   simulation code functions     **
**                                 **
*************************************
*/

//---------------------------------------------

void polar_sim_ele(FILE **result_files, Config *config){
    

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;

    for (int i = 1 ; i <= N ; i++){
        
        double K = i;

        if(skip(config,K,0)){
            continue;
        }
        
        FILE* res_f = result_files[N-i];

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

    }

    free(curr_itr);
    free(next_itr);

}

void polar_sim_rel_ele(FILE **result_files , Config *config){
    
    
    simItr *curr_itr , *next_itr;
    // keep track of vars for itration i adn a i+1
    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));
    // Hbar_sqr is the value of hbar squared
    double Hbar_sqr = HBAR*HBAR;
    // reached peak of the eclipse
    bool at_max = true;
    // start calculationg
    for (int i = 1 ; i <= N ; i++){
        
        double K = i;
        
        if(skip(config,K,0)){
            continue;
        }
        
        FILE* res_f = result_files[N-i];
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
                    
                    double  chi = calc_rel_chi(HBAR,CHARGE,R(curr_itr),(double)(K));
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

    }

    free(curr_itr);
    free(next_itr);

}

void spherical_sim_ele(FILE **result_files , Config *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
    int fileIndex = 0;

    for (int i = 1 ; i <=N ; i++){

        double K = i;

        if(skip(config,K,0)){
        
            fileIndex+=(i+1);
            continue;
        
        }
        
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        double* rMinMax = calc_rmin_rmax(N,K);

        for(double m = 0 ; m <= K ; m++){
       
            if(skip(config,K,m)){
            
                fileIndex++;
                continue;
        
            }
            
            double Nphi = K-m;

            double thetamin= sphere_calc_theta_min(Nphi,K);
            
            FILE* res_f = result_files[fileIndex];
            
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
                    THETA_DOT(next_itr) = sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr));
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

            fileIndex++;


        }

        free(rMinMax);

    }
    
    free(curr_itr);
    free(next_itr);

}

void rel_spherical_sim_ele(FILE **result_files , Config *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
    int fileIndex = 0;

    for (int i = 1 ; i <=N ; i++){

        double K = i;

        // if(skip(config,K,0)){
        
            // fileIndex+=(i+1);
            // continue;
        
        // }
        
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        double alpha = calc_alpha(CHARGE,HBAR);
        
        double w = calc_rel_w(N,K,MASS,alpha);

        double a = calc_rel_A(MASS,w);

        double b = calc_rel_B(MASS,CHARGE,w);

        double c = calc_rel_C(K_sqr*Hbar_sqr,CHARGE);

        double rel_rmin = calc_rel_rmin(a,b,c);

        double* rMinMax = calc_rmin_rmax(N,K);


        double  chi = calc_rel_chi(HBAR,CHARGE,R(curr_itr),(double)(K));

        for(double m = 0 ; m <= K ; m++){
            
            
            // if(skip(config,K,m)){
        
                // fileIndex++;
                // continue;
        
            // }
            
            double prevPhi = 0;
            double* prevMaxVec= NULL;
            double* currMaxVec= NULL;
            double prevR = 0;
            bool at_max = true;
            
            double Nphi = K-m;

            double thetamin= rel_sphere_calc_theta_min(Nphi,K);
            
            FILE* res_f = result_files[fileIndex];
            
            initItrations(curr_itr,TYPE);
            initItrations(next_itr,TYPE);

            double curr_l = HBAR*K;

            R(curr_itr) = R_MIN;

            GAMMA(curr_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

            THETA(curr_itr) = thetamin;

            if(m == K){
            
                PHI(next_itr) = PI/2;
                PHI(curr_itr) = PI/2;
                THETA_DOT(curr_itr) = rel_sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr),GAMMA(curr_itr));
                THETA_DOT(next_itr) = THETA_DOT(curr_itr);
                
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
                    THETA_DOT(next_itr) = rel_sphere_calc_spc_case_theta_dot(K,HBAR,MASS,R(curr_itr),GAMMA(curr_itr));
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
                        printf("N= %d ,K = %e, M = %e \n",N,K,m);
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
                    logItration(res_f,curr_itr);
                }
                simItr* temp = curr_itr;
                curr_itr = next_itr;
                next_itr = temp;
            }

            logItration(res_f,curr_itr);

            fileIndex++;

            free(currMaxVec);
        }

        free(rMinMax);

    }
    
    free(curr_itr);
    free(next_itr);

}

void spin_sim_ele(FILE **result_files , Config *config){

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
    int fileIndex = 0;

    for (int i = 1 ; i <=N ; i++){
        
        
        double K = i;
        
        if(skip(config,K,0)){
        
            fileIndex+=(i+1);
            continue;
        
        }
        
        double curr_l = HBAR*K;
        double K_sqr = K*K;

        double* rMinMax = calc_rmin_rmax(N,K);

        for(double m = 0 ; m <= K ; m++){
                
            if(skip(config,K,m)){
               
                fileIndex++;
                continue;
            
            }

            double Nphi = K-m;

            double thetamin= sphere_calc_theta_min(Nphi,K);
            
            FILE* res_f = result_files[fileIndex];
            
            initItrations(curr_itr,TYPE);
            initItrations(next_itr,TYPE);



            R(curr_itr) = R_MIN;
            THETA(curr_itr) = thetamin;
            
            PHI_DOT_0(curr_itr) = spin_calc_phi_dot_0(R(curr_itr),MASS,Nphi,HBAR,THETA(curr_itr));
            EPSILON(curr_itr) = spin_calc_epsilon(R(curr_itr),MASS,CHARGE,THETA(curr_itr),Nphi);

            PHI_DOT(curr_itr) = spin_calc_phi_dot(PHI_DOT_0(curr_itr),EPSILON(curr_itr));
            THETA_DOT_DOT(curr_itr) = spin_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr));
            R_DOT_DOT(curr_itr) = spin_calc_r_dot_dot(R(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr),MASS,CHARGE);
            
            logItration(res_f,curr_itr);

            for (int it = 1; it < config->itrs; it++){
            
                    
                iterate(curr_itr,next_itr,config);
                
                PHI_DOT_0(next_itr) = spin_calc_phi_dot_0(R(curr_itr),MASS,Nphi,HBAR,THETA(curr_itr));
                EPSILON(next_itr) = spin_calc_epsilon(R(curr_itr),MASS,CHARGE,THETA(curr_itr),Nphi);

                PHI_DOT(next_itr) = spin_calc_phi_dot(PHI_DOT_0(curr_itr),EPSILON(curr_itr));
                THETA_DOT_DOT(next_itr) = spin_calc_theta_dot_dot(R(curr_itr),R_DOT(curr_itr),THETA(curr_itr),THETA(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr));
                R_DOT_DOT(next_itr) = spin_calc_r_dot_dot(R(curr_itr),THETA(curr_itr),THETA_DOT(curr_itr),PHI_DOT_0(curr_itr),EPSILON(curr_itr),MASS,CHARGE);
            
                if(it % LOG_P == 0){
                    logItration(res_f,curr_itr);
                }
                simItr* temp = curr_itr;
                curr_itr = next_itr;
                next_itr = temp;
            }

            logItration(res_f,curr_itr);

            fileIndex++;


        }

        free(rMinMax);

    }
    
    free(curr_itr);
    free(next_itr);
            printf("here\n");

}

//---------------------------------------------
