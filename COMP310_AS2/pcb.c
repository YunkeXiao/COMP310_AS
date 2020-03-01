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

//----------GETTERS----------
int getEnd(struct PCB *pcb){
    return pcb->end;
}

struct PCB* getNext(struct PCB *pcb){
    return pcb->next;
}

int getPC(struct PCB *pcb){
    return pcb->PC;
}

struct PCB* getPrev(struct PCB *pcb){
    return pcb->prev;
}

int getStart(struct PCB *pcb){
    return pcb->start;
}
//----------SETTERS----------
void setNext(struct PCB* pcb, struct PCB* next){
    pcb->next = next;
}

void setPC(struct PCB* pcb, int pc){
    pcb->PC = pc;
}


void setPrev(struct PCB* pcb, struct PCB* prev){
    pcb->prev = prev;
}