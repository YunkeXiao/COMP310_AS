#ifndef COMP310_AS2_KERNEL_H
#define COMP310_AS2_KERNEL_H

#include "PCB_DS.h"
#include "READY_QUEUE_DS.h"

void boot();
int kernel();
struct PCB* removeHead();
void addToReady(struct PCB *aPCB);
int myInit(char *filename);
int scheduler();

struct PCB* getHead(struct READY_QUEUE *rq);
struct PCB* getTail(struct READY_QUEUE *rq);

void setHead(struct READY_QUEUE *rq, struct PCB *head);
void setTail(struct READY_QUEUE *rq, struct PCB *tail);

extern struct READY_QUEUE *rq;
extern struct CPU *cpu;
extern char *ram[];

#endif //COMP310_AS2_KERNEL_H
