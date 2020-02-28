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

struct READY_QUEUE *rq;

int main(){
    // Initalize ready queue
    rq = malloc(sizeof(struct READY_QUEUE));
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

int myInit(char *filename){
    /*
     * Take a script, put each command into ram, create a PCB for the script, and add it to the ready queue
     *
     * @param aPCB New PCB
     * @param rq Ready Queue
     */
    int errorCode = 0;
    int start, end;
    FILE *file = fopen(filename, "r");
    errorCode = addToRAM(file, &start, &end);
    addToReady(makePCB(start, end), rq);
    return 0;
}

int scheduler(){

}