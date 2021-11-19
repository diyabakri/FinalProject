#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulation/simulation.h"

int main()
{
    
    sim_init *config = getInitVals();

    while( ORBITS >= 1){

        FILE *results_f[ORBITS]; 
        
        for(int i = 0 ; i < ORBITS ; i++){
            char str[50];
            
            sprintf(str,RES_PATH,ORBITS,i);
            results_f[i] = fopen(str,"w");

            if (results_f[i]== NULL){
                perror("ERROR creating restult files");
                exit(EXIT_FAILURE);
            }
        }

        long begin_time = clock();

        sim_ele(results_f, config);  

        long end_time = clock();

        // close results.txt file
        for(int i  = 0 ; i < ORBITS ; i++){
            fclose(results_f[i]);
        }

        printf("finished calculation for energy level = %d time = %f s \n",ORBITS, (double)(end_time - begin_time) / CLOCKS_PER_SEC);
        ORBITS--;
    }
    free(RES_PATH);

    free(config);

    return 0;
}
