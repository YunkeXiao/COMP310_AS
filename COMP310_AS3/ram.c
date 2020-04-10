#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "kernel.h"
#include "memorymanager.h"

void loadRAMFrame(char* instruction, int frameNumber, int offset){
    /*
     * Load a page into the RAM
     *
     * @param instruction Instruction string
     * @param frameNumber The RAM frame
     * @param offset Where in the frame the instruction should be loaded
     */
    ram[frameNumber * 4 + offset] = strdup(instruction);
}

void initializeRAM(){
    /*
     * Set all RAM instructions to NULL
     */
    for (int i = 0; i < RAM_MEM_SIZE; i++){
        ram[i] = NULL;
    }
}