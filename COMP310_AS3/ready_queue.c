#include <stdio.h>
#include "ready_queue.h"
#include "kernel.h"
#include "READY_QUEUE_DS.h"
#include "pcb.h"

struct PCB *removeHead() {
    /*
     * Pop the head of the ready queue
     *
     * @return rq Ready Queue
     */
    struct PCB *head = getHead(rq);
    struct PCB *headNext = getNext(head);
    struct PCB *replace = getNext(headNext);
    setNext(head, replace);
    setPrev(replace, head);
    return headNext;
}

void addToReady(struct PCB *aPCB) {
    /*
     * Add a PCB to the tail of the ready queue
     *
     * @param aPCB New PCB
     * @param rq Ready Queue
     */
    struct PCB *tail = getTail(rq);
    struct PCB *prevTail = getPrev(tail);
    setPrev(tail, aPCB);
    setNext(prevTail, aPCB);
    setNext(aPCB, tail);
    setPrev(aPCB, prevTail);

}
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