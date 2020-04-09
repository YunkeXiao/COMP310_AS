#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "kernel.h"

int addToRAM(FILE *p, int *start, int *end){
    /*
     * Add script to RAM by assigning each command to a RAM cell
     *
     * @param p Script file pointer
     * @param start Start address in the ram
     * @param end End address in the ram
     */
    char command[INSTRUCTION_BUFFER_SIZE];
    int currentPtr = 0;

    // Get first available RAM cell
    while(ram[currentPtr] != NULL){
        currentPtr++;
    }

    // If memory overflows, then stop operation
    if (currentPtr >= RAM_MEM_SIZE){
        return 2;
    }
    // Set start variable
    *start = currentPtr;

    // Commands in the ram
    while(fgets(command, INSTRUCTION_BUFFER_SIZE, p)){
        ram[currentPtr] = strdup(command);
        currentPtr++;
    }

    // Set end variable
    *end = --currentPtr;

    return 0;
}

void initializeRAM(){
    for (int i = 0; i < RAM_MEM_SIZE; i++){
        ram[i] = NULL;
    }
}