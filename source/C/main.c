#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../header/simulation/simulation.h"

int getFileNum(int n){
    n++;
    int sum = n*(n+1);
    sum/=2;
    sum--;

    return sum;
}

int main()
{
    
    Config *config = getInitVals();
    
    createResultPath(RES_PATH,N);

    int energy_level = 1;
    int max_energy_level = N;
    double ex_factor = 3;
    
    while( energy_level <= max_energy_level){
        
        //---------- OPEN RESULT FILES ------------
        FILE **results_f;
        int fileCount = 0;
        //---------- SPHERICAL SIMULATION ---------
        if(TYPE == SPHERICAL || TYPE == REL_SPHERICAL){

            fileCount = getFileNum(energy_level);

            results_f = (FILE**)malloc(sizeof(FILE*)*fileCount);

            int fileIndex = 0; 

            for(int i = 1 ; i <= energy_level ; i++){
                
                for(int j = 0 ; j <= i; j++){
                    
                    char str[100];
                    
                    sprintf(str,RES_PATH,energy_level,i,j);

                    results_f[fileIndex] = fopen(str,"w");
                    if (results_f[fileIndex] == NULL){
                        perror("ERROR creating result files"); 
                        exit(EXIT_FAILURE);
                    }
                    fileIndex++;

                }

            }
            
        }else{
            //---------- POLAR SIMULATION ------------
            fileCount = energy_level;

            results_f = (FILE**)malloc(sizeof(FILE*)*fileCount);

            for(int i = 1 ; i <= energy_level ; i++){
                
                char str[100];
                
                sprintf(str,RES_PATH,energy_level,i,0);
                results_f[i-1] = fopen(str,"w");

                if (results_f[i-1] == NULL){
                    perror("ERROR creating result files"); 
                    exit(EXIT_FAILURE);
                }

            }

        }
        
        //-----------------------------------------

        //------------ BEGIN SIMULATION -----------
        N = energy_level;
        // start timer
        long begin_time = clock();
        switch (TYPE)
        {
            case POLAR:

                polar_sim_ele(results_f,config);

            break;
            case REL_POLAR:

                polar_sim_rel_ele(results_f, config);  

            break;
            case SPHERICAL:
                spherical_sim_ele(results_f,config);
            break;
            case REL_SPHERICAL:
                rel_spherical_sim_ele(results_f,config);
            break;
        }
        // stop timer
        long end_time = clock();
        //-----------------------------------------

        // close results.txt file
        for(int i  = 0 ; i < fileCount ; i++){
            fclose(results_f[i]);
        }
        free(results_f);
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
