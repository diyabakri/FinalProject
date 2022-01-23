#ifndef CALCREL_H_
#define CALCREL_H_

#define C (double)(29979245800)
#define FSC (1.0/137.0) // fine structur constant approximation

/*
*************************************************************************************************************
*** All calculations are done acording to Atomic Structure And Spectral Lines Vol. I by Arnold Sommerfeld ***
*************************************************************************************************************
*/

/**
    Calculates theta dot with relativty incorporated  "anugular speed" of and electron 
       
    where: theta = l / (gamma * m * r^2)

    @param double l = 1.05435246E-27 double gamma = calc_rel_gamma m =9.109383E-28 r = r of the currnt itration
    @return double theta_dot 

*/
double calc_rel_theta_dot(double l , double gamma , double r , double m);
/**
    Calculates gamma  "change of the mass" of and electron 

    @param double l = 1.05435246E-27 double gamma = calc_rel_gamma m =9.109383E-28 r = r of the currnt itration
    @return double theta_dot 

*/
double calc_rel_gamma(double l , double m , double r, double r_dot);
/**
    Calculates R_dot_dot  with relativty incorporated "acceleration" of and electron 
    where   

        gamma*m*r_dot_dot = (l^2)/(gamma*m*(r^3)) - (e^2)/(r^2)

    @param double m = 9.109383e-28 double e = 4.803 e-10 l_sqr = Calc_l_sqr r = r of the currnt itration gamma = calc_rel_gamma
    @return double r_dot_dot 

*/
double calc_rel_r_dot_dot(double l_sqr , double m , double gamma , double r , double e , double r_dot);
/**
    Calculates Rmin with relativty incorporated the starting point of the simulation 
    where   

        RMIN = ( -B + (B^2 - A*C)^0.5 ) / A

    @param double a = calc_rel_A , b = calc_rel_B , c = calc_rel_C  
    @return double Rmin 

*/
double calc_rel_rmin(double a , double b , double c);
/**
    Calculates rel_A to be used in calculating Rmin   
    where   

        A = 2*m*W + (W^2 / C^2)

    @param double m = 9.109383e-28 W = calc_rel_W
    @return double A 

*/
double calc_rel_A(double m , double w);
/**
    Calculates rel_B to be used in calculating Rmin   
    where   

        B = m*e^2 + (W*e^2 / C^2)

    @param double e = 4.803 e-10 W = calc_rel_W
    @return double B 

*/
double calc_rel_B(double m , double e , double w);
/**
    Calculates rel_C to be used in calculating Rmin   
    where   

        C = -(k*hbar)^2 + (e^4 / C(speed of light)^2)

    @param double e = 4.803 e-10  m = 9.109383e-28
    @return double C 

*/
double calc_rel_C(double l_sqr , double e);
/**
    Calculates rel_W to be used in calculating A,B for Rmin    
    where   

        1+(W/(m*c^2)) = (1+ (alpha^2 / (n-k + (k^2 - alpha^2)^0.5 )^2 ))^-0.5

    @param double e = 4.803 e-10  n = energy level k = current orbit  alpha = FSC 
    @return double W

*/
double calc_rel_w(double energy_level , double h_mult , double m , double alpha );

double calc_rel_psi(double h_bar , double e, double r , double energy_level);

double calc_alpha(double charge , double hbar );


#endif//CALCREL_H_