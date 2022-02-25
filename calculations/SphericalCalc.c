#include "SphericalCalc.h"
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
