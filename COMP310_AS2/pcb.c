#include <stdlib.h>
#include "PCB.h"

struct PCB* makePCB(int start, int end){
    struct PCB *aPCB = malloc(sizeof(struct PCB));
    aPCB->start = start;
    aPCB->end = end;
    aPCB->PC = start;
    return aPCB;
}