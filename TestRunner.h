#ifndef TestRunner_h

#define TestRunner_h

bool         RunTest                  (struct Equation *test);

bool         RunAllTests              (void);

void         SkipLine                 (FILE *fp);

bool         GetOneEquation           (FILE *fp, struct Equation* equation_info);

#endif
