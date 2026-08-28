#include <stdio.h>
#include <string.h>

#include "UserInterface.h"
#include "ImitatorOfAI.h"

#define MAX_MSG 100

#define LINE_SIZE 256


void StartConversationAI(void)
{
    char input[MAX_MSG] = {};

    printf("Hello! My name is NikitAI! I am your personal quadratic equation solver. Wanna start the program?\n");;

    while(strcmp(ReadLine(input, MAX_MSG), "Yes") != 0)
    {
        printf("Sorry, I can't understand that. Enter 'Yes' if you wanna start the program\n");
    }

    printf("Great! Thinking...\n");
}

void Thinking(void) //
{
    printf("Thinking...\n");
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
