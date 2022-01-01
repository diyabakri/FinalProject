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
    config->Hbar = parceDouble(configLines[5]); 
    config->n = parceInt(configLines[6]);
    config->i = parceIntArray(configLines[7],&(config->so_size));
    config->reltive = parceInt(configLines[8]);
    config->log_p = parceInt(configLines[9]);
    config->results_path = get_filepath(configLines[10]);

    for(int i = 0 ; i <length ; i++){
        free(configLines[i]);
    }
    free(configLines);

    fclose(config_f);

    return config;

}

int createResultPath(char* path , int orbits){
    
    char tempPath[strlen(path)+1];
    strcpy(tempPath,path);
    char* maindir = strtok(tempPath,"/");
    char* seconddir = strtok(NULL,"/");
    char commmandbuffer[107];
    memset(commmandbuffer,0,100);
    struct stat s;
    
    sprintf(commmandbuffer,"mkdir %s",maindir);
    
    if(stat(maindir,&s)!=0){
        system(commmandbuffer);
    }

    for(int i = 0 ; i < orbits ; i++){
            char tempcom[100];
            sprintf(tempcom,"%s/%s",maindir,seconddir);
            sprintf(tempcom,tempcom,(i+1));
        if(stat(tempcom,&s)!=0){

            sprintf(commmandbuffer,"mkdir %s",tempcom);
            system(commmandbuffer);
        }   
    }

    return 1;
}

