#include "../../../header/config/Config.h"
#include <time.h>

char* genrateTimeStamp(){

    time_t pctime = time(NULL);
    struct tm localTime = *localtime(&pctime);
    char* timeStr = (char*) malloc(100);

    sprintf(timeStr,"%02d.%02d.%02d_%02d:%02d:%02d", localTime.tm_year - 100  , localTime.tm_mon + 1, localTime.tm_mday, localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

    return timeStr;

}

FILE* getOrbitFile(Orbit orbit,char* genratedTimeStamp){
    
    char orbitPath[strlen(genratedTimeStamp)+100];

    if(orbit.m == -1){
        
        sprintf(orbitPath,"%s/results_N%hi/results_K%hi.txt",genratedTimeStamp,orbit.n,orbit.k);
        
    }else{

        sprintf(orbitPath,"%s/results_N%hi/results_K%hi/results_M%hi.txt",genratedTimeStamp,orbit.n,orbit.k,orbit.m);

    }
    printf("%s\n",orbitPath);
    FILE* logFile =  fopen(orbitPath,"w");
    if(logFile == NULL){
        printf("heree\n");
    }
    return logFile;
}

char* createResultsPath(LinkedList* filterList){
    
    char* path = genrateTimeStamp(); 
    
    char command[200];
    
    memset(command,0,200);

    int last_n = 0;
    int last_k = 0;
    int listSize = L_Size(filterList);
    
    sprintf(command,"mkdir %s",path);

    if(system(command)<0){
        return NULL;
    }

    for(int i = 0 ; i < listSize ; i++){
        Orbit* orbit = (Orbit*)L_Pop(filterList);

        if(orbit->n > last_n){
        // printf("n= %hi last_n = %d\n",orbit->n,last_n);             
            #ifdef _WIN32 // make dir for windows
                sprintf(command,"mkdir %s\\results_N%hi",path,orbit->n);
            #endif

            #ifndef _WIN32
                sprintf(command,"mkdir %s/results_N%hi",path,orbit->n);
            #endif
            
            if(system(command)<0){
                return NULL;
            }

            last_k = 0;
            last_n = orbit->n;
        }
        if(orbit->k > last_k && orbit->m != -1){
            #ifdef _WIN32 // make dir for windows
                sprintf(command,"mkdir %s\\results_N%hi\\results_K%hi",path,orbit->n,orbit->k);
            #endif

            #ifndef _WIN32
                sprintf(command,"mkdir %s/results_N%hi/results_K%hi",path,orbit->n,orbit->k);
            #endif
                    
            if(system(command)<0){
                return NULL;
            }
            
            last_k = orbit->k;
        }

        L_Append(filterList,orbit);

    }

    return path;
}

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
        if(strstr(currLine,"revolutions =") == currLine){
            config->revolutions = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"itrs =") == currLine){
            config->itrs = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"Hbar =") == currLine){
            config->Hbar = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"charge =") == currLine){
            config->electron_charge = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"mass =") == currLine){
            config->electron_mass = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"t =") == currLine){
            config->time_intervolt = parceDouble(currLine);
            continue;
        }else if(strstr(currLine,"R =") == currLine){
            config->init_r = parceDouble(currLine); 
            continue;
        }else if(strstr(currLine,"Type =") == currLine){
            config->type = parceInt(currLine);
            continue;
        }else if(strstr(currLine,"logPerod =") == currLine){
            config->log_p = parceInt(currLine);
            continue;
        }
    }
    
    config->filtterList = getFilterList(config->type);
    
    TIME_STAMP = createResultsPath(config->filtterList);

    int listSize = L_Size(FILTTER);

    LOG_FILES = newLinkedList();

    for(int i = 0 ; i < listSize ; i++){
        
        Orbit* orbit = (Orbit*)L_Pop(FILTTER);

        FILE* logfile = getOrbitFile(*orbit,TIME_STAMP);
        
        L_Append(LOG_FILES,logfile);

        L_Append(FILTTER,orbit);
    }

    fclose(config_f);
    config_f = fopen(CONFIG_PATH,"w");

    for(int i = 0 ; i <length ; i++){
        if(strstr(configLines[i],"TimeStamp =")!= NULL){
        fprintf(config_f,"TimeStamp =%s\n",TIME_STAMP);
        }else{
        fprintf(config_f,"%s\n",configLines[i]);
        }
        free(configLines[i]);
    }
    free(configLines);
    fclose(config_f);


    return config;

}

