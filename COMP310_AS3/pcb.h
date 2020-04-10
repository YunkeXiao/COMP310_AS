#ifndef COMP310_AS2_PCB1_H
#define COMP310_AS2_PCB1_H

#include "PCB_DS.h"
#include <bits/types/FILE.h>

struct PCB* makePCB(FILE *filePointer, int PID);
struct PCB* getNext(struct PCB *pcb);
struct PCB* getPrev(struct PCB *pcb);
void setNext(struct PCB *pcb, struct PCB *next);
void setPrev(struct PCB *pcb, struct PCB *prev);

#endif //COMP310_AS2_PCB_H
