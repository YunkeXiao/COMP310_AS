#include <stdlib.h>
#include <bits/types/FILE.h>
#include "PCB_DS.h"
#include "memorymanager.h"

struct PCB* makePCB(FILE *filePointer, int PID){
    /*
     * Initialize a new PCB
     *
     * @param start Start pointer in the RAM
     * @param end End pointer in the RAM
     * @return Initalized PCB
     */
    struct PCB *aPCB = malloc(sizeof(struct PCB));
    aPCB->PC = 0;
    aPCB->PC_page = 0;
    aPCB->PC_offset = 0;
    aPCB->pages_max = countTotalPages(filePointer);
    aPCB->PID = PID;
    for(int i = 0; i < 10; i++){
        aPCB->pageTable[i] = -1;
    }
    return aPCB;
}

//----------GETTERS----------
struct PCB* getNext(struct PCB *pcb){
    return pcb->next;
}

struct PCB* getPrev(struct PCB *pcb){
    return pcb->prev;
}

//----------SETTERS----------
void setNext(struct PCB* pcb, struct PCB* next){
    pcb->next = next;
}

void setPrev(struct PCB* pcb, struct PCB* prev){
    pcb->prev = prev;
}