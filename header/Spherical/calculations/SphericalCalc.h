#ifndef SPHERE_CALC_H_
#define SPHERE_CALC_H_

#include "../../utility/macros.h"


double sphere_calc_theta_min(double Nphi , double k);

double sphere_calc_r_dot_dot(double m , double r , double e , double k_sqr, double Hbar_sqr );

double sphere_calc_theta_dot_dot(double r , double r_dot , double theta , double theta_dot , double phi_dot);

double sphere_calc_phi_dot(double Nphi , double Hbar , double theta , double mass , double r);

double sphere_calc_init_phi_dot(double K, double Hbar , double nphi , double mass , double r);

double sphere_calc_spc_case_r_dot_dot(double r, double theta_dot , double charge , double mass);

double sphere_calc_spc_case_theta_dot(double k , double Hbar , double mass , double r);

#endif//SPHERE_CALC_H_