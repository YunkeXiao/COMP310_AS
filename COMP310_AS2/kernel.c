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


//    shellUI();
}


void addToReady(struct PCB *aPCB, struct READY_QUEUE *rq){

    struct PCB *prevTail = rq->tail->next;
    rq->tail->next = aPCB;
    aPCB->prev = rq->tail;
    aPCB->next = prevTail;
    prevTail->prev = aPCB;
}

