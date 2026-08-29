#include "ConsoleReader.h"

void ExplainProgram(void)
{
    printf("This program solves quadratic equation.\n\n"
           "User gives three arguments as input and gets the existing roots.\n"
           "If roots doesn't exist, user gets \"There are no real roots\" message\n"
           "If there are infinite number of roots, user gets \"There is an infinite number of solutions\" message\n\n"
           "FLAGS:\n"
           "\"-h\"                         - gives the general info about the program\n"
           "\"-t SOMEFILE\"                - takes info from SOMEFILE and tests program on its info in case it is possible\n"
           "\"-r INPUT_FILE\"              - takes info from INPUT_FILE and, in case it is valid, shows user the result in the console\n"
           "\"-w OUTPUT_FILE\"             - takes info from the user in console and writes the result into OUTPUT_FILE\n"
           "\"-rw INPUT_FILE OUTPUT_FILE\" - takes info from INPUT_FILE and, in case it is valid, writes the result into OUTPUT_FILE\n\n"
           "If there are no flags, you start conversation with NikitAI\n");
}

void InvalidFlags(void)
{
    printf("Invalid flags\n");
}


bool ReadCoeffs(const char* filename, struct Equation* equation_info)   // returns true if succeded, false if failed
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf(RED "No such file as %s. Program failed\n" RESET, filename);
        return false;
    }

    SkipLine(file);

    if (fscanf(file, "%lg %lg %lg", &equation_info->coeffs.a,
                                    &equation_info->coeffs.b,
                                    &equation_info->coeffs.c) != 3)
    {
        printf(RED "Invalid data in file %s. Couldn't read from it\n" RESET, filename);
        return false;
    }

    return true;
}


bool WriteRoots(const char* filename, struct Equation* equation_info)
{
    FILE *file = fopen(filename, "w");

    if (!file)
    {
        printf(RED "No such file as %s. Program failed\n" RESET, filename);
        return false;
    }

    fprintf(file, "total roots: %d\n", equation_info->roots.total_roots);
    fprintf(file, "x1 = %lg\n", equation_info->roots.x1);
    fprintf(file, "x2 = %lg\n", equation_info->roots.x2);

    return true;
}


int ProcessFlags(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], HELP_FLAG) == 0)
        {
            ExplainProgram();
            return EXIT_SUCCESS;
        }

        InvalidFlags();
        return EXIT_FAILURE;
    }

    else if (argc == 3)
    {
        if (strcmp(argv[1], TEST_FLAG) == 0)
        {
            if (RunAllTests(argv[2]))
                return EXIT_SUCCESS;

            return EXIT_FAILURE;
        }

        else if (strcmp(argv[1], READ_FLAG) == 0)
        {
            struct Equation equation_info = {};
            const char* filename = argv[2];

            if (!ReadCoeffs(filename, &equation_info))
                return EXIT_FAILURE;

            SolveQuadratic(&equation_info);

            Thinking();

            ShowProgramResults(&equation_info.roots);

            EndConversationAI();

            return EXIT_SUCCESS;
        }

        else if (strcmp(argv[1], WRITE_FLAG) == 0)
        {
            StartConversationAI();

            struct Equation equation_info = {};
            const char* filename = argv[2];

            GreetUser();

            if (!GetAllCoeffs(&equation_info.coeffs))
            {
                ProgramFailed();
                EndConversationAI();
                return EXIT_FAILURE;
            }

            SolveQuadratic(&equation_info);

            Thinking();

            if (WriteRoots(filename, &equation_info))
            {
                EndConversationAI();
                return EXIT_SUCCESS;
            }

            return EXIT_FAILURE;
        }

        InvalidFlags();
        return EXIT_FAILURE;
    }

    else if (argc == 4)
    {
        if (strcmp(argv[1], READ_WRITE_FLAG) == 0)
        {
            struct Equation equation_info = {};

            const char* input_file = argv[2];
            const char* output_file = argv[3];

            if (!ReadCoeffs(input_file, &equation_info))
                return EXIT_FAILURE;

            SolveQuadratic(&equation_info);

            if (!WriteRoots(output_file, &equation_info))
                return EXIT_FAILURE;

            EndConversationAI();

            return EXIT_SUCCESS;
        }
        printf("couldnt read flag\n");
        InvalidFlags();
        return EXIT_FAILURE;
    }

    else
    {
        printf("Too much flags\n");
        InvalidFlags();
        return EXIT_FAILURE;
    }
}
