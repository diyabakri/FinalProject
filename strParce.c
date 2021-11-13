#include "strParce.h"


int parceInt(char* str){

    int n = strlen(str);
    int num = 0;
    short sig = 1;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '-'){
            sig = -1;
        }
        int curr_num = (int)(str[i]);
        if(curr_num >= 0x30 && curr_num <= 0x39){
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }
    }
    return num;
}

long parceLong(char* str){

    int n = strlen(str);
    long num = 0;
    short sig = 1;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '-'){
            sig = -1;
        }
        int curr_num = (int)(str[i]);
        if(curr_num >= 0x30 && curr_num <= 0x39){
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }
    }
    return num;
}

short parceShort(char* str){

    int n = strlen(str);
    short num = 0;
    short sig = 1;
    for(int i = 0 ; i < n ; i++){
        if(str[i] == '-'){
            sig = -1;
        }
        int curr_num = (int)(str[i]);
        if(curr_num >= 0x30 && curr_num <= 0x39){
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }
    }
    return num;
}

float parceFloat(char* str){

    int n = strlen(str);
    float num = 0;
    short sig = 1;
    short disp = 0;
    short powoft = 0;
    for(int i = 0 ; i < n ; i++){

        if(str[i] == '-'){
            sig = -1;
        }
        if(str[i] == '.'){
            disp = 1;
            continue;
        }
        int curr_num = (int)(str[i]);

        if(str[i]== 'E'){
            powoft += parceInt((str+i));
            break;
        }else if((curr_num >= 0x30 && curr_num <= 0x39) || disp == 1){
            if(disp){
                powoft--;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }
    }
    return num*pow(10,powoft);
}

double parceDouble(char* str){
    
    int n = strlen(str);
    double num = 0;
    short sig = 1;
    short disp = 0;
    short powoft = 0;
    for(int i = 0 ; i < n ; i++){

        if(str[i] == '-'){
            sig = -1;
        }
        if(str[i] == '.'){
            disp = 1;
            continue;
        }
        int curr_num = (int)(str[i]);

        if(str[i]== 'E'){
            powoft += parceInt((str+i));
            break;
        }else if((curr_num >= 0x30 && curr_num <= 0x39) || disp == 1){
            if(disp){
                powoft--;
            }
            num*=10;
            num+=(sig*(curr_num-0x30));
        }else if(num != 0){
            break;
        }
    }
    return num*pow(10,powoft);
}
