#include "../../../header/utility/iterator.h"


void iterate(simItr* curr_itr , simItr* next_itr , Config* config){

    T(next_itr) += T_INTERVAL;
    R(next_itr) = R(curr_itr)+(R_DOT(curr_itr)* T_INTERVAL);
    R_DOT(next_itr) = R_DOT(curr_itr) + (R_DOT_DOT(curr_itr) * T_INTERVAL);
    PHI(next_itr) = PHI(curr_itr) + (PHI_DOT(curr_itr)* T_INTERVAL);
    if (PHI(next_itr) > _2_PI)
    {
        PHI(next_itr) = PHI(next_itr) - _2_PI;
    }
    if (TYPE == SPHERICAL || TYPE == REL_SPHERICAL || TYPE == SPIN)
    {
        THETA(next_itr) = THETA(curr_itr)+ (THETA_DOT(curr_itr)*T_INTERVAL);
        THETA_DOT(next_itr) = THETA_DOT(curr_itr)+(THETA_DOT_DOT(curr_itr)*T_INTERVAL);
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