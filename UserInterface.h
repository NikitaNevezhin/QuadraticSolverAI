void         GreetUser                (void);

void         ProgramFailed            (void);

void         ShowProgramResults       (struct RootsInfo *result_roots);

int          GetCoeff                 (double *coeff, int symb);

bool         DotProcessing            (char input[], int *i, bool *seen_dot, int curr_ch);

bool         MinusProcessing          (char input[], int *i, int curr_ch);

bool         IsSymbolTaken            (char input[], int *i, bool *seen_dot, int curr_ch);

bool         IsEmpty                  (char input[]);

bool         EndsWithDot              (char input[]);

int          GetAllCoeffs             (struct Coefficients *input_coeffs);
