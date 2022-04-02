#ifndef SPHERE_CALC_H_
#define SPHERE_CALC_H_


#ifndef CALC_H_
    #define PI 3.14159265358979323846
    #define _2_PI  2 * PI
    #define BOHR_R 0.0000000052977210903//5.29*10^-9 = a_0 bohr radios 0.0000000052977210903
#endif


double sphere_calc_phi_dot(double NPhi , double Hbar , double mass , double r , double theta);

double sphere_calc_theta_dot(double Nphi, double Hbar , double phi_dot , double charge , double mass , double r);

double sphere_calc_theta_min(double Nphi , double k);

double sphere_calc_r_dot_dot(double r , double theta , double theta_dot , double phi_dot , double mass , double charge);

double sphere_calc_theta_dot_dot(double r , double r_dot , double theta , double theta_dot , double phi_dot);

double sphere_calc_phi_dot_dot(double r , double r_dot , double theta , double theta_dot , double phi_dot);

double sphere_calc_init_phi_dot(double K, double Hbar , double nphi , double mass , double r);

double sphere_calc_spc_case_r_dot_dot(double r, double theta_dot , double charge , double mass);

double sphere_calc_spc_case_theta_dot(double k , double Hbar , double mass , double r);

#endif//SPHERE_CALC_H_