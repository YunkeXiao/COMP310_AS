#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
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
 * ERROR 8: Too many running files
 * ERROR 9: EOF reached
 * ERROR 10: Duplicate script loaded
 * ERROR 11: Unable to create BackingStore files
 */

// Function declaration
int processInput(char* input);
int parseInput(char* input, char** words);
int runFile(char* fileName, char** running_files);

char userInput[BUFFER_SIZE];
int errorCode;
int memorySize = 0;

int shellUI(){
    // Initialize shellMemory;
    initializeShellMemory();

    printf("%s", WELCOME_MESSAGE);
    printf("%s", OPEN_MESSAGE);

    // Unless user closes the shell or errorCode is -1, the program runs infinitely
    while(1){
        // Reset errorCode for the next command and print user prompt
        errorCode = 0;
        printf("%s", PROMPT);

        if (fgets(userInput, BUFFER_SIZE, stdin) == NULL){
            printf("----------ERROR 9: EOF reached----------\n\n%s", QUIT_MESSAGE);
            FILE *tty = fopen("/dev/tty", "r");
            exit(99);
        }

        // If reading inputs from file, then format inputs to emulate terminal input
        if (!isatty(fileno(stdin))){
            int length = (int)strlen(userInput);
            if (userInput[length - 1] != '\n'){
                printf("%s\n", userInput);
            } else {
                printf("%s", userInput);
            }
        }

        errorCode = processInput(userInput);
        memset(userInput, '\0', BUFFER_SIZE);

        // Error code 5 isn't an error, in fact it's to tell the shell that a file needs to be run
        if (errorCode == 5){
            // running_files keeps track of open files. If too many testfiles are run, the 'run' command ends
            char* running_files[MAX_OPEN_FILE_COUNT];
            for (int i = 0; i < MAX_OPEN_FILE_COUNT; i++){
                running_files[i] = NULL;
            }

            errorCode = runFile(getFileName(), running_files);
        }

        if (errorCode == 1){
            printf("----------ERROR 1: Input size is too large----------\n\n");
            continue;
        }

        if (errorCode == 2){
            printf("----------ERROR 2: Wrong number of arguments----------\n\n");
            continue;
        }

        if (errorCode == 3){
            printf("----------ERROR 3: Maximum number of variables reached----------\n\n");
            continue;
        }

        if (errorCode == 4){
            printf("----------ERROR 4: Variable not found----------\n\n");
            continue;
        }

        if (errorCode == 6){
            printf("----------ERROR 6: File not found----------\n\n");
            continue;
        }
        if (errorCode == 7){
            printf("----------ERROR 7: Invalid command----------\n\n");
            continue;
        }
        if (errorCode == 8){
            printf("----------ERROR 8: Too many files running at the same time. Check for infinite recursion----------\n\n");
            continue;
        }
        if (errorCode == 11){
            printf("----------ERROR 11: Unable to create BackingStore files----------\n\n");
            continue;
        }
        if (errorCode == -1 ){
            printf("\n%s", QUIT_MESSAGE);
            exit(99);
        }
    }
}

int runFile(char* fileName, char** running_files){
    /*
     * Given a filename, read line by line and try to process them like you would a user input
     * @param: fileName String of the filename
     * @return: int Error code
     */
    FILE* fp;
    int error;
    int too_many_files = 1;

    // Check if there is too many running files
    for(int i = 0; i < MAX_OPEN_FILE_COUNT; i++){
        if (running_files[i] == NULL){
            too_many_files = 0;
        }
    }
    if (too_many_files){
        return 8;
    }

    if ((fp = fopen(fileName,"r"))){
        char buffer[BUFFER_SIZE];

        printf("\n----------RUNNING %s----------\n", fileName);

        while((fgets(buffer, BUFFER_SIZE, fp)) != NULL){
            // Add file to running file list
            for (int i = 0; i < MAX_OPEN_FILE_COUNT; i++){
                if (running_files[i] == NULL){
                    running_files[i] = fileName;
                    break;
                }
            }

            // It's expected that every line ends with a newline. Format buffer to ensure that the last line also
            // follows this rule
            formatBuffer(buffer);

            printf("%s%s",PROMPT, buffer);
            error = processInput(buffer);

            // If there's another run command in the test file, process that file
            if (error == 5){
                error = runFile(getFileName(), running_files);
            }

            // If a quit command if encountered in a run command, then stop reading instructions
            if (error == -1){
                break;
            }

            // Once and error is encountered, stop running the text file and return the error
            if (error != 0){
                return error;
            }
            // Reset buffer, otherwise new inputs may get corrupted
            memset(buffer, '\0', BUFFER_SIZE);
        }

        // Upon a successful 'run' command, we remove the current file from the running files list, and return error
        // code 0.
        for (int i = 0; i < MAX_OPEN_FILE_COUNT; i++){
            if (running_files[i] == fileName){
                running_files[i] = NULL;
            }
        }

        printf("----------CLOSING %s----------\n\n", fileName);
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
    int index, tempIndex, seenSpace = 0;
    char word[BUFFER_SIZE];


    for (index = 0; input[index] == ' ' && index < BUFFER_SIZE; index++);  // Get rid of white space

    while(input[index] != '\0' && index < BUFFER_SIZE){
        memset(word, '\0', BUFFER_SIZE);

        // Check that character is alphanumerical
        for (tempIndex = 0; input[index] >= 33 && input[index] <= 126; tempIndex++){
            // If the first word, i.e. the command type, then ignore case
            if (!seenSpace) {
                word[tempIndex] = (char) tolower(input[index]);
            } else{
                word[tempIndex] = input[index];
            }
            index++;
        }

        // If we encounter a string of whitespace or newlines, we ignore them.
        if (tempIndex != 0){
            words[wordCount] = strdup(word);
            seenSpace = 1;
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
    if (strlen(input) > BUFFER_SIZE){
        return 1;
    }
    // Pass the parsed user input into the interpreter
    char* words[100];
    memset(words, '\0', 100);
    int wordCount = parseInput(input, words);
    return interpreter(words, wordCount, &memorySize);
}