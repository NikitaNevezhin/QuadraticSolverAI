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
#include "ColorPrint.h"

#define HELP_FLAG        "-h"
#define TEST_FLAG        "-t"
#define READ_FLAG        "-r"
#define WRITE_FLAG       "-w"
#define READ_WRITE_FLAG  "-rw"

#define LONG_HELP_FLAG   "--help"
#define LONG_TEST_FLAG   "--test"
#define LONG_READ_FLAG   "--read"
#define LONG_WRITE_FLAG  "--write"

void ExplainProgram  (void);

void InvalidFlags    (void);

int  ProcessFlags    (int argc, char *argv[]);

int  ProcessHelp     (char* argv[]);

int  ProcessTest     (char* argv[]);

int  ProcessRead     (char *argv[]);

int  ProcessWrite    (char *argv[]);

bool ReadCoeffs      (const char* filename, struct Equation* equation_info);

bool WriteRoots      (const char* filename, struct Equation* equation_info);

#endif
