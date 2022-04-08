#ifndef TYPE_H_
#define TYPE_H_


typedef struct _linkedList LinkedList;

typedef enum{

    POLAR = 1,
    REL_POLAR = 2,
    SPHERICAL = 3,
    REL_SPHERICAL = 4

}simType;


typedef struct Config{

    int itrs; // number of iteration to run
    double init_r; // statring value of R in cm
    double electron_charge; // electron charge value = 4.803e-10 esu
    double electron_mass;  // electron maxx value = 9.109383e-28 g
    double time_intervolt; // time elapsed between each iteration  
    double Hbar; // inital value of l if needes to be changed
    int n; //the eneregy level to simulate.
    int*k_list; //the spific energy_levels to simulate if set to 0 all energy_levels will be simulated format ex: 1,2,3
    int k_size; // number of the energy_levels to simulate
    int*m_list;
    int m_size;
    simType type; // idicator to the type of equations to use 0 use regular 1 use reletivity 
    int log_p; // the number of ittrations to skip before logging 
    char* results_path; // url for the results to saved in

}Config;

typedef struct {// struct simItr (simulation itration) to hold the current and next itration values
    double t;// itration time
    double r;// itration distance
    double r_dot;// itration movment speed
    double r_dot_dot;// itration movment acceleration
    double phi;// itration angle
    double phi_dot;// itration angleular speed
    double gamma;//itration rel mass mult
    double delataphi;//itration angle of the perahelion
    double theta;
    double theta_dot;
    double theta_dot_dot;
}simItr;


#endif//TYPE_H_