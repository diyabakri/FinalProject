#include "Calc.h"

double calc_theta_dot(double l,double m,double r){
    return(l/(m*r*r));
}

double calc_R_dot_dot(double m , double r , double e , double l_sqr){

    double arg1,arg2;
    
    double r_sq = r*r; 
    
    arg1 = l_sqr;
    arg1/= m*r_sq*r;
    
    arg2 = e*e;
    arg2/= r_sq;
    
    arg1 = arg1-arg2;

    arg1/= m;

    return arg1;
}

double calc_l_sqr(double m ,double e ,double r){    
    return e*e*m*r;
}

double* calc_rmin_rmax(double n , double i ){
    
    
    double a = n*n;//4
    double b = (n-i)/n;//2
    b*=a;

    double dis = a*a;
    dis-= b*b;

    dis= sqrt(dis);

    double* results = (double*)malloc(2*sizeof(double));

    results[0] = results[1] = a;
    results[0]-= dis;
    results[1]+= dis;
    
    results[0]*=BOHR_R;
    results[1]*=BOHR_R;

    return results;

}

double calc_rel_thetat_dot(double l , double gamma , double r , double m){
    
    r*=r;
    
    double arg1 = gamma * m;
    arg1 *= r;
    
    return(l/arg1);

}

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

double calc_rel_w(double energy_level , double h_mult_sqr , double m){

    energy_level =0;
    
    double alpha_sqr = (FSC*FSC);

    double arg1 = (h_mult_sqr - alpha_sqr);
    arg1 = sqrt(arg1);
    arg1 += energy_level;

    arg1 = alpha_sqr/arg1;
    arg1++;

    arg1 = sqrt(arg1);
    arg1 = 1/arg1;

    double arg2 = m*C*C;

    arg1--;

    return(arg1*arg2);
}

double calc_rel_psi(double h_bar , double e, double r , double H_mult){
    
    double arg1 = h_bar*C*H_mult;
    arg1 = (e*e)/arg1;
    arg1*=arg1;
    arg1 = 1-arg1;

    return(sqrt(arg1));


}

double calc_polar_distance(double r1,  double r2, double theta1 , double theta2){
    
    double arg1 = r1*r1;
    arg1 += r2*r2;

    double arg2 = (2.0)*r1*r2;
    arg2 *= cos(theta2-theta1);

    return (sqrt(arg1 - arg2));

}