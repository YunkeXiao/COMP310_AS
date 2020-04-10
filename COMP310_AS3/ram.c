#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "kernel.h"

int addToRAM(FILE *p, int *start, int *end){
    /*
     * Add script to RAM by assigning each instruction to a RAM cell
     *
     * @param p Script file pointer
     * @param start Start address in the ram
     * @param end End address in the ram
     */
    char instruction[INSTRUCTION_BUFFER_SIZE];
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

    // instructions in the ram
    while(fgets(instruction, INSTRUCTION_BUFFER_SIZE, p)){
        ram[currentPtr] = strdup(instruction);
        currentPtr++;
    }

    // Set end variable
    *end = --currentPtr;

    return 0;
}

void loadRAMFrame(char* instruction, int frameNumber, int offset){
    /*
     * Load a page into the RAM
     *
     * @param instruction Instruction string
     * @param frameNumber The RAM frame
     * @param offset Where in the frame the instruction should be loaded
     */
    char* input = strdup(instruction);
    ram[frameNumber * 4 + offset] = input;
}

void initializeRAM(){
    /*
     * Set all RAM instructions to NULL
     */
    for (int i = 0; i < RAM_MEM_SIZE; i++){
        ram[i] = NULL;
    }
}