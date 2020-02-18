#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "helper.h"
#include "MEM.h"
#include "constants.h"

/*
 * Error Code Definitions
 *
 * Error 0: No error
 * Error 1: User input too large
 * Error 2: Wrong number of arguments
 * Error 3: Max variable count
 * Error 4: Variable not found
 * Error 5: run command
 * Error 6: File not found
 * Error 7: Invalid command
 */

// Function declaration
int processInput(char* input);
int parseInput(char* input, char** words);
int runFile(char* fileName);

char userInput[BUFFER_SIZE];
int errorCode;
int memorySize = 0;

int main(){
    // Initialize shellMemory;
    initializeShellMemory();

    printf("%s", WELCOME_MESSAGE);
    printf("%s", OPEN_MESSAGE);
    // Unless user closes the shell or errorCode is -1, the program runs infinitely
    while(1){
        errorCode = 0;
        printf("%s", PROMPT);
        fgets(userInput, BUFFER_SIZE, stdin);
        errorCode = processInput(userInput);

        // Error code 5 isn't an error, in fact it's to tell the shell that a file needs to be run
        if (errorCode == 5){
            errorCode = runFile(getFileName());
        }

        if (errorCode == 1){
            printf("ERROR 1: Input size is too large.\n");
            continue;
        }

        if (errorCode == 2){
            printf("ERROR 2: Wrong number of arguments.\n");
            continue;
        }

        if (errorCode == 3){
            printf("ERROR 3: Maximum number of variables reached.\n");
            continue;
        }

        if (errorCode == 4){
            printf("ERROR 4: Variable not found.\n");
            continue;
        }

        if (errorCode == 6){
            printf("ERROR 6: File not found.\n");
            continue;
        }
        if (errorCode == 7){
            printf("ERROR 7: Invalid command.\n");
            continue;
        }
        if (errorCode == -1 ){
            printf("\n%s", QUIT_MESSAGE);
            exit(99);
        }
    }
}

int runFile(char* fileName){
    /*
     * Given a filename, read line by line and try to process them like you would a user input
     * @param: fileName String of the filename
     * @return: int Error code
     */
    FILE* fp;
    int error;
    if ((fp = fopen(fileName,"r"))){
        char buffer[BUFFER_SIZE];
        while((fgets(buffer, BUFFER_SIZE, fp)) != NULL){
            printf("%s%s",PROMPT, buffer);
            error = processInput(buffer);
            // Once and error is encountered, stop running the text file and return the error
            if (error != 0){
                return error;
            }
            // Reset buffer, otherwise new inputs may get corrupted
            memset(buffer, '\0', BUFFER_SIZE);
        }
        return 0;
    } else {
        return 6;
    }
}

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

int processInput(char* input){
    /*
     * Takes a string input and tries to run shell commands based on it
     *
     * @param: input String input
     * @return: int Error code
     */

    // Check for user input size
    if (inputTooLarge(input, BUFFER_SIZE)){
        return 1;
    }
    // Pass the parsed user input into the iterpreter
    char* words[100];
    int wordCount = parseInput(input, words);
    return interpreter(words, wordCount, &memorySize);
    return 0;
}