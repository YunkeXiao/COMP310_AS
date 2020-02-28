#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"

char *ram[RAM_MEM_SIZE];

int addToRAM(FILE *p, int *start, int *end){
    char command[INSTRUCTION_BUFFER_SIZE];
    int currentPtr = 0;

    // Get first available RAM cell
    while(ram[currentPtr]){
        currentPtr++;
    }

    // If memory overflows, then stop operation
    if (currentPtr >= RAM_MEM_SIZE){
        return 1;
    }
    // Set start variable
    *start = currentPtr;

    // Commands in the ram
    while(fgets(command, INSTRUCTION_BUFFER_SIZE, p)){
        ram[currentPtr] = strdup(command);
        currentPtr++;
    }

//     Set end variable
    *end = --currentPtr;

    for (int i = 0; i <= 2; i++){
        printf("Command: %s", ram[i]);
    }

    return 0;

}