#ifndef TestRunner_h

#define TestRunner_h

bool         RunTest                  (struct Equation *test, int test_number);

bool         RunAllTests              (const char* filename);

void         SkipLine                 (FILE *fp);

bool         GetOneEquation           (FILE *fp, struct Equation* equation_info);

#endif
