#include <string.h>
#include <stdio.h>

int interpreter(char** words, int wordCount){
    if (wordCount == 0){
        return 0;
    }

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

    if (strcmp(words[0], "quit") == 0) {
        if (wordCount != 1){
            return 2;
        }
        return -1;
    }

    return 0;
}
