#ifndef SPIN_H_
#define SPIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../config/Config.h"
#include "calculations/SpinCalc.h"
#include "../utility/macros.h"
#include "../utility/types.h"
#include "../utility/iterator.h"
#include "../Polar/calculations/Calc.h"
#include "../Polar/calculations/CalcRel.h"
#include "../Spherical/calculations/SphericalCalc.h"
#include "../Spherical/calculations/RelSphericalCalc.h"

void spin_sim_ele(Config *config);

void logItration(FILE *result_f ,simItr* itr);

#endif //SPIN_H_