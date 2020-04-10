#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cpu.h"
#include "CPU_DS.h"
#include "shell.h"
#include "kernel.h"
#include "interpreter.h"
#include "memorymanager.h"

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
    /*
     * Takes a quanta and runs the CPU
     *
     * @param quanta size
     * @return int Error code
     */
    for (int time = 0; time < quanta; time++){
        //TODO: DEBUG
        struct CPU *cpucpu = cpu;
        char *ramram[500];
        for (int i = 0; i < 40; i++){ramram[i] = ram[i];}
        //END DEBUG
        // Get the instruction type. If it's a quit instruction, quit immediately
        char *buffer = strdup(ram[cpu->IP + cpu->offset]);
        int index;
        for (index = 0; buffer[index] >= 33 && buffer[index] <= 126; index++){
        }
        buffer[index] = '\0';

        if (strcmp(buffer, "quit") == 0) {
            printf("%squit\n", PROMPT);
            return 1;
        }
        // Update CPU's IR to contain the next command to run
        memset(cpu->IR, '\0', 999);
        strcpy(cpu->IR, ram[cpu->IP + cpu->offset]);
        printf("%s%s", PROMPT, cpu->IR);

        // Add the new line at the end of the last instruction
        if (cpu->IP + cpu->offset + 1 == end){
            printf("\n");
        }

        // Run instruction
        int errorCode = processInput(cpu->IR);
        cpu->offset++;

        //TODO: DEBUG
        cpucpu = cpu;
        for (int i = 0; i < 40; i++){ramram[i] = ram[i];}
        //END DEBUG


        // If we have reached the last instruction, before completing the frame (odd frame number)
        if (ram[cpu->IP + cpu->offset] == NULL && cpu->offset%2 == 1) {
            return 1;
        }

        // If offset = 4, we have to use a new page
        if (cpu->offset == RAM_FRAME_SIZE){
            return 2;
        }

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
        if (errorCode == 12){
            printf("----------ERROR 12: Empty program----------\n\n");
            continue;
        }
        if (errorCode == 13){
            printf("----------ERROR 13: Program too large. A maximum of 40 instructions per program is allowed----------\n\n");
            continue;
        }
    }
    return 0;
}

//----------GETTERS----------
void setIP(struct CPU *cpu, int ip){
    cpu->IP = ip;
}
