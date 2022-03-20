#ifndef MACROS_H_
#define MACROS_H_
// -------------MACROS--------------------
    //--------simitrs macros--------
    #define T(itr)              (itr->t)
    #define R(itr)              (itr->r)
    #define R_DOT(itr)          (itr->r_dot)
    #define R_DOT_DOT(itr)      (itr->r_dot_dot)
    #define PHI(itr)            (itr->phi)
    #define PHI_DOT(itr)        (itr->phi_dot)
    #define PHI_DOT_DOT(itr)    (itr->phi_dot_dot)
    #define DELTAPHI(itr)       (itr->delataphi)
    #define THETA(itr)          (itr->theta)
    #define THETA_DOT(itr)      (itr->theta_dot)
    #define THETA_DOT_DOT(itr)  (itr->theta_dot_dot)
    #define GAMMA(itr)          (itr->gamma)
    //--------config macros--------
    #define MASS                (config->electron_mass) 
    #define CHARGE              (config->electron_charge)
    #define T_INTERVAL          (config->time_intervolt)
    #define HBAR                (config->Hbar)
    #define INIT_R              (config->init_r)
    #define RES_PATH            (config->results_path)
    #define N                   (config->n)
    #define K_LIST              (config->k_list)
    #define K_SIZE              (config->k_size)
    #define M_LIST              (config->m_list)
    #define M_SIZE              (config->m_size)
    #define LOG_P               (config->log_p)
    //---------Result mactros------
    #define R_MIN               (rMinMax[0])
    #define R_MAX               (rMinMax[1])
//----------------------------------------
#endif//MACROS_H_