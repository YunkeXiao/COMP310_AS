#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cpu.h"
#include "CPU_DS.h"
#include "shell.h"
#include "kernel.h"
#include "interpreter.h"

struct CPU *createCPU(int quanta){
    /*
     * Create new CPU
     * @param quanta size
     */
    struct CPU *new_cpu = malloc(sizeof(struct CPU));
    new_cpu->quanta = quanta;
    return new_cpu;
}

int run(int quanta, int end){
    for (int time = 0; time < quanta; time++){
        // If the IP goes over the end or the quit command is read, end this run
        char *buffer = strdup(ram[cpu->IP]);
        int index;
        for (index = 0; buffer[index] >= 33 && buffer[index] <= 126; index++){
        }
        buffer[index] = '\0';

        if (cpu->IP > end || strcmp(buffer, "quit") == 0) {
            printf("%squit\n", PROMPT);
            return 1;
        }
        // Update CUP's IR to contain the next command to run
        memset(cpu->IR, '\0', 999);
        strcpy(cpu->IR, ram[cpu->IP]);
        printf("%s%s", PROMPT, cpu->IR);
        int errorCode = processInput(cpu->IR);
        cpu->IP++;

        // Process errors
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
            return 1;
        }

        if (errorCode == 2){
            printf("----------ERROR 2: Wrong number of arguments----------\n\n");
            return 1;
        }

        if (errorCode == 3){
            printf("----------ERROR 3: Maximum number of variables reached----------\n\n");
            return 1;
        }

        if (errorCode == 4){
            printf("----------ERROR 4: Variable not found----------\n\n");
            return 1;
        }

        if (errorCode == 6){
            printf("----------ERROR 6: File not found----------\n\n");
            return 1;
        }
        if (errorCode == 7){
            printf("----------ERROR 7: Invalid command----------\n\n");
            return 1;
        }
        if (errorCode == 8){
            printf("----------ERROR 8: Too many files running at the same time. Check for infinite recursion----------\n\n");
            return 1;
        }
        if (errorCode == 11){
            printf("----------ERROR 11: Insufficient RAM to load script(s)----------\n\n");
            continue;
        }
    }
    return 0;
}

//----------GETTERS----------
void setIP(struct CPU *cpu, int ip){
    cpu->IP = ip;
}

//----------SETTERS----------
int getIP(struct CPU *cpu){
    return cpu->IP;
}

int getQuanta(struct CPU *cpu){
    return cpu->quanta;
}