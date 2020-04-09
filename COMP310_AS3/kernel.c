#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "shell.h"
#include "constants.h"
#include "ram.h"
#include "pcb.h"
#include "PCB_DS.h"
#include "READY_QUEUE_DS.h"
#include "CPU_DS.h"
#include "cpu.h"
#include "ready_queue.h"

struct READY_QUEUE *rq;
struct CPU *cpu;
char *ram[RAM_MEM_SIZE];

int main() {
    // Initalize CPU
    cpu = createCPU(CPU_QUANTA);

    // Initalize ready queue
    rq = malloc(sizeof(struct READY_QUEUE));
    struct PCB *head = malloc(sizeof(struct PCB));
    struct PCB *tail = malloc(sizeof(struct PCB));
    setNext(head, tail);
    setPrev(head, NULL);
    setNext(tail, NULL);
    setPrev(tail, head);

    setHead(rq, head);
    setTail(rq, tail);

    // Run shell UI
    shellUI();
    return 0;
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

int myInit(char *filename) {
    /*
     * Take a script, put each command into ram, create a PCB for the script, and add it to the ready queue
     *
     * @param aPCB New PCB
     * @param rq Ready Queue
     * @errorCode
     */
    int errorCode = 0;
    int start, end;
    FILE *file = fopen(filename, "r");
    // If file doesn't exist, return errorCode 1
    if (!file){
        return 1;
    } else {
        errorCode = addToRAM(file, &start, &end);
        addToReady(makePCB(start, end));
        return errorCode;
    }
}

int scheduler() {
    /*
     * Simulate the ready queue until all programs have completed
     */
    struct PCB *head = getHead(rq);
    struct PCB *tail = getTail(rq);
    // The scheduler ends when the ready queue only consists of the head and the tail
    while (getNext(head) != tail) {
        // Dequeue the ready queue and run the script for the quanta
        struct PCB *current = removeHead();
        setIP(cpu, getPC(current));
        int errorCode = run(getQuanta(cpu), getEnd(current));

        // errorCode is 1 when the program exits prematurely, or ends
        if (errorCode == 1) {
            int start = getStart(current);
            int end = getEnd(current);
            for (int i = start; i <= end; i++) {
                ram[i] = NULL;
            }
            free(current);
        } else {
            setPC(current, getIP(cpu));
            addToReady(current);
        }
    }
    return 0;
}