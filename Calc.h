#ifndef CALC_H_
#define CALC_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define BOHR_R 0.00000000529//5.29*10^-9 = a_0 bohr radios

double calc_R_dot_dot(double m , double r , double e , double l_sqr);

double calc_theta_dot(double l,double m,double r);

double calc_l_sqr(double m ,double e ,double r );

/*
    Calculates the R_max and the R_min for a given electron orbit
    Calculations are done acording to Atomic Structure And Spectral Lines Vol. I by Arnold Sommerfeld Page(116)
    where   

        (1) r_min + r_max = 2*a
        (2) r_min*max = b^2

        where a = n^2 * BOHR_R 
        and   b = (n-i)/n * a

    @params double n double i
    @return double result[2] containing the r_min at index 0 and r_max at index 1

*/  
double* clac_rmin_rmax(double n , double i );



#endif // CALC_H_
