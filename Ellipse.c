#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulation.h"

int main()
{

    sim_init *config = getInitVals();

    FILE *results_f[ORBITS]; 

    for(int i = 0 ; i < ORBITS ; i++){
        char str[20];
        sprintf(str,"%s%d.txt",RES_PATH,i);
        results_f[i] = fopen(str,"w");
    }

    long begin_time = clock();

    sim_ele(results_f, config);  

    long end_time = clock();

    // close results.txt file
    for(int i  = 0 ; i < ORBITS ; i++){
        fclose(results_f[i]);
    }

    printf("program output is saved in ./result.txt \ncalculation time = %f s \n", (double)(end_time - begin_time) / CLOCKS_PER_SEC);

    free(RES_PATH);

    free(config);

    return 0;
}
