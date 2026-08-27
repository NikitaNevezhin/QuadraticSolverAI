#include <math.h>
#include <assert.h>

#include "SolverEngine.h"
#include "EquationStructure.h"
#include "UserInterface.h"
#include "FloatTools.h"
#include "MyAssert.h"



double CalcDiscriminant(struct Coefficients *input_coeffs)
{
    MyAssert(input_coeffs, ProgramFailed);

    return pow(input_coeffs->b, 2) - 4 * input_coeffs->a * input_coeffs->c;
}

void SolveLinear(struct Equation *equation_info)
{
    MyAssert(equation_info, ProgramFailed);
    //assert(equation_info);

    if (FloatEqual(equation_info->coeffs.b, 0.0))
    {
        if (FloatEqual(equation_info->coeffs.c, 0.0))
        {
            equation_info->roots.total_roots = INFINITE_NUMBER;
            return;
        }
        else
        {
            equation_info->roots.total_roots = ZERO;
            return;
        }
    }

    else if (FloatEqual(equation_info->coeffs.c, 0.0))
    {
        equation_info->roots.x1 = 0.0;
        equation_info->roots.total_roots = ONE;
        return;
    }

    equation_info->roots.x1 = -(equation_info->coeffs.c / equation_info->coeffs.b);
    equation_info->roots.total_roots = ONE;
    return;
}


void SolveQuadratic(struct Equation *equation_info)
{
    MyAssert(equation_info, ProgramFailed);

    double disc = 0.0, sq_disc = 0.0;

    if (FloatEqual(equation_info->coeffs.a, 0.0))
    {
        // equation_info = NULL; // фича Костяна
        SolveLinear(equation_info);
        return;
    }

    disc = CalcDiscriminant(&(equation_info->coeffs));

    if (disc < 0)
        equation_info->roots.total_roots = ZERO;

    else
    {
        sq_disc = sqrt(disc);

        equation_info->roots.x1 = (-equation_info->coeffs.b - sq_disc) / (2 * equation_info->coeffs.a);
        equation_info->roots.x2 = (-equation_info->coeffs.b + sq_disc) / (2 * equation_info->coeffs.a);

        if (FloatEqual(disc, 0.0))
            equation_info->roots.total_roots = ONE;

        else
            equation_info->roots.total_roots = TWO;
    }
}
