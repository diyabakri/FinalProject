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
    for(int i = 0 ; i < length ; i++){
        
        char* currLine = configLines[i];

        if(strstr(currLine,"itrs =")!= NULL){
            config->itrs = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"Hbar =")!=NULL){
            config->Hbar = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"charge =")!=NULL){
            config->electron_charge = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"mass =")!=NULL){
            config->electron_mass = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"t =")!=NULL){
            config->time_intervolt = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"R =")!=NULL){
            config->init_r = parceDouble(currLine); 
            continue;
        }else if(strstr(currLine,"N =")!=NULL){
            config->n = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"K_LIST =")!=NULL){
            config->k_list = parceIntArray(currLine,&(config->k_size));
            continue;
        }else if(strstr(currLine,"M_LIST =")!=NULL){
            config->m_list = parceIntArray(currLine,&(config->m_size));
            continue;
        }else if(strstr(currLine,"Type =")!=NULL){
            config->type = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"logPerod =")!=NULL){
            config->log_p = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"results_path =")!=NULL){
            config->results_path = get_filepath(currLine);
            continue;
        }
    }
    

    for(int i = 0 ; i <length ; i++){
        free(configLines[i]);
    }
    free(configLines);

    fclose(config_f);

    return config;

}

int createResultPath(char* path , int orbits){
    int size = strlen(path)+1;
    char tempPath[size];
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
            #ifdef _WIN32 // make dir for windows
                sprintf(NFileCommand,"%s\\%s",nDir,kDir);
            #endif

            #ifndef _WIN32
                sprintf(NFileCommand,"%s/%s",nDir,kDir);
            #endif

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

            #ifdef _WIN32 // make dir for windows
                sprintf(KFileCommand,"%s\\%s",NFileCommand,mDir);
            #endif

            #ifndef _WIN32
                sprintf(KFileCommand,"%s/%s",NFileCommand,mDir);
            #endif

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

