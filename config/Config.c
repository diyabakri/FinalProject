#include "Config.h"

sim_init* getInitVals(){
    

    FILE* config_f = fopen(CONFIG_PATH,"r");
    if (config_f == NULL){
        perror("ERROR opening Config file");
        exit(EXIT_FAILURE);
    }


    int length = -1;
    char** configLines = readLines(config_f,&length);
    sim_init* config = (sim_init*)malloc(sizeof(sim_init));
   

    config->itrs = parceInt(configLines[0]);
    config->init_r = parceDouble(configLines[1]);
    config->electron_charge = parceDouble(configLines[2]);
    config->electron_mass = parceDouble(configLines[3]);
    config->time_intervolt = parceDouble(configLines[4]);
    config->l = parceDouble(configLines[5]); 
    config->n = parceInt(configLines[6]);
    config->log_p = parceInt(configLines[7]);
    config->results_path = get_filepath(configLines[8]);

    for(int i = 0 ; i <length ; i++){
        free(configLines[i]);
    }
    free(configLines);

    fclose(config_f);

    return config;

}
