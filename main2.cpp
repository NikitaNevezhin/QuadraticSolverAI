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

#define HELP_FLAG "-h"
#define TEST_FLAG "-t"

void ExplainProgram  (void);
void InvalidFlags    (void);
int  AnalyzeFlags    (int argc, char *argv[]);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        StartConversationAI();

        struct Equation equation_info = {};

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

    else
        return AnalyzeFlags(argc, argv);

}

void ExplainProgram(void)
{
    printf("This program solves quadratic equation.\n\n"
           "User gives three arguments as input and gets the existing roots.\n"
           "If roots doesn't exist, user gets \"There are no real roots\" message\n"
           "If there are infinite number of roots, user gets \"There is an infinite number of solutions\" message\n\n"
           "FLAGS:\n"
           "\"-h\" - gives the general info about the program\n"
           "\"-t SOMEFILE\" - takes info from SOMEFILE and tests program on its info in case it is possible\n\n"
           "If there are no flags, you start conversation with NikitAI\n");
}

void InvalidFlags(void)
{
    printf("Invalid flags\n");
}

int AnalyzeFlags(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], HELP_FLAG) == 0)
        {
            ExplainProgram();
            return EXIT_SUCCESS;
        }

        InvalidFlags();
        return EXIT_FAILURE;
    }

    else if (argc == 3)
    {
        if (strcmp(argv[1], TEST_FLAG) == 0)
        {
            if (RunAllTests(argv[2]))
                return EXIT_SUCCESS;

            return EXIT_FAILURE;
        }

        InvalidFlags();
        return EXIT_FAILURE;
    }

    else
    {
        InvalidFlags();
        return EXIT_FAILURE;
    }
}










