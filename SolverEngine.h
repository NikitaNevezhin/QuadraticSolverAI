#ifndef SolverEngine_h

#define SolverEngine_h

#include "EquationStructure.h"

void         SolveLinear              (struct Equation *equation_info);

void         SolveQuadratic           (struct Equation *equation_info);

double       CalcDiscriminant         (struct Coefficients *input_coeffs);

#endif
