#ifndef COMP310_AS2_PCB1_H
#define COMP310_AS2_PCB1_H

#include "PCB_DS.h"

struct PCB* makePCB(int start, int end);

int getEnd(struct PCB *pcb);
struct PCB* getNext(struct PCB *pcb);
struct PCB* getPrev(struct PCB *pcb);
int getPC(struct PCB *pcb);
int getStart(struct PCB *pcb);
void setNext(struct PCB *pcb, struct PCB *next);
void setPrev(struct PCB *pcb, struct PCB *prev);
void setPC(struct PCB *pcb, int pc);

#endif //COMP310_AS2_PCB_H
