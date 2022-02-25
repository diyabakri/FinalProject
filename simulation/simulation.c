#include "simulation.h"

#include <float.h>

void logItration(FILE *result_f ,simItr* itr){
    
    fprintf(result_f, "t= %E\t", T(itr) );

    fprintf(result_f, "r= %E\t", R(itr) );

    fprintf(result_f, "r'= %E\t", R_DOT(itr) );
    fprintf(result_f, "r''= %E\t", R_DOT_DOT(itr) );
    
    fprintf(result_f, "phi= %E\t", PHI(itr) );
    fprintf(result_f, "phi'= %E\t", PHI_DOT(itr));

    if(THETA(itr) != -1.0){

        fprintf(result_f,"theta= %E\t",THETA(itr));
    
    }
    if(THETA_DOT(itr) != -1.0){
    
        fprintf(result_f,"theta'= %E\t",THETA_DOT(itr));
    
    }


    if (GAMMA(itr) != -1.0){ 
    
        fprintf(result_f, "gamma= %E\t", GAMMA(itr));
    
    }
    
    
    if(DELTAPHI(itr) != -1.0){
    
        fprintf(result_f, "deltaPhi= %E\t", DELTAPHI(itr));
    
    }

    fprintf(result_f, "\n");
    
}

void polar_sim_ele(FILE **result_files, Config *config){
    
    double _2_PI =  2 * PI;

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;

    for (int i = 1 ; i <= N ; i++){

        if(K_LIST[0]!= 0 || K_SIZE !=1){
        
            bool isSimulated = false;
            
            for(int j = 0 ; j < K_SIZE ; j++){
                if(K_LIST[j] == i ){
                    isSimulated = true;
                    break;
                }
            }
            if(isSimulated==false){
                continue;
            }
        }
        
        FILE* res_f = result_files[N-i];
        double K = i;
        double* rMinMax = calc_rmin_rmax(N,K);
        double curr_l = HBAR*K;
        double K_sqr = K*K;


        
        T(curr_itr) = 0;
        R(curr_itr) = R_MIN;
        R_DOT(curr_itr) = 0;
        R_DOT_DOT(curr_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE, K_sqr*Hbar_sqr);
        PHI(curr_itr) = 0;
        PHI_DOT(curr_itr) = calc_phi_dot(curr_l, MASS, R(curr_itr));
        
        GAMMA(curr_itr) = -1.0;
        DELTAPHI(curr_itr)= -1.0;
        THETA(curr_itr) = -1.0;
        THETA_DOT(curr_itr)=-1.0;
        GAMMA(next_itr) = -1.0;
        DELTAPHI(next_itr)= -1.0;
        THETA(next_itr) = -1.0;
        THETA_DOT(next_itr)=-1.0;

        for (int j = 1; j < config->itrs; j++){
                
            T(next_itr) += T_INTERVAL;
            R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
            R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
            PHI(next_itr) = PHI(curr_itr) + (PHI_DOT(curr_itr)* T_INTERVAL);
            R_DOT_DOT(next_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE,K_sqr* Hbar_sqr);
            PHI_DOT(next_itr) = calc_phi_dot(curr_l, MASS, R(curr_itr));

            if (PHI(curr_itr) > _2_PI)
            {
                PHI(curr_itr) = PHI(curr_itr) - _2_PI;
            }
            if (PHI(next_itr) > _2_PI)
            {
                PHI(next_itr) = PHI(next_itr) - _2_PI;
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

void polar_sim_rel_ele(FILE **result_files , Config *config){
    double _2_PI =  2 * PI;
    
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
        
        if(K_LIST[0]!= 0 || K_SIZE !=1){
        
            bool isSimulated = false;
            
            for(int j = 0 ; j < K_SIZE ; j++){
                if(K_LIST[j] == i ){
                    isSimulated = true;
                    break;
                }
            }
            if(isSimulated==false){
                continue;
            }
        }
        
        FILE* res_f = result_files[N-i];
        // printf(" n-i = %d\n",(N-i));


        // The multiplier of H_BAR
        double K = i;
        // double* rMinMax = calc_rmin_rmax(N,K);
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
        double prevMaxPhi= 0;
        double prevR = 0;
        
        
        T(curr_itr) = 0;
        R(curr_itr) = rel_rmin;
        R_DOT(curr_itr) = 0;
        GAMMA(curr_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));
        R_DOT_DOT(curr_itr) = calc_rel_r_dot_dot(K_sqr*Hbar_sqr,MASS,GAMMA(curr_itr),R(curr_itr),CHARGE,R_DOT(curr_itr));
        PHI(curr_itr) = 0;
        PHI_DOT(curr_itr) = calc_rel_phi_dot(curr_l,GAMMA(curr_itr),R(curr_itr),MASS);
        DELTAPHI(curr_itr) = 0;

        DELTAPHI(next_itr) = 0;
        THETA(curr_itr) = -1.0;
        THETA(next_itr) = -1.0;
        THETA_DOT(curr_itr) = -1.0;
        THETA_DOT(next_itr) = -1.0;


        for (int j = 1; j < config->itrs; j++){
                
            T(next_itr) += T_INTERVAL;
            R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
            R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
            PHI(next_itr) = PHI(curr_itr) + (PHI_DOT(curr_itr)* T_INTERVAL);
            if (PHI(next_itr) > _2_PI){
                PHI(next_itr) = PHI(next_itr) - _2_PI;
            }
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
                    if(prevMaxPhi != 0){

                        DELTAPHI(curr_itr) = PHI(curr_itr) - prevMaxPhi;
                        // printf("curr PHI = %.*E , prev PHI  = %.*E \t",PHI(curr_itr),DECIMAL_DIG,prevPhi,DECIMAL_DIG);
                        // printf(" currMaxth - prevMAxPhi  %E, acurrate %E \n",DELTAPHI(curr_itr), (((2*PI)/chi)-2*PI));
                    }
                                                
                    prevR = R(curr_itr);
                    prevMaxPhi = PHI(curr_itr);

                }

            }

            prevPhi = PHI(curr_itr);
            
            GAMMA(next_itr) = calc_rel_gamma(curr_l,MASS,R(curr_itr),R_DOT(curr_itr));

            DELTAPHI(next_itr) = DELTAPHI(curr_itr);

            if (PHI(curr_itr) > _2_PI)
            {
                PHI(curr_itr) = PHI(curr_itr) - _2_PI;
            }
            if(j % LOG_P == 0){
                logItration(res_f,curr_itr);

            } 
            
            simItr* temp = curr_itr;
            curr_itr = next_itr;
            next_itr = temp;
        }

        // free(rMinMax);
        logItration(res_f,curr_itr);

    }

    free(curr_itr);
    free(next_itr);

}

void spherical_sim_ele(FILE **result_files , Config *config){

    double _2_PI =  2 * PI;

    simItr *curr_itr , *next_itr;

    curr_itr = (simItr*)malloc(sizeof(simItr));
    next_itr = (simItr*)malloc(sizeof(simItr));

    long double Hbar_sqr = HBAR*HBAR;
    int fileIndex = 0;

    for (int i = 1 ; i <=N ; i++){

        if(K_LIST[0]!= 0 || K_SIZE !=1){
        
            bool isSimulated = false;
            
            for(int j = 0 ; j < K_SIZE ; j++){
                if(K_LIST[j] == i ){
                    isSimulated = true;
                    break;
                }
            }
            if(isSimulated==false){
                fileIndex+=(i+1);
                continue;
            }
        }
        
        double K = i;
        double curr_l = HBAR*K;
        double K_sqr = K*K;


        for(double m = 0 ; m <= K ; m++){

            double Nphi = K-m;
            // printf("Nphi %E\n",Nphi);

            double thetamin= sphere_calc_theta_min(Nphi,K);
            FILE* res_f = result_files[fileIndex];
            
            if(M_LIST[0]!= 0 || M_SIZE !=1){
        
            bool isSimulated = false;
            
            for(int j = 0 ; j < M_SIZE ; j++){
            
                if(M_LIST[j] == m ){
                    isSimulated = true;
                    break;
                }
            }
                if(isSimulated==false){
                    fileIndex++;
                    continue;
                }
            }
            
            T(curr_itr) = 0;
            R(curr_itr) = BOHR_R;
            R_DOT(curr_itr) = 0;
            R_DOT_DOT(curr_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE, K_sqr*Hbar_sqr);
            THETA(curr_itr) = thetamin;
            THETA_DOT(curr_itr)=0;
            PHI(curr_itr) = 0;
            PHI_DOT(curr_itr) =sphere_calc_phi_dot(Nphi,HBAR,MASS,R(curr_itr),THETA(curr_itr));
            GAMMA(curr_itr) = -1.0;
            DELTAPHI(curr_itr)= -1.0;

            T(next_itr) = 0;
            R(next_itr) = BOHR_R;
            R_DOT(next_itr) = 0;
            R_DOT_DOT(next_itr)=0;
            PHI(next_itr) = 0;
            PHI_DOT(next_itr) = 0;
            THETA(next_itr) = thetamin;
            // printf("theta min = %E m = %E , k =%E\n",THETA(next_itr),m,K);
            THETA_DOT(next_itr)=0;
            GAMMA(next_itr) = -1.0;
            DELTAPHI(next_itr)= -1.0;

            for (int it = 1; it < config->itrs; it++){
                    
                T(next_itr) += T_INTERVAL;
                R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
                R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
                R_DOT_DOT(next_itr) = calc_R_dot_dot(MASS, R(curr_itr), CHARGE,K_sqr* Hbar_sqr);
                PHI(next_itr) = PHI(curr_itr) + (PHI_DOT(curr_itr)* T_INTERVAL);
                PHI_DOT(next_itr) = sphere_calc_phi_dot(Nphi,HBAR,MASS,R(curr_itr),THETA(curr_itr));
                THETA(next_itr) = THETA(curr_itr)+ (THETA_DOT(curr_itr)*T_INTERVAL); 
                THETA_DOT(next_itr) = sphere_calc_theta_dot(Nphi,HBAR,PHI_DOT(curr_itr),CHARGE,MASS,R(curr_itr));
                // break;
                if (PHI(curr_itr) > _2_PI)
                {
                    PHI(curr_itr) = PHI(curr_itr) - _2_PI;
                }
                if (PHI(next_itr) > _2_PI)
                {
                    PHI(next_itr) = PHI(next_itr) - _2_PI;
                }
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

    }
    
    free(curr_itr);
    free(next_itr);

}
