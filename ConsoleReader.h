#ifndef ConsoleReader_h

#define ConsoleReader_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EquationStructure.h"
#include "TestRunner.h"
#include "SolverEngine.h"
#include "ImitatorOfAI.h"
#include "UserInterface.h"

#define HELP_FLAG       "-h"
#define TEST_FLAG       "-t"
#define READ_FLAG       "-r"
#define WRITE_FLAG      "-w"
#define READ_WRITE_FLAG "-rw"

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void ExplainProgram  (void);
void InvalidFlags    (void);
int  ProcessFlags    (int argc, char *argv[]);
bool ReadCoeffs      (const char* filename, struct Equation* equation_info);
bool WriteRoots      (const char* filename, struct Equation* equation_info);

#endif
