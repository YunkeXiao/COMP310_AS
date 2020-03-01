#include <string.h>
#include <stdio.h>
#include "shellmemory.h"
#include "MEM.h"
#include "constants.h"
#include "kernel.h"
#include "ram.h"

char* fileName;

int interpreter(char** words, int wordCount, int* memorySize){
    /*
     * Given the parsed shell input, check which command is being called, if any, and apply its effects.
     * @param: words Parsed input
     * @param: wordCount Used to check for correctness in argument count
     * @param: shellMemory Needed for setting and printing variables
     * @param: memorySize Optimizes search algorithm
     */
    if (wordCount == 0){
        return 0;
    }

    // help command
    if (strcmp(words[0], "help") == 0){
        if (wordCount != 1) {
            return 2;
        }
        printf("%s", LINE);
        printf("help                             Displays all the commands\n");
        printf("quit                             Exits/terminates the shell with a farewell message\n");
        printf("set VAR STRING                   Assigns a value to shell memory\n");
        printf("print VAR                        Displays the STRING assigned to VAR\n");
        printf("run SCRIPT.TXT                   Executes the file SCRIPT.TXT\n");
        printf("%s", LINE);

        return 0;
    }

    // quit command
    if (strcmp(words[0], "quit") == 0) {
        if (wordCount != 1){
            return 2;
        }
        return -1;  // Error code -1 signals the shell to quit
    }

    // set command
    if (strcmp(words[0], "set") == 0) {
        if (wordCount < 3){
            return 2;
        }
        char value[BUFFER_SIZE];
        for (int i = 2; i < wordCount; i++){
            strcat(value, words[i]);
            if (i != wordCount - 1){
                strcat(value, " ");
            }
        }
        return setValue(words[1], value, memorySize);
    }

    // print command
    if (strcmp(words[0], "print") == 0) {
        if (wordCount != 2) {
            return 2;
        }
        return printValue(words[1], memorySize);
    }

    // run command
    if (strcmp(words[0], "run") == 0) {
        if (wordCount != 2) {
            return 2;
        }
        fileName = words[1];
        return 5;
    }

    if (strcmp(words[0],"exec") == 0){
        if (wordCount > 4 || wordCount < 1){
            return 2;
        }
        // Check if same script has been loaded multiple times
        char *programs[3];
        programs[0] = words[1];
        for (int i = 2; i < wordCount; i++){
            for (int j = 0; j < i - 1; j++){
                if (strcmp(words[i], programs[j]) == 0){
                    printf("----------ERROR 10: Script %s already loaded----------\n\n", words[i]);
                    words[i] = NULL;
                }
            }
        }
        // Initalize RAM to empty
        for (int i = 0; i < RAM_MEM_SIZE; i++){
            ram[i] = NULL;
        }
        // Initalize ready queue and PCBs
        for (int i = 1; i < wordCount; i++){
            // If duplicated script, ignore
            if (!words[i]){
                continue;
            }
            int errorCode = myInit(words[i]);
            switch (errorCode){
                case 1:
                    return 6;
                case 2:
                    return 11;
                default:
                    continue;
            }
        }
        // Run programs
        scheduler();
        return 0;
    }
    return 7;
}

char* getFileName(){
    /*
     * Filename getter. This is needed, since our function for running shell commands is in shell.c
     * return: char* String for the filename
     */
    return fileName;
}
