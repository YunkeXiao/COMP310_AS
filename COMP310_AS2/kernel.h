#ifndef COMP310_AS2_KERNEL_H
#define COMP310_AS2_KERNEL_H

#include "PCB.h"
#include "READY_QUEUE.h"

struct PCB* removeHead();
void addToReady(struct PCB *aPCB);
int myInit(char *filename);
int scheduler();

extern struct CPU *cpu;
extern char *ram[];

#endif //COMP310_AS2_KERNEL_H
