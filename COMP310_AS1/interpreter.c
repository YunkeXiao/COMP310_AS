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
        printf("\nhelp                             Displays all the commands\n");
        printf("quit                             Exits/terminates the shell with a farewell message\n");
        printf("set VAR STRING                   Assigns a value to shell memory\n");
        printf("print VAR                        Displays the STRING assigned to VAR\n");
        printf("run SCRIPT.TXT                   Executes the file SCRIPT.TXT\n\n");
        return 0;
    }

    if (strcmp(words[0], "quit") == 0) {
        if (wordCount != 1){
            return 2;
        }
        return -1;  // Error code -1 signals the shell to quit
    }

    if (strcmp(words[0], "set") == 0) {
        if (wordCount != 3) {
            return 2;
        }


    }
    return 0;
}
