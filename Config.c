#include "Config.h"

sim_init* getInitVals(){
    
    FILE* config_f = fopen(CONFIG_PATH,"r");


    int length = -1;
    char** configLines = readLines(config_f,&length);

    sim_init* config = (sim_init*)malloc(sizeof(sim_init));
   

    config->itrs = parceInt(configLines[0],strlen(configLines[0]));
    config->init_r = parceDouble(configLines[1],strlen(configLines[1]));
    config->electron_charge = parceDouble(configLines[2],strlen(configLines[2]));
    config->electron_mass = parceDouble(configLines[3],strlen(configLines[3]));
    config->time_intervolt = parceDouble(configLines[4],strlen(configLines[4]));
    config->l = parceDouble(configLines[5],strlen(configLines[5])); 
    config->results_path = get_filepath(configLines[6]);

    for(int i = 0 ; i <length ; i++){
        free(configLines[i]);
    }
    free(configLines);

    return config;

}
