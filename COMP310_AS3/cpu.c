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

int run(int quanta, struct PCB * current){

    for (int time = 0; time < quanta; time++){
        // Set cpu offset, and update offset in PCB
        cpu->offset = current->PC_offset;
        int a = cpu->IP;
        int b = cpu->offset;

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

        // Add the new line at th end of the last instruction
        if (current->PC + 1 == current->end){
            printf("\n");
        }

        int errorCode = processInput(cpu->IR);

        // Update PC_offset and PC
        current->PC_offset++;
        current->PC = (current->PC_page * RAM_FRAME_SIZE) + current->PC_offset;

        if (current->PC >= current->end) {
            return 1;
        }

        // If offset = 4, we have to use a new page
        if (current->PC_offset == RAM_FRAME_SIZE){
            current->PC_offset = 0;
            current->PC_page++;
            // If page is greater, then it means we have finished running the program
            if (current->PC_page >= current->pages_max){
                return 1;
            }

            // Otherwise we want to check if the next page is loaded. If it is, continue, otherwise find victim frame
            if (current->pageTable[current->PC_page] != -1){
                return 0;
            }

            FILE *filePointer;
            switch (current->PID){
                case 0:
                    filePointer = fopen("BackingStore/p0.txt", "r+");
                    break;
                case 1:
                    filePointer = fopen("BackingStore/p1.txt", "r+");
                    break;
                case 2:
                    filePointer = fopen("BackingStore/p2.txt", "r+");
                    break;
            }
            addPagesToRAM(filePointer, current, current->PC_page, 1);
            fclose(filePointer);
            return 0;
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
