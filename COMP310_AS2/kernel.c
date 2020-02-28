#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "shell.h"
#include "constants.h"
#include "ram.h"
#include "pcb.h"
#include "PCB.h"
#include "READY_QUEUE.h"


int main(){
    // Initalize ready queue
    struct READY_QUEUE *rq = malloc(sizeof(struct READY_QUEUE));
    struct PCB *head = malloc(sizeof(struct PCB));
    struct PCB *tail = malloc(sizeof(struct PCB));

    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;

    rq->head = head;
    rq->tail = tail;

    struct PCB *a = malloc(sizeof(struct PCB));
    struct PCB *b = malloc(sizeof(struct PCB));

    a = makePCB(0, 10);
    a->PC = 0;

    b = makePCB(10,20);
    b->PC = 10;

    addToReady(a,rq);
    addToReady(b,rq);

//    shellUI();
}


void addToReady(struct PCB *aPCB, struct READY_QUEUE *rq){
    /*
     * Add a PCB to the tail of the ready queue
     *
     * @param aPCB New PCB
     * @param rq Ready Queue
     */
    struct PCB *prevTail = rq->tail->prev;
    rq->tail->prev = aPCB;
    aPCB->next = rq->tail;
    aPCB->prev = prevTail;
    prevTail->next = aPCB;
}

