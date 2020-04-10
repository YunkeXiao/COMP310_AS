#ifndef COMP310_AS2_READY_QUEUE1_H
#define COMP310_AS2_READY_QUEUE1_H

#include "READY_QUEUE_DS.h"
#include <stdlib.h>


struct PCB *removeHead();
struct PCB* getHead(struct READY_QUEUE *rq);
void addToReady(struct PCB *aPCB);
void removeFromReady(struct PCB *aPCB);
struct PCB* getTail(struct READY_QUEUE *rq);
void setHead(struct READY_QUEUE *rq, struct PCB *head);
void setTail(struct READY_QUEUE *rq, struct PCB *tail);

#endif //COMP310_AS2_READY_QUEUE_H
