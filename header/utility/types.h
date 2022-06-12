#ifndef TYPE_H_
#define TYPE_H_
#include <stdbool.h>

typedef struct _linkedList LinkedList;

typedef struct {
    
    short n;
    short k;
    short m;

}Orbit;

typedef enum{

    POLAR = 1,
    REL_POLAR = 2,
    SPHERICAL = 3,
    REL_SPHERICAL = 4,
    SPIN = 5,
    REL_SPIN = 6

}simType;

typedef struct Config{
    bool itr_mode;
    simType type; // idicator to the type of equations to use 0 use regular 1 use reletivity 
    int log_p; // the number of ittrations to skip before logging
    int itrs; // number of iteration to run
    double revolutions; 
    double electron_charge; // electron charge value = 4.803e-10 esu
    double electron_mass;  // electron maxx value = 9.109383e-28 g
    double time_intervolt; // time elapsed between each iteration  
    double Hbar; // inital value of l if needes to be changed
    LinkedList* filtterList;// contains the exact orbits to simulate
    LinkedList* logFiles;// contains the files to write
    char* timeStamp;// the id of the test results 
    
}Config;

typedef struct {// struct simItr (simulation iteration) to hold the current and next iteration values
    double t;// iteration time
    double r;// iteration distance
    double r_dot;// iteration movment speed
    double r_dot_dot;// iteration movment acceleration
    double phi;// iteration angle
    double phi_dot;// iteration angleular speed
    double phi_dot_0;
    double gamma;//iteration rel mass mult
    double delataphi;//iteration angle of the perahelion
    double theta;
    double theta_dot;
    double theta_dot_dot;
    double epsilon;
}simItr;


#endif//TYPE_H_