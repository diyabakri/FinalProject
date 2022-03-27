#include "../../../header/calculations/SphericalCalc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double sphere_calc_phi_dot(double NPhi , double Hbar , double mass , double r , double theta){
    
    double arg1 = NPhi*Hbar;

    if(NPhi == 0){
        return 0;
    }
    
    double arg2 = sin(theta);
    arg2*=arg2;
    
    arg2 *= (r*r);
    arg2 *= mass;
    return(arg1/arg2);
}

double sphere_calc_theta_dot(double Nphi, double Hbar , double phi_dot , double charge , double mass , double r ){
    
    double r_sqr = r*r;
    double arg1 = mass*r*r_sqr;
    arg1 = (charge*charge)/arg1;
    // printf("e^2 / m*r^3 = %E\n",arg1);

    double arg2 = r_sqr*mass;
    double arg3 = (Nphi*Hbar*phi_dot);

    arg2 = arg3/arg2;

    double final = arg1 - arg2 ;

    if(final < 0 ){
        // printf("Warning : negative value under square root in Theta Dot\n");
        return 0;
    }
    return(sqrt(final));

}

double sphere_calc_theta_min(double Nphi , double k){

    double arg1 = Nphi/k;

    return(asin(arg1));

}

double sphere_calc_r_dot_dot(double r , double theta , double theta_dot, double phi_dot , double mass , double charge){
    
    double arg1 = sin(theta);
    arg1 *= arg1;
    arg1 *= (phi_dot*phi_dot);
    arg1 += (theta_dot * theta_dot);
    arg1 *= r;

    double arg2 = (charge * charge);
    arg2 /= (mass*r*r);

    return (arg1 - arg2);

}

double sphere_calc_theta_dot_dot(double r , double r_dot , double theta , double theta_dot , double phi_dot){

    double arg1 = sin(theta) * cos(theta);
    arg1 *= (phi_dot*phi_dot);

    double arg2 = r_dot/r;
    arg2 *= (2*theta_dot);
    
    return (arg1 - arg2);
}

double sphere_calc_phi_dot_dot(double r , double r_dot , double theta , double theta_dot , double phi_dot){
    
    double arg1 = cos(theta);// might change later
    arg1 /= sin(theta);
    arg1 =arg1 *(-2*theta_dot*phi_dot);

    double arg2 = r_dot/r;
    arg2*= (2*phi_dot);

    return (arg1 - arg2); 

}

double sphere_calc_init_phi_dot(double K, double Hbar , double Nphi , double mass , double r){
    
    if(Nphi == 0 ){
        return 0;
    }

    double arg1 = K*K*Hbar;

    double arg2 = Nphi*mass*r*r;

    return(arg1/arg2);

}


double sphere_calc_spc_case_r_dot_dot(double r, double theta_dot , double charge , double mass){

    double arg1 = r*theta_dot*theta_dot;

    double arg2 = charge*charge;
    
    arg2/= (mass*r*r);

    return arg1 - arg2;

}

double sphere_calc_spc_case_theta_dot(double k , double Hbar , double mass , double r){

    double arg1 = k*k*Hbar*Hbar;

    double arg2 = r*r*mass;

    return(arg1/arg2);
    
    
}

