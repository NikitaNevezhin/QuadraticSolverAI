#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


#include "TestRunner.h"
#include "UserInterface.h"
#include "EquationStructure.h"
#include "MyAssert.h"
#include "SolverEngine.h"
#include "FloatTools.h"

#define SAMPLES_AMOUNT 10
#define LINE_SIZE 256
#define VALUE_SIZE 20

void SkipLine(FILE *fp)
{
    char buffer[LINE_SIZE] = {};
    fgets(buffer, LINE_SIZE, fp);
}

bool GetOneEquation(FILE *fp, struct Equation* equation_info)
{
    char x1[VALUE_SIZE] = {};
    char x2[VALUE_SIZE] = {};

    if (fscanf(fp, "%lg %lg %lg %d %s %s", &equation_info->coeffs.a, &equation_info->coeffs.b, &equation_info->coeffs.c, &equation_info->roots.total_roots, x1, x2) != 6)
        return false;

    if (strcmp(x1, "NAN") == 0)
        equation_info->roots.x1 = NAN;

    else
        equation_info->roots.x1 = atof(x1);

    if (strcmp(x1, "NAN") == 0)
        equation_info->roots.x2 = NAN;

    else {
        equation_info->roots.x2 = atof(x2);
    }

    return true;
}


bool RunTest(struct Equation *sample)
{
    MyAssert(sample, ProgramFailed);

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
    struct Equation equation_info = {};

    const char* filename = "TESTS.txt";

    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        printf("No such file as %s. Program failed\n", filename);
        return false;
    }

    SkipLine(fp);
    while (GetOneEquation(fp, &equation_info))
    {
        if (!RunTest(&equation_info))
        {
            printf("Program failed pre-launch tests. Cannot execute this program\n");
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    printf("Pre-launch tests completed successfully\n");
    return true;
}
