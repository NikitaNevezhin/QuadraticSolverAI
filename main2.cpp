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

    struct Equation equation_info = {};

    if (!RunAllTests())
        return EXIT_FAILURE;

    GreetUser();

    if (!GetAllCoeffs(&equation_info.coeffs))
    {
        ProgramFailed();
        EndConversationAI();
        return EXIT_FAILURE;
    }

    SolveQuadratic(&equation_info);

    Thinking();

    ShowProgramResults(&equation_info.roots);

    EndConversationAI();

    return EXIT_SUCCESS;
}








