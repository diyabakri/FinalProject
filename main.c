#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulation/simulation.h"

int main()
{
    
    Config *config = getInitVals();
    
    createResultPath(RES_PATH,N);

    int energy_level = 1;
    int max_energy_level = N;
    double ex_factor = 3;
    
    while( energy_level <= max_energy_level){
        
        //---------- OPEN RESULT FILES ------------
        FILE *results_f[energy_level]; 
        
        for(int i = 0 ; i < energy_level ; i++){
            char str[50];
            
            sprintf(str,RES_PATH,energy_level,i);
            results_f[i] = fopen(str,"w");

            if (results_f[i]== NULL){
                perror("ERROR creating restult files");
                exit(EXIT_FAILURE);
            }
        }
        //-----------------------------------------

        //------------ BEGIN SIMULATION -----------
        N = energy_level;

        long begin_time = clock();
        if(config->reltive){

            sim_rel_ele(results_f, config);  
        
        }else{

            sim_ele(results_f,config);
            
        }
        long end_time = clock();
        //-----------------------------------------

        // close results.txt file
        for(int i  = 0 ; i < energy_level ; i++){
            fclose(results_f[i]);
        }

        printf("finished calculation for energy level = %d time = %f s  with %d itrations\n\n",energy_level, (double)(end_time - begin_time) / CLOCKS_PER_SEC ,config->itrs);
        energy_level++;

        if(energy_level == 5 ){
            ex_factor = 2;
        }
        
        config->itrs*=ex_factor;
        LOG_P*=ex_factor;
    }
    
    free(RES_PATH);

    free(config);

    return 0;
}
