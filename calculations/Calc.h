#ifndef CALC_H_
#define CALC_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define BOHR_R 0.00000000529//5.29*10^-9 = a_0 bohr radios
#define C (double)(29979245800)
#define FSC (1.0/137.0) // fine structur constant aprox
/*
    Calculates R_dot_dot "acceleration" of and electron
    Calculations are done acording to Atomic Structure And Spectral Lines Vol. I by Arnold Sommerfeld 
    where   

        m*r_dot_dot = (l^2)/(m*(r^3)) - (e^2)/(r^2)

    @params double m = 9.109383e-28 double e = 4.803 e-10 l_sqr = Calc_l_sqr r = r of the currnt itration
    @return double r_dot_dot 

*/
double calc_R_dot_dot(double m , double r , double e , double l_sqr);


/*

    Calculates the angel change rate of the electron movment
    Calculations are done acording to Atomic Structure And Spectral Lines Vol. I by Arnold Sommerfeld 
    where   

        theta_dot = L / m*(r^2)

    @params double m = 9.109383e-28 double e = 4.803 e-10  r = r of the currnt itration
    @return double THETA_dot 


*/
double calc_theta_dot(double l,double m,double r);


/*

    Calculates l squared with enought precision to cancle the deviation of rounding 
    Calculations are done acording to Atomic Structure And Spectral Lines Vol. I by Arnold Sommerfeld 
    where   

        l_sqr = (e^2)*m*r 

    @params double m = 9.109383e-28 double e = 4.803 e-10  r = BOHR_R
    @return double l_sqr which is acually (H-)^2 which the coefficient is added later in the code


*/
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
double* calc_rmin_rmax(double n , double i );

double calc_rel_thetat_dot(double l , double gamma , double r , double m);

double calc_rel_gamma(double l , double m , double r, double r_dot);

double calc_rel_r_dot_dot(double l_sqr , double m , double gamma , double r , double e , double r_dot);

double calc_rel_rmin(double a , double b , double c);

double calc_rel_A(double m , double w);

double calc_rel_B(double m , double e , double w);

double calc_rel_C(double l_sqr , double e);

double calc_rel_w(double energy_level , double h_mult_sqr , double m);

double calc_rel_psi(double h_bar , double e, double r , double energy_level);

double calc_polar_distance(double r1,  double r2, double theta1 , double theta2);

#endif // CALC_H_
