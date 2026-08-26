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
