#ifndef COMP310_AS2_KERNEL_H
#define COMP310_AS2_KERNEL_H

#include "PCB.h"
#include "READY_QUEUE.h"

struct PCB* removeHead();
void addToReady(struct PCB *aPCB);
int myInit(char *filename);
int scheduler();

struct PCB* getHead(struct READY_QUEUE *rq);
struct PCB* getTail(struct READY_QUEUE *rq);

void setHead(struct READY_QUEUE *rq, struct PCB *head);
void setTail(struct READY_QUEUE *rq, struct PCB *tail);

extern struct CPU *cpu;
extern char *ram[];

#endif //COMP310_AS2_KERNEL_H
