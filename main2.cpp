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
#include "SolverEngine.h"


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

