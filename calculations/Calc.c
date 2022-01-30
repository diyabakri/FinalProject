#include "Calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

double calc_Hbar_sqr(double m ,double e ,double r){    
    return e*e*m*r;
}

double* calc_rmin_rmax(double n , double k ){
    
    
    double a = n*n;
    double b = k/n;
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

