#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "EquationStructure.h"
#include "MyAssert.h"

#define POLYNOMIAL_DEGREE 2 // for quadratic equation
#define SIZE 100

void GreetUser(void)
{
    printf("This AIprogram solves quadratic equation in the following format: "
           "ax^2 + bx + c = 0\nPlease, enter the coeffs:\n");
}

void ProgramFailed(void)
{
    printf("AIProgram failed\n");
}

void ShowProgramResults(struct RootsInfo *result_roots)
{
    MyAssert(result_roots, ProgramFailed);

    switch (result_roots->total_roots)
    {
        case ZERO:
            printf("There are no real solutions\n");
            break;

        case ONE:
            printf("There is a single solution: %lf\n", result_roots->x1);
            break;

        case TWO:
            printf("There are two solutions: %lf and %lf\n", result_roots->x1, result_roots->x2);
            break;

        case INFINITE_NUMBER:
            printf("There is an infinite number of solutions\n");
            break;

        default:
            printf("Some error occured in function SolveQuadratic :( \n");
            break;
    }
}

bool DotProcessing(char input[], int *i, bool *seen_dot, int curr_ch) // returns true if dot was processed successfully, false if failed
{
    if (*seen_dot)
    {
        return false;
    }
    input[*i] = (char)curr_ch;
    (*i)++;
    *seen_dot = true;
    return true;
}

bool MinusProcessing(char input[], int *i, int curr_ch)   // returns true if minus was processed successfully, false if failed
{
    if (*i != 0)
    {
        return false;
    }

    input[*i] = (char)curr_ch;
    (*i)++;
    return true;
}

bool IsSymbolTaken(char input[], int *i, bool *seen_dot, int curr_ch)  // returns true if symbol was taken, false if failed
{
    if (isdigit(curr_ch) || curr_ch == '.' || curr_ch == '-')
    {
        if (isdigit(curr_ch))
        {
            input[*i] = (char)curr_ch;
            (*i)++;
            return true;
        }

        else if (curr_ch == '.')
            return DotProcessing(input, i, seen_dot, curr_ch);

        else
            return MinusProcessing(input, i, curr_ch);
    }

    return false;
}

bool IsEmpty(char input[])
{
    return input[0] == '\0';
}


bool EndsWithDot(char input[])
{
    int length = strlen(input);

    if (IsEmpty(input)) return false;

    return input[length - 1] == '.';
}

int GetCoeff(double *coeff, int symb) // returns 1 if succeeded, 0 if failed
{
    char input[SIZE] = {};
    int curr_ch = 0;
    int i = 0;
    bool seen_dot = false;

    printf("Coeff %c: ", symb);

    while ( (curr_ch = getchar()) != '\n')
    {
        if (IsSymbolTaken(input, &i, &seen_dot, curr_ch))
            continue;

        else
        {
            printf("Invalid input\n");
            return 0;
        }
    }

    input[i] = '\0';

    if (IsEmpty(input) || EndsWithDot(input))
    {
        printf("Invalid input\n");
        return 0;
    }

    *coeff = atof(input);

    return 1;
}

int GetAllCoeffs(struct Coefficients *input_coeffs)    // returns 1 if succeeded, 0 if failed
{
    MyAssert(input_coeffs, ProgramFailed);

    int i = 0;
    double coeffs[POLYNOMIAL_DEGREE + 1] = {};  // POLYNOMIAL_DEGREE + 1 = amount of members of polynomial
    int coeff_letter = 'a';

    for (; i <= POLYNOMIAL_DEGREE; i++)
    {
        if (!GetCoeff(&coeffs[i], coeff_letter + i))
            return 0;
    }

    input_coeffs->a = coeffs[0];
    input_coeffs->b = coeffs[1];
    input_coeffs->c = coeffs[2];

    return 1;
}
