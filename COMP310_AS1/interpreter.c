#include <string.h>
#include <stdio.h>
#include "shellmemory.h"
#include "MEM.h"


int interpreter(char** words, int wordCount, struct MEM* shellMemory, int* memorySize){
    if (wordCount == 0){
        return 0;
    }

    // help command
    if (strcmp(words[0], "help") == 0){
        if (wordCount != 1) {
            return 2;
        }
        printf("help                             Displays all the commands\n");
        printf("quit                             Exits/terminates the shell with a farewell message\n");
        printf("set VAR STRING                   Assigns a value to shell memory\n");
        printf("print VAR                        Displays the STRING assigned to VAR\n");
        printf("run SCRIPT.TXT                   Executes the file SCRIPT.TXT\n");
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
        if (wordCount != 3) {
            return 2;
        }
        return setValue(words[1], words[2], shellMemory, memorySize);
    }

    //print command
    if (strcmp(words[0], "print") == 0) {
        if (wordCount != 2) {
            return 2;
        }
        return printValue(words[1], shellMemory, memorySize);
    }

    return 0;
}
