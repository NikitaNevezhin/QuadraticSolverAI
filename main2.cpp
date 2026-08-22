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


void   GreetUser                (void);

void   ProgramFailed            (void);

void   LinearSolver             (struct Coefficients *input_coeffs, struct RootsInfo *result_roots);

void   QuadraticSolver          (struct Coefficients *input_coeffs, struct RootsInfo *result_roots);

bool   FloatEqual               (const double x, const double y);

double CalcDiscriminant         (struct Coefficients *input_coeffs);

void   QuadraticSolverResults   (struct RootsInfo *result_roots);

int    GetCoeff                 (double *coeff, int symb);

bool   DotProcessing            (char input[], int *i, bool *seen_dot, int curr_ch);

bool   MinusProcessing          (char input[], int *i, int curr_ch);

bool   IsSymbolTaken            (char input[], int *i, bool *seen_dot, int curr_ch);

bool   IsEmpty                  (char input[]);

bool   EndsWithDot              (char input[]);

int    GetAllCoeffs             (struct Coefficients *input_coeffs);

bool   IsMore                   (const double x1, const double x2);

bool   RunTest                  (struct Equation *test);

bool   RunAllTests              (void);



int main(void)
{
    struct Coefficients input_coeffs = {0.0, 0.0, 0.0};
    struct RootsInfo result_roots = {0, 0.0, 0.0};

    if (!RunAllTests())
        return 0;

    GreetUser();

    if (!GetAllCoeffs(&input_coeffs))
    {
        ProgramFailed();
        return 0;
    }

    QuadraticSolver(&input_coeffs, &result_roots);

    QuadraticSolverResults(&result_roots);

    return 0;
}


void GreetUser(void)
{
    printf("This program solves quadratic equation in the following format: ");
    printf("ax^2 + bx + c = 0\n");
}

void ProgramFailed(void)
{
    printf("Program failed\n");
}



void LinearSolver(struct Coefficients *input_coeffs, struct RootsInfo *result_roots)
{
    if (FloatEqual(input_coeffs->b, 0.0))
    {
        if (FloatEqual(input_coeffs->c, 0.0))
        {
            result_roots->total_roots = INFINITE_NUMBER;
            return;
        }
        else
        {
            result_roots->total_roots = ZERO;
            return;
        }
    }

    else if (FloatEqual(input_coeffs->c, 0.0) )
    {
        result_roots->x1 = 0.0;
        result_roots->total_roots = ONE;
        return;
    }

    result_roots->x1 = -(input_coeffs->c / input_coeffs->b);
    result_roots->total_roots = ONE;
    return;
}


void QuadraticSolver(struct Coefficients *input_coeffs, struct RootsInfo *result_roots)
{
    double disc = 0.0, sq_disc = 0.0;

    if (FloatEqual(input_coeffs->a, 0.0))
    {
        LinearSolver(input_coeffs, result_roots);
        return;
    }

    disc = CalcDiscriminant(input_coeffs);

    if (disc < 0)
        result_roots->total_roots = ZERO;

    else
    {
        sq_disc = sqrt(disc);

        result_roots->x1 = (-input_coeffs->b - sq_disc) / (2 * input_coeffs->a);
        result_roots->x2 = (-input_coeffs->b + sq_disc) / (2 * input_coeffs->a);

        if (FloatEqual(disc, 0.0))
            result_roots->total_roots = ONE;

        else
            result_roots->total_roots = TWO;
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


double CalcDiscriminant(struct Coefficients *input_coeffs)
{
    return pow(input_coeffs->b, 2) - 4 * input_coeffs->a * input_coeffs->c;
}


void QuadraticSolverResults(struct RootsInfo *result_roots)
{
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
            printf("Some error occured in function QuadraticSolver :( \n");
            break;
    }
}


int GetAllCoeffs(struct Coefficients *input_coeffs)    // returns 1 if succeeded, 0 if failed
{
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
    struct RootsInfo result_roots = {0, 0.0, 0.0};

    QuadraticSolver(&(sample->coeffs), &result_roots);

    if (result_roots.total_roots != sample->roots.total_roots)
        return false;

    if (result_roots.total_roots == ZERO || result_roots.total_roots == INFINITE_NUMBER)
        return true;

    else if (result_roots.total_roots == ONE)
        return FloatEqual(result_roots.x1, sample->roots.x1);

    else
        return FloatEqual(result_roots.x1, sample->roots.x1) && FloatEqual(result_roots.x2, sample->roots.x2);
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


