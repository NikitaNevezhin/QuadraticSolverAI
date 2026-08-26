//#define NDEBUG
// #define MYNDEBUG

#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "UserInterface.h"
#include "TestRunner.h"
#include "SolverEngine.h"

#define MAX_MSG 100

void StartConversationAI(void);

void ShowOopsBeaver(void);

void EndConversationAI(void);

char* s_gets(char* st, int n);

void thinking(void);

int main(void)
{
    StartConversationAI();

    struct Equation equation_info =
    {
        {0.0, 0.0, 0.0},
        {0, 0.0, 0.0}
    };

    if (!RunAllTests())
        return 0;

    GreetUser();

    if (!GetAllCoeffs(&equation_info.coeffs))
    {
        ProgramFailed();
        EndConversationAI();
        return 0;
    }

    SolveQuadratic(&equation_info);

    thinking();
    ShowProgramResults(&equation_info.roots);

    EndConversationAI();

    return 0;
}

void StartConversationAI(void)
{
    char input[MAX_MSG] = {};

    printf("Hello! My name is NikitAI! I am your personal quadratic equation solver. Wanna start the program?\n");;

    while(strcmp(s_gets(input, MAX_MSG), "Yes") != 0)
    {
        printf("Sorry, I can't understand that. Enter 'Yes' if you wanna start the program\n");
    }

    printf("Great! Thinking...\n");
}

void thinking(void)
{
    printf("Thinking...\n");
}

void ShowOopsBeaver(void)
{
    const char* filename = "beaver.txt";

    char buffer[256];

    printf("\n");
    FILE *fp = fopen(filename, "r");
    if(fp)
    {
        while((fgets(buffer, 256, fp))!=NULL)
        {
            printf("%s", buffer);
        }

        fclose(fp);
    }
}

void EndConversationAI(void)
{
    ShowOopsBeaver();

    printf("\n\nOops! Looks like you've used your free attempt in NikitAI!\n"
           "To continue using NikitAI for free, subscribe to the channels:\n"
           "-> Nikita and tochka - brief, bite-sized news from the world of AI\n"
           "-> N&AI - latest research in AI field of CyberNikita ltd.\n"
           "-> CyberNikita Life - official CyberNikita's channel.\n"
           "With a subcription you recieve 100 free requests on NikitaGPT, NikSeek and picture generator Nano Nikita Pro.\n"
           "\nWant full functionality without ads?\n"
           "Press PREMIUM button right here!\n");
    printf("Buy NikitAI PREMIUM: ");
    while (getchar() != '\n')
        continue;

}

char* s_gets(char* st, int n)
{
    char* ret_val;
    char* newline;

    ret_val = fgets(st, n, stdin);

    if (ret_val)
    {
        newline = strchr(st, '\n');
        if (newline)
            *newline = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}







