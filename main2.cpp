//#define NDEBUG
// #define MYNDEBUG

#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "FloatTools.h"
#include "MyAssert.h"
#include "EquationStructure.h"

#include "UserInterface.h"

#define SAMPLES_AMOUNT 10


void         SolveLinear              (struct Equation *equation_info);

void         SolveQuadratic           (struct Equation *equation_info);

double       CalcDiscriminant         (struct Coefficients *input_coeffs);

bool         RunTest                  (struct Equation *test);

bool         RunAllTests              (void);


int main(void)
{
    struct Equation equation_info =
    {
        {0.0, 0.0, 0.0},
        {0, 0.0, 0.0}
    };

    if (!RunAllTests())
        return 0;

    GreetUser();

    if (!GetAllCoeffs(&equation_info.coeffs))
    {
        ProgramFailed();
        return 0;
    }

    SolveQuadratic(&equation_info);

    ShowProgramResults(&equation_info.roots);

    return 0;
}

void SolveLinear(struct Equation *equation_info)
{
    MyAssert(equation_info, ProgramFailed);
    // assert(equation_info);

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
    assert(equation_info != NULL);

    double disc = 0.0, sq_disc = 0.0;

    if (FloatEqual(equation_info->coeffs.a, 0.0))
    {
        equation_info = NULL; // фича Костяна
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


double CalcDiscriminant(struct Coefficients *input_coeffs)
{
    assert(input_coeffs != NULL);

    return pow(input_coeffs->b, 2) - 4 * input_coeffs->a * input_coeffs->c;
}


bool RunTest(struct Equation *sample)
{
    assert(sample != NULL);

    struct Equation result_info = {sample->coeffs, {0, 0.0, 0.0}};

    SolveQuadratic(&result_info);

    if (result_info.roots.total_roots != sample->roots.total_roots)
        return false;

    if (result_info.roots.total_roots == ZERO || result_info.roots.total_roots == INFINITE_NUMBER)
        return true;

    else if (result_info.roots.total_roots == ONE)
        return FloatEqual(result_info.roots.x1, sample->roots.x1);

    else
        return FloatEqual(result_info.roots.x1, sample->roots.x1) && FloatEqual(result_info.roots.x2, sample->roots.x2);
}

bool RunAllTests()
{
    struct Equation program_samples[SAMPLES_AMOUNT] =
    {
        { {0,     0,  0},  {INFINITE_NUMBER,      NAN, NAN} },
        { {0,     0,  2},  {           ZERO,      NAN, NAN} },
        { {0,    -1, -1},  {            ONE,       -1, NAN} },
        { {0,     1,  2},  {            ONE,       -2, NAN} },
        { {1,     0,  0},  {            ONE,        0, NAN} },
        { {1,     0,  2},  {           ZERO,      NAN, NAN} },
        { {1,     0, -4},  {            TWO,       -2,   2} },
        { {1,     2,  0},  {            TWO,       -2,   0} },
        { {1,     2,  1},  {            ONE,       -1, NAN} },
        { {1.5, 2.5, -4},  {            TWO,   -8.0/3,   1} }
    };

    for (int i = 0; i < SAMPLES_AMOUNT; i++)
    {
        if (!RunTest(&program_samples[i]))
        {
            printf("Program failed pre-launch tests. Cannot execute this program\n");
            return false;
        }
    }

    printf("Pre-launch tests completed successfully\n");
    return true;
}




