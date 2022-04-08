#include "../../../header/calculations/RelSphericalCalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


double rel_sphere_calc_r_dot_dot(double k_sqr ,double Hbar_sqr , double mass , double gamma , double r , double charge , double r_dot){
        
    double arg1,arg2,arg3;
    
    double r_sq = r*r; 
    
    arg1 = k_sqr*Hbar_sqr;
    arg1/= gamma*mass*r_sq*r;
    
    arg2 = charge*charge;
    arg2/= r_sq;
    
    arg3 = r_dot/C;
    arg3*= arg3;
    arg3 = 1-arg3;

    arg2 *= arg3;

    arg1 = arg1-arg2;

    arg1/= gamma*mass;

    return arg1;
}

double rel_sphere_calc_phi_dot(double Nphi , double Hbar , double theta , double mass , double r, double gamma){

    double arg1 = Nphi*Hbar;

    double arg2 = sin(theta);
    arg2*= arg2;
    arg2*= (gamma*mass*r*r);

    return (arg1/arg2);

}

double rel_sphere_calc_theta_dot_dot(double r , double r_dot , double theta , double theta_dot , double phi_dot , double charge , double mass , double gamma){

    double arg1 = sin(theta) * cos(theta);
    arg1 *= (phi_dot*phi_dot);

    double arg2 = r_dot/r;
    arg2 *= (2*theta_dot);
    
    double arg3 = gamma*mass*C*C*r;
    arg3 = (charge*charge)/arg3;
    arg3 = (1-arg3);
    arg2*=arg3;

    return (arg1 - arg2);
}

double rel_sphere_calc_gamma(double k , double Hbar , double mass , double r, double r_dot){

    double arg1 = C;
    arg1 *= mass*r;
    arg1 = (k*Hbar)/arg1; 
    arg1*=arg1;
    arg1++;

    double arg2 = C;
    arg2 = r_dot/arg2;
    arg2*= arg2;
    arg2 = 1-arg2;

    arg1 = sqrt(arg1/arg2);

    return arg1;
}

double rel_sphere_calc_theta_min(double Nphi , double k){

    double arg1 = Nphi/k;

    return(asin(arg1));

}

double rel_sphere_calc_spc_case_r_dot_dot(double r, double theta_dot , double charge , double mass, double gamma){

    double arg1 = r*theta_dot*theta_dot;

    double arg2 = charge*charge;
    
    arg2/= (mass*r*r);

    return arg1 - arg2;

}

double rel_sphere_calc_spc_case_theta_dot(double k , double Hbar , double mass , double r , double gamma){

    double arg1 = k*Hbar;

    double arg2 = r*r*mass;

    return(arg1/arg2);
    
}
