#ifndef SPHERE_CALC_H_
#define SPHERE_CALC_H_


#ifndef CALC_H_
    #define PI 3.14159265358979323846
    #define BOHR_R 0.0000000052977210903//5.29*10^-9 = a_0 bohr radios 0.0000000052977210903
#endif


double sphere_calc_phi_dot(double NPhi , double Hbar , double mass , double r , double theta);

double sphere_calc_theta_dot(double Nphi, double Hbar , double phi_dot , double charge , double mass , double r);

double sphere_calc_theta_min(double Nphi , double k);

#endif//SPHERE_CALC_H_