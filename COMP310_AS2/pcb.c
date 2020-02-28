#include <stdlib.h>
#include "PCB.h"

struct PCB* makePCB(int start, int end){
    /*
     * Initialize a new PCB
     *
     * @param start Start pointer in the RAM
     * @param end End pointer in the RAM
     * @return Initalized PCB
     */
    struct PCB *aPCB = malloc(sizeof(struct PCB));
    aPCB->start = start;
    aPCB->end = end;
    aPCB->PC = start;
    return aPCB;
}