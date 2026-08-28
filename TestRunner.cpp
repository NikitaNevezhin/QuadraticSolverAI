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

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

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

    if (strcmp(x2, "NAN") == 0)
        equation_info->roots.x2 = NAN;

    else {
        equation_info->roots.x2 = atof(x2);
    }

    return true;
}


bool RunTest(struct Equation *sample, int test_number)
{
    MyAssert(sample, ProgramFailed);

    struct Equation result_info = {sample->coeffs, {0, 0.0, 0.0}};

    SolveQuadratic(&result_info);

    if (result_info.roots.total_roots != sample->roots.total_roots)
    {
        printf(RED "#test %d failed:\n" RESET, test_number);
        printf(RED "Expected %d roots, got %d roots\n" RESET, sample->roots.total_roots, result_info.roots.total_roots);
        return false;
    }

    if (result_info.roots.total_roots == ZERO || result_info.roots.total_roots == INFINITE_NUMBER)
        return true;

    else if (result_info.roots.total_roots == ONE)
    {
        if (FloatEqual(result_info.roots.x1, sample->roots.x1))
            return true;
        else
        {
            printf(RED "#test %d failed:\n" RESET, test_number);
            printf(RED "Expected x1 = %lg\n" RESET, sample->roots.x1);
            printf(RED "Got x1 = %lg\n" RESET, result_info.roots.x1);
            return false;
        }

    }
    else
    {
        if (FloatEqual(result_info.roots.x1, sample->roots.x1) && FloatEqual(result_info.roots.x2, sample->roots.x2))
            return true;
        else
        {
            printf(RED "#test %d failed:\n" RESET, test_number);
            printf(RED "Expected x1 = %lg; x2 = %lg\n" RESET, sample->roots.x1, sample->roots.x2);
            printf(RED "Got x1 = %lg; x2 = %lg\n" RESET, result_info.roots.x1, result_info.roots.x2);
            return false;
        }

    }
}

bool RunAllTests()
{
    int test_counter = 0;

    struct Equation equation_info = {};

    const char* filename = "TESTS.txt";

    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        printf(RED "No such file as %s. Program failed\n" RESET, filename);
        return false;
    }

    SkipLine(fp);
    while (GetOneEquation(fp, &equation_info))
    {
        test_counter++;

        if (!RunTest(&equation_info, test_counter))
        {
            printf(RED "Program failed pre-launch tests. Cannot execute this program\n" RESET);
            fclose(fp);
            return false;
        }
    }

    if (fgetc(fp) != EOF)
    {
        fclose(fp);
        printf(RED "#File reading error:\n" RESET);
        printf(RED "Invalid value on line %d of %s\n" RESET, test_counter + 1, filename); // error line equals to test_counter + 1 as first line is title
        return false;
    }

    fclose(fp);
    printf(GREEN "%d/%d " RESET, test_counter, test_counter);
    printf(GREEN "pre-launch tests completed successfully\n" RESET);
    return true;
}
