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
#include "CPU.h"
#include "cpu.h"

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

    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;

    rq->head = head;
    rq->tail = tail;

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
    struct PCB *prevTail = rq->tail->prev;
    rq->tail->prev = aPCB;
    aPCB->next = rq->tail;
    aPCB->prev = prevTail;
    prevTail->next = aPCB;
}

struct PCB *removeHead() {
    /*
     * Pop the head of the ready queue
     *
     * @return rq Ready Queue
     */
    struct PCB *head = rq->head;
    struct PCB *headNext = rq->head->next;
    struct PCB *replace = headNext->next;
    head->next = replace;
    replace->prev = head;
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
    while (rq->head->next != rq->tail) {
        struct PCB *current = removeHead();
        cpu->IP = current->PC;
        int errorCode = run(cpu->quanta, current->end);

        if (errorCode == 1) {
            int start = current->start;
            int end = current->end;
            for (int i = start; i <= end; i++) {
                ram[i] = NULL;
            }
            free(current);
        } else {
            current->PC = cpu->IP;
            addToReady(current);
        }
    }

    return 0;
}