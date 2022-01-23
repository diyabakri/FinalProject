#include "CalcRel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Valid
double calc_rel_theta_dot(double l , double gamma , double r , double m){
    
    r*=r;
    
    double arg1 = gamma * m;
    arg1 *= r;
    
    return(l/arg1);

}
// Valid
double calc_rel_gamma(double l , double m , double r, double r_dot){
   
    double arg1 = C;
    arg1 *= m*r;
    arg1 = l/arg1; 
    arg1*=arg1;
    arg1++;

    double arg2 = C;
    arg2 = r_dot/arg2;
    arg2*=arg2;
    arg2++;

    arg1 = sqrt(arg1/arg2);

    return arg1;
}
// Valid
double calc_rel_r_dot_dot(double l_sqr , double m , double gamma , double r , double e , double r_dot){
    
    double arg1,arg2,arg3;
    
    double r_sq = r*r; 
    
    arg1 = l_sqr;
    arg1/= gamma*m*r_sq*r;
    
    arg2 = e*e;
    arg2/= r_sq;
    
    arg3 = r_dot/C;
    arg3*= arg3;
    arg3 = 1-arg3;

    arg2 *= arg3;

    arg1 = arg1-arg2;

    arg1/= gamma*m;

    return arg1;
}
// Valid
double calc_rel_rmin(double a , double b , double c){

    double arg1 = b*b;
    
    arg1-=(a*c);
    arg1 = sqrt(arg1);

    double arg2 = -1*b;

    arg2+=arg1;

    return(arg2/a);

}
// Valid
double calc_rel_A(double m , double w){


    double arg1 = w*w;
    arg1 /= (C*C);

    double arg2 = 2*m*w;

    return(arg1 + arg2);
}
// Valid
double calc_rel_B(double m , double e , double w){

    double e_sqr = e*e;
    double arg1 = e_sqr*w;
    arg1 /= (C*C);

    double arg2 = m*e_sqr;

    return(arg1 +arg2);

}
// Valid
double calc_rel_C(double l_sqr , double e){
    
    double arg1 = pow(e,4);
    arg1/= (C*C);


    return(arg1 - l_sqr);

}

double calc_rel_w(double energy_level , double h_mult , double m, double alpha){

    double alpha_sqr = (alpha*alpha);
    
    double h_mult_sqr = h_mult * h_mult;

    double arg1 = (h_mult_sqr - alpha_sqr);

    arg1 = sqrt(arg1);

    arg1 += (energy_level-h_mult);
    arg1 *=arg1;

    arg1 = alpha_sqr/arg1;
    arg1++;

    arg1 = sqrt(arg1);
    arg1 = 1/arg1;

    arg1--;

    double arg2 = m*C*C;


    return(arg1*arg2);
}

double calc_rel_chi(double h_bar , double e, double r , double H_mult){
    
    double arg1 = h_bar*C*H_mult;
    arg1 = (e*e)/arg1;
    arg1*=arg1;
    arg1 = 1-arg1;

    return(sqrt(arg1));


}

double calc_alpha(double charge , double hbar ){
    double e_sqr = charge*charge;
    double arg1 = hbar*C;
    return(e_sqr/arg1); 
}