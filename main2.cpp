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

#include "UserInterface.h"
#include "TestRunner.h"
#include "SolverEngine.h"
#include "ImitatorOfAI.h"

int main(void)
{
    StartConversationAI();

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
        EndConversationAI();
        return 0;
    }

    SolveQuadratic(&equation_info);

    thinking();

    ShowProgramResults(&equation_info.roots);

    EndConversationAI();

    return 0;
}








