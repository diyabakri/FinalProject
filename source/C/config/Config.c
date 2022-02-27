#include "../../../header/config/Config.h"

Config* getInitVals(){
    

    FILE* config_f = fopen(CONFIG_PATH,"r");
    if (config_f == NULL){
        perror("ERROR opening Config file");
        exit(EXIT_FAILURE);
    }


    int length = -1;
    
    char** configLines = readLines(config_f,&length);

    Config* config = (Config*)malloc(sizeof(Config));
   
    config->itrs = parceInt(configLines[0]);
    config->init_r = parceDouble(configLines[1]);
    config->electron_charge = parceDouble(configLines[2]);
    config->electron_mass = parceDouble(configLines[3]);
    config->time_intervolt = parceDouble(configLines[4]);
    config->Hbar = parceDouble(configLines[5]); 
    config->n = parceInt(configLines[6]);
    config->k_list = parceIntArray(configLines[7],&(config->k_size));
    config->m_list = parceIntArray(configLines[8],&(config->m_size));
    config->reltive = parceInt(configLines[9]);
    config->spherical = parceInt(configLines[10]);
    config->log_p = parceInt(configLines[11]);
    config->results_path = get_filepath(configLines[12]);

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
    
    char* nDir = strtok(tempPath,"/");
    char* kDir = strtok(NULL,"/");
    char* mDir = strtok(NULL,"/");
    int sysReturn;
    char commmandbuffer[157];

    memset(commmandbuffer,0,150);
    struct stat s;
    
    sprintf(commmandbuffer,"mkdir %s",nDir);
    
    if(stat(nDir,&s)!=0){
        sysReturn = system(commmandbuffer);
        if(sysReturn < 0){
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 1 ; i <= orbits ; i++){
        
        char NFileCommand[100];
            sprintf(NFileCommand,"%s/%s",nDir,kDir);
            sprintf(NFileCommand,NFileCommand,i);

            if(stat(NFileCommand,&s)!=0){

                sprintf(commmandbuffer,"mkdir %s",NFileCommand);
                sysReturn = system(commmandbuffer);
                if(sysReturn < 0){
                    exit(EXIT_FAILURE);
                }

            }   

        for(int j = 1 ; j <= i ; j++){
            
            char KFileCommand[150];
            sprintf(KFileCommand,"%s/%s",NFileCommand,mDir);
            
            sprintf(KFileCommand,KFileCommand,j);
        
            if(stat(KFileCommand,&s)!=0){

                sprintf(commmandbuffer,"mkdir %s",KFileCommand);
                sysReturn = system(commmandbuffer);
                if(sysReturn < 0){
                    exit(EXIT_FAILURE);
                }

            }   

        }

    }

    return 1;
}

