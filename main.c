#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulation/simulation.h"

int main()
{
    
    sim_init *config = getInitVals();
    int energy_level = 1;
    int max_energy_level = ORBITS;
    while( energy_level <= max_energy_level){

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

        ORBITS = energy_level;

        long begin_time = clock();

        sim_ele(results_f, config);  

        long end_time = clock();

        // close results.txt file
        for(int i  = 0 ; i < energy_level ; i++){
            fclose(results_f[i]);
        }

        printf("finished calculation for energy level = %d time = %f s \n",energy_level, (double)(end_time - begin_time) / CLOCKS_PER_SEC);
        energy_level++;
        config->itrs*=3;
        LOG_P*=3;
    }
    free(RES_PATH);

    free(config);

    return 0;
}
