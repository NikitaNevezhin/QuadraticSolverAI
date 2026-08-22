#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define ACCURACY 10e-6
#define POLYNOMIAL_DEGREE 2 // for quadratic equation
#define SIZE 100
#define SAMPLES_AMOUNT 10


enum Roots
{
    INFINITE_NUMBER = -1,
    ZERO = 0,
    ONE = 1,
    TWO = 2
};

struct Coefficients
{
    double a;
    double b;
    double c;
};

struct RootsInfo
{
    int total_roots;
    double x1;
    double x2;
};

struct Equation
{
    struct Coefficients coeffs;
    struct RootsInfo roots;
};


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


int    LinearSolver             (const double b, const double c, double *x);

int    QuadraticSolver          (const double a, const double b, const double c, double *x1, double *x2);

bool   FloatEqual               (const double x, const double y);

double CalcDiscriminant         (const double a, const double b, const double c);

void   QuadraticSolverResults   (const int total_roots, const double x1, const double x2);

int    GetCoeff                 (double *coeff, int symb);

bool   DotProcessing            (char input[], int *i, bool *seen_dot, int curr_ch);

bool   MinusProcessing          (char input[], int *i, int curr_ch);

bool   IsSymbolTaken            (char input[], int *i, bool *seen_dot, int curr_ch);

bool   IsEmpty                  (char input[]);

bool   EndsWithDot              (char input[]);

int    GetAllCoeffs             (double *a, double *b, double *c);

bool   IsMore                   (const double x1, const double x2);

bool   RunTest                  (struct Equation *test);

bool   RunAllTests              (struct Equation *samples, int samples_amount);



int main(void)
{
    double a = 0.0, b = 0.0, c = 0.0;
    double x1 = 0.0, x2 = 0.0;
    int total_roots = 0;

    if (!RunAllTests(program_samples, SAMPLES_AMOUNT))
        return 0;


    printf("This program solves quadratic equation in the following format: ");
    printf("ax^2 + bx + c = 0\n");

    if (!GetAllCoeffs(&a, &b, &c))
    {
        printf("Program failed\n");
        return 0;
    }

    total_roots = QuadraticSolver(a, b, c, &x1, &x2);

    QuadraticSolverResults(total_roots, x1, x2);

    return 0;
}

int LinearSolver(const double b, const double c, double *x)
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


int QuadraticSolver(const double a, const double b, const double c, double *x1, double *x2)
{
    double disc = 0.0, sq_disc = 0.0;

    if (FloatEqual(a, 0.0))
    {
        return LinearSolver(b, c, x1);
    }

    disc = CalcDiscriminant(a, b, c);

    if (disc < 0) return ZERO;

    else
    {
        sq_disc = sqrt(disc);
        *x1 = (-b - sq_disc) / (2 * a);
        *x2 = (-b + sq_disc) / (2 * a);

        if (FloatEqual(disc, 0.0))
            return ONE;

        else
            return TWO;
    }
}


bool FloatEqual(const double x, const double y)
{
    return fabs(x - y) < ACCURACY;
}


bool IsMore(const double x1, const double x2)
{
    return (x1 - x2) > ACCURACY;
}


double CalcDiscriminant(const double a, const double b, const double c)
{
    return pow(b, 2) - 4 * a * c;
}


void QuadraticSolverResults(const int total_roots, const double x1, const double x2)
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


int GetAllCoeffs(double *a, double *b, double *c)    // returns 1 if succeeded, 0 if failed
{
    int i = 0;
    double* coeffs[POLYNOMIAL_DEGREE + 1] = {a, b, c};  // POLYNOMIAL_DEGREE + 1 = amount of members of polynomial
    int coeff_letter = 'a';

    for (; i <= POLYNOMIAL_DEGREE; i++)
    {
        if (!GetCoeff(coeffs[i], coeff_letter + i))
            return 0;
    }

    return 1;
}

bool DotProcessing(char input[], int *i, bool *seen_dot, int curr_ch) // returns true if dot was processed successfully, false if failed
{
    if (*seen_dot)
    {
        // printf("I was here when i = %d\n", *i);
        return false;
    }
    // printf("I was here when i = %d\n", *i);
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


bool RunTest(struct Equation *sample)
{
    double check_x1 = 0.0, check_x2 = 0.0;
    int total_roots = 0;

    total_roots = QuadraticSolver(sample->coeffs.a, sample->coeffs.b, sample->coeffs.c, &check_x1, &check_x2);

    if (total_roots != sample->roots.total_roots)
        return false;

    if (total_roots == ZERO || total_roots == INFINITE_NUMBER)
        return true;

    else if (total_roots == ONE)
        return FloatEqual(check_x1, sample->roots.x1);

    else
        return FloatEqual(check_x1, sample->roots.x1) && FloatEqual(check_x2, sample->roots.x2);
}

bool RunAllTests(struct Equation *samples, int samples_amount)
{
    for (int i = 0; i < samples_amount; i++)
    {
        if (!RunTest(&samples[i]))
        {
            printf("Program failed pre-launch tests. Cannot execute this program\n");
            return false;
        }
    }

    printf("Pre-launch tests completed successfully\n");
    return true;
}


