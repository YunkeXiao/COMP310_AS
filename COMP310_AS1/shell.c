#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "helper.h"
#include "MEM.h"

/*
 * Error Code Definitions
 *
 * Error 0: No error
 * Error 1: User input too large
 * Error 2: Wrong number of arguments
 * Error 3: Max variable count
 * Error 4: Variable not found
 */

#define MEM_SIZE 1000
#define BUFFER_SIZE 502

//int processInput(char* input);
int parseInput(char* input, char** words);

char prompt[100] = "$ \0";
char userInput[BUFFER_SIZE];
int errorCode;
struct MEM* shellMemory;
int memorySize = 0;

char shellMeta[100] = "Turtle Shell\nVersion 1.0 Created On 01/15/2020\n";
char welcomeMessage[5000] = "██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ██╗\n"
                            "██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ██║\n"
                            "██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗      ██║\n"
                            "██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝      ╚═╝\n"
                            "╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗    ██╗\n"
                            " ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝    ╚═╝\n";

char quitMessage[5000] = "███████╗███████╗███████╗    ██╗   ██╗ ██████╗ ██╗   ██╗    ███████╗ ██████╗  ██████╗ ███╗   ██╗██╗\n"
                         "██╔════╝██╔════╝██╔════╝    ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██╔════╝██╔═══██╗██╔═══██╗████╗  ██║██║\n"
                         "███████╗█████╗  █████╗       ╚████╔╝ ██║   ██║██║   ██║    ███████╗██║   ██║██║   ██║██╔██╗ ██║██║\n"
                         "╚════██║██╔══╝  ██╔══╝        ╚██╔╝  ██║   ██║██║   ██║    ╚════██║██║   ██║██║   ██║██║╚██╗██║╚═╝\n"
                         "███████║███████╗███████╗       ██║   ╚██████╔╝╚██████╔╝    ███████║╚██████╔╝╚██████╔╝██║ ╚████║██╗\n"
                         "╚══════╝╚══════╝╚══════╝       ╚═╝    ╚═════╝  ╚═════╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝\n";

int main(){
    // Initialize shellMemory;
    shellMemory = malloc(sizeof(struct MEM) * MEM_SIZE);
    for (int i = 0; i < MEM_SIZE; i++){
        struct MEM data = {.var = "", .value = ""};
        shellMemory[i] = data;
    }


    printf("%s", welcomeMessage);
    printf("%s", shellMeta);
    // Unless user closes the shell or errorCode is -1, the program runs infinitely
    while(1){
        errorCode = 0;
        printf("%s", prompt);
        fgets(userInput, BUFFER_SIZE, stdin);
        
        // Check for user input size
        if (inputTooLarge(userInput, BUFFER_SIZE)){
            errorCode = 1;
        }

        if (errorCode == 1){
            printf("ERROR 1: Input size is too large.\n");
            continue;
        }

        // Pass the parsed user input into the iterpreter
        char* words[100];
        int wordCount = parseInput(userInput, words);
        errorCode = interpreter(words, wordCount, shellMemory, &memorySize);

        if (errorCode == 2){
            printf("ERROR 2: Wrong number of arguments.\n");
            continue;
        }

        else if (errorCode == 3){
            printf("ERROR 3: Maximum number of variables reached.");
            continue;
        }

        else if (errorCode == 4){
            printf("ERROR 4: Variable not found.");
            continue;
        }

        else if (errorCode == -1 ){
            printf("%s", quitMessage);
            exit(99);
        }
    }
}

//int processInput(char* input){
//
//}



int parseInput(char* input, char** words){
    /*
     * {input} is parsed, with all unnecessary whitespace at the start of the string removed, and individual words
     * separated. Returns the number of words that were encountered during the parsing.
     *
     * @param: input The string that needs to be parsed
     * @param: words The string array that receives the parsed string
     */
    int wordCount = 0;
    int index;
    int tempIndex;
    char word[BUFFER_SIZE];

    for (index = 0; input[index] == ' ' && index < BUFFER_SIZE; index++);  // Get rid of white space

    while(input[index] != '\0' && index < BUFFER_SIZE){
        memset(word, '\0', BUFFER_SIZE);

        for (tempIndex = 0; input[index] != ' ' && input[index] != '\n' && input[index] != '\0'; tempIndex++){
            word[tempIndex] = (char)tolower(input[index]);
            index++;
        }

        // If we encounter a string of whitespace or newlines, we ignore them.
        if (tempIndex != 0){
            words[wordCount] = strdup(word);
            wordCount++;
        }
        index++;  // Index is currently on an invalid character, so we move it by one byte
    }
    return wordCount;
}

