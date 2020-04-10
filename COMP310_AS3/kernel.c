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
#include "memorymanager.h"

struct READY_QUEUE *rq;
struct CPU *cpu;
char *ram[RAM_MEM_SIZE];

int main(){
    int error = 0;
    boot();
    error = kernel();
    return error;
}

void boot(){
    /*
     * Reset RAM to NULLs, and clean the BackingStore folder
     */
    initializeRAM();
    system("mkdir -p BackingStore");
    system("rm -rf BackingStore/*");
}

int kernel() {
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

int myInit(char *filename) {
    /*
     * Take a script, put each command into ram, create a PCB for the script, and add it to the ready queue
     *
     * @param aPCB New PCB
     * @param rq Ready Queue
     * @errorCode 1: File doesn't exist
     */
    int errorCode = 0;
    FILE *file = fopen(filename, "r");
    // If file doesn't exist, return errorCode 1
    if (!file){
        return 6;
    } else {
        // Check if program can be loaded
        errorCode = launcher(file);
        switch(errorCode){
            case -1:
                errorCode = 6;
                break;
            case -2:
                errorCode = 12;
                break;
            case -3:
                errorCode = 13;
                break;
            default:
                errorCode = 0;
        }
        fclose(file);
        return errorCode;
    }
}

int scheduler() {
//    /*
//     * Simulate the ready queue until all programs have completed
//     */
    struct PCB *head = getHead(rq);
    struct PCB *tail = getTail(rq);
    // The scheduler ends when the ready queue only consists of the head and the tail
    while (getNext(head) != tail) {
        // Dequeue the ready queue and run the script for the quanta
        struct PCB *current = removeHead();

        cpu->IP = current->pageTable[current->PC_page] * RAM_FRAME_SIZE;
        char *c[40];
        for (int i = 0; i < 40; i++){
            c[i] = ram[i];
        }

        int errorCode = run(cpu->quanta, current);

        // errorCode is 1 when the program exits prematurely, or ends
        if (errorCode == 1) {
            for(int i = 0 ; i < PAGE_TABLE_SIZE; i++){
                for (int j = 0; j < RAM_FRAME_SIZE; j++) {
                    if (current->pageTable[i] != -1) {
                        int a = current->pageTable[i]*4 + j;
                        ram[(current->pageTable[i])*RAM_FRAME_SIZE + j] = NULL;
                    }
                }
            }
            char * command;
            switch (current->PID){
                case 0:
                    command = "BackingStore/p0.txt";
                    break;
                case 1:
                    command = "BackingStore/p1.txt";
                    break;
                case 2:
                    command = "BackingStore/p2.txt";
                    break;
                default:
                    return -1;
            }
            system(command);
            free(current);
        } else {
            addToReady(current);
        }
    }
    return 0;
}