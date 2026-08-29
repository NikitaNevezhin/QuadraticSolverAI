#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "UserInterface.h"
#include "ImitatorOfAI.h"
#include "ColorPrint.h"

#define MAX_MSG 100

#define LINE_SIZE 256


bool NoRegCmp(const char s1[], const char s2[])
{
    int length1 = strlen(s1);
    int length2 = strlen(s2);

    if (length1 != length2)
        return false;

    for (int i = 0; i < length1; i++)
    {
        if (tolower(s1[i]) != tolower(s2[i]))
            return false;
    }

    return true;
}


void StartConversationAI(void)
{
    char input[MAX_MSG] = {};

    printf(LIGHT_BLUE "Hello! My name is NikitAI! I am your personal quadratic equation solver. Wanna start the program?\n" RESET);

    while(!NoRegCmp(ReadLine(input, MAX_MSG), "Yes"))
    {
        printf(LIGHT_BLUE "Sorry, I can't understand that. Enter 'Yes' if you wanna start the program\n" RESET);
    }

    printf(LIGHT_BLUE "Great! Thinking...\n" RESET);
}

void Thinking(void)
{
    printf(LIGHT_BLUE "Thinking...\n" RESET);
}

void ShowOopsBeaver(void)
{
    const char* filename = "beaver.txt";

    char buffer[LINE_SIZE] = {};

    printf("\n");

    FILE *fp = fopen(filename, "r");

    if(fp)
    {
        while((fgets(buffer, LINE_SIZE, fp))!=NULL)
        {
            printf(YELLOW "%s" RESET, buffer);
        }

        fclose(fp);
    }
}

void EndConversationAI(void)
{
    ShowOopsBeaver();

    printf(LIGHT_BLUE "\n\nOops! Looks like you've used your free attempt in NikitAI!\n"
                      "To continue using NikitAI for free, subscribe to the channels:\n"
                      "-> Nikita and tochka - brief, bite-sized news from the world of AI\n"
                      "-> N&AI - latest research in AI field of CyberNikita ltd.\n"
                      "-> CyberNikita Life - official CyberNikita's channel.\n"
                      "With a subcription you recieve 100 free requests on NikitaGPT, NikSeek and picture generator Nano Nikita Pro.\n"
                      "\nWant full functionality without ads?\n"
                      "Press PREMIUM button right here!\n" RESET);
    printf(LIGHT_BLUE "Buy NikitAI PREMIUM: " RESET);

    while (getchar() != '\n')
        continue;

}
