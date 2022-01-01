// -------------MACROS--------------------
    //--------simitrs macros--------
    #define T(itr)           (itr->t)
    #define R(itr)           (itr->r)
    #define R_DOT(itr)       (itr->r_dot)
    #define R_DOT_DOT(itr)   (itr->r_dot_dot)
    #define THETA(itr)       (itr->theta)
    #define THETA_DOT(itr)   (itr->theta_dot)
    //--------config macros--------
    #define MASS        (config->electron_mass) 
    #define CHARGE      (config->electron_charge)
    #define T_INTERVAL  (config->time_intervolt)
    #define L           (config->Hbar)
    #define INIT_R      (config->init_r)
    #define RES_PATH    (config->results_path)
    #define ORBITS      (config->n)
    #define SUBORBITS   (config->i)
    #define SOSIZE      (config->so_size)
    #define LOG_P       (config->log_p)
    //---------Result mactros------
    #define R_MIN       (rMinMax[0])
    #define R_MAX       (rMinMax[1])
//----------------------------------------