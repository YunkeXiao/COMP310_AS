#include "ready_queue.h"
#include "kernel.h"
#include "READY_QUEUE_DS.h"

//----------GETTERS----------

struct PCB* getHead(struct READY_QUEUE *rq){
    return rq->head;
}

struct PCB* getTail(struct READY_QUEUE *rq){
    return rq->tail;
}

//----------SETTERS----------
void setHead(struct READY_QUEUE *rq, struct PCB *head){
    rq->head = head;
}

void setTail(struct READY_QUEUE *rq, struct PCB *tail){
    rq->tail = tail;
}