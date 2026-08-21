#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define ACCURACY 10e-6
#define POLYNOMIAL_DEGREE 2 // for quadratic equation
#define SIZE 100

enum ROOTS
{
    INFINITE_NUMBER = -1,
    ZERO = 0,
    ONE = 1,
    TWO = 2
};

int    LinearSolver             (double b, double c, double *x);

int    QuadraticSolver          (double a, double b, double c, double *x1, double *x2);

bool   FloatEqual               (double x, double y);

double CalcDiscriminant         (double a, double b, double c);

void   QuadraticSolverResults   (int total_roots, double x1, double x2);

int    GetCoeff                 (double *coeff, int symb);

int    GetCoeffs                (double *a, double *b, double *c);

bool   IsMore                   (double x1, double x2);


int main(void)
{
    double a = 0.0, b = 0.0, c = 0.0;
    double x1 = 0.0, x2 = 0.0;
    int total_roots = 0;

    printf("This program solves quadratic equation in the following format: ");
    printf("ax^2 + bx + c = 0\n");

    if (!GetCoeffs(&a, &b, &c))
    {
        printf("Program failed\n");
        return 0;
    }

    total_roots = QuadraticSolver(a, b, c, &x1, &x2);

    QuadraticSolverResults(total_roots, x1, x2);

    return 0;
}

int LinearSolver(double b, double c, double *x)
{
    if (FloatEqual(b, 0.0))
    {
        if (FloatEqual(c, 0.0))
            return INFINITE_NUMBER; // infinite number of solutions
        else
            return ZERO; // no solutions
    }

    else if (FloatEqual(c, 0.0) )
    {
        *x = 0.0;
        return ONE;
    }

    *x = -(c / b);
    return ONE; // one solution
}


int QuadraticSolver(double a, double b, double c, double *x1, double *x2)
{
    double disc = 0.0;

    if (FloatEqual(a, 0.0))
    {
        return LinearSolver(b, c, x1);
    }

    disc = CalcDiscriminant(a, b, c);

    if (disc < 0) return ZERO;

    else
    {
        *x1 = (-b - sqrt(disc)) / (2 * a);
        *x2 = (-b + sqrt(disc)) / (2 * a);

        if (FloatEqual(disc, 0.0))
            return ONE;

        else
            return TWO;
    }
}


bool FloatEqual(double x, double y)
{
    return fabs(x - y) < ACCURACY;
}


bool IsMore(double x1, double x2)
{
    return (x1 - x2) > ACCURACY;
}


double CalcDiscriminant(double a, double b, double c)
{
    return pow(b, 2) - 4 * a * c;
}


void QuadraticSolverResults(int total_roots, double x1, double x2)
{
    switch (total_roots)
    {
        case ZERO:
            printf("There are no real solutions\n");
            break;

        case ONE:
            printf("There is a single solution: %lf\n", x1);
            break;

        case TWO:
            printf("There are two solutions: %lf and %lf\n", x1, x2);
            break;

        case INFINITE_NUMBER:
            printf("There is an infinite number of solutions\n");
            break;

        default:
            printf("Some error occured in function QuadraticSolver :( \n");
            break;
    }
}


int GetCoeffs(double *a, double *b, double *c)    // returns 1 if succeeded, 0 if failed
{
    int i = 0;
    double *coeffs[POLYNOMIAL_DEGREE + 1] = {a, b, c};  // POLYNOMIAL_DEGREE + 1 = amount of members of polynomial
    int coeff_letter = 'a';

    for (; i <= POLYNOMIAL_DEGREE; i++)
    {
        if (!GetCoeff(coeffs[i], coeff_letter + i))
            return 0;
    }

    return 1;
}

int GetCoeff(double *coeff, int symb) // returns 1 if succeeded, 0 if failed
{
    char input[SIZE] = {0};
    int curr_ch = 0;
    int i = 0;
    bool seen_dot = false;

    printf("Coeff %c: ", symb);

    while ( (curr_ch = getchar()) != '\n')
    {
        if (isdigit(curr_ch))
        {
            input[i] = (char)curr_ch;
            i++;
        }

        else if (!seen_dot && curr_ch == '.')
        {
            input[i] = (char)curr_ch;
            i++;
            seen_dot = true;
        }

        else if (curr_ch == '-')
        {
            if (i == 0)
            {
                input[i] = (char)curr_ch;
                i++;
            }

            else
            {
                printf("Invalid input\n");
                return 0;
            }
        }

        else
        {

            printf("Invalid input\n");
            return 0;
        }
    }

    if (i == 0)
    {
        printf("Invalid input\n");
        return 0;
    }

    if (input[i - 1] == '.')
    {
        printf("Invalid input\n");
        return 0;
    }

    input[i] = '\0';

    *coeff = atof(input);

    return 1;
}



