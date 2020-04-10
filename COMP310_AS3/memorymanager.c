//#include <bits/types/FILE.h>
#include <stdio.h>
#include "memorymanager.h"
#include "constants.h"
#include "kernel.h"
#include <math.h>
#include <stdlib.h>
#include <zconf.h>
#include "ram.h"
#include "pcb.h"
#include <stdlib.h>

int launcher(FILE *filePointer){
    /*
     * Given a file, copy it into the backing store and load it into a PCB
     *
     * @param filePointer File pointer to the program
     * @return int errorcode
     */
    FILE *BSPointer;
    int PID;

    // Check for errors
    if (!filePointer){
        return -1;
    } else if (countTotalPages(filePointer) == 0){
        return -2;
    } else if (countTotalPages(filePointer) > PAGE_TABLE_SIZE){
        return -3;
    }

    // Check which file is to be created (p0.txt for the first program, p1.txt for the second, p3.txt for the third)
    if (access("BackingStore/p0.txt", F_OK) == -1){
        BSPointer = fopen("BackingStore/p0.txt", "w+");
        PID = 0;
    } else if (access("BackingStore/p1.txt", F_OK) == -1){
        BSPointer = fopen("BackingStore/p1.txt", "w+");
        PID = 1;
    } else {
        BSPointer = fopen("BackingStore/p2.txt", "w+");
        PID = 2;
    }

    // Copy code over
    char inp;
    while ( (inp = (char)fgetc(filePointer)) != EOF){
        fputc(inp, BSPointer);
    }
    // Clean pointers
    rewind(filePointer);
    rewind(BSPointer);

    struct PCB *aPCB = makePCB(BSPointer, PID);
    addToReady(aPCB);

    if(aPCB->pages_max == 1){
        addPagesToRAM(BSPointer, aPCB, 0, 1);
    } else {
        addPagesToRAM(BSPointer, aPCB, 0, 2);
    }
    fclose(BSPointer);
    return 1;
}

int addPagesToRAM(FILE* filePointer, struct PCB *aPCB, int pageNumber, int pageCount){
    /*
     * Add pages of a given PCB to RAM
     *
     * @param filePointer File pointer to the program
     * @param aPCB PCB in question
     * @param pageCount Number of pages to add
     * @return int Frame number
     */
    for(int i = 0; i < pageCount; i++){
        // Find frame to put the page in
        int isVictim = 0;
        int frame = findFrame();
        if (frame == -1){
            frame = findVictim(aPCB);
            isVictim = 1;
        }

        loadPage(pageNumber + i, filePointer, frame);
        updatePageTable(aPCB, pageNumber + i, frame, isVictim);
    }
}

int countTotalInstructions(FILE *filePointer) {
    /*
     * Count the number of instructions in the program
     *
     * @param filePointer File pointer to the program
     * @return int Number of instructions
     */
    // Invalid file pointer
    if (!filePointer) {
        return -1;
    }
    int lineCount = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), filePointer)) {
        lineCount++;
    }
    rewind(filePointer);
    return lineCount;
}

int countTotalPages(FILE *filePointer){
    /*
     * Count the number of Pages needed by the program
     *
     * @param filePointer File pointer to the program
     * @return int Number of pages
     */
    return (countTotalInstructions(filePointer) + RAM_FRAME_SIZE - 1)/RAM_FRAME_SIZE;
}

void loadPage(int pageNumber, FILE* filePointer, int frameNumber){
    /*
     * Loads a page (4 instructions) into RAM, specifically at the given frame
     *
     * @param pageNumber The page of the program
     * @param filePointer File pointer to the program
     * @param frameNumber Frame of RAM
     */
    char buffer[INSTRUCTION_BUFFER_SIZE];
    // Skip to correct page
    for(int i = 0; i < pageNumber * RAM_FRAME_SIZE; i++){
        fgets(buffer, sizeof(buffer), filePointer);
    }
    for (int i = 0; i < RAM_FRAME_SIZE; i++){
        if (!fgets(buffer, sizeof(buffer), filePointer)){
            break;
        } else {
            loadRAMFrame(buffer, frameNumber, i);
        }
    }
    rewind(filePointer);
}

int findFrame(){
    /*
     * Find the first frame in FIFO fashion that is free
     *
     * @return int Frame number
     */
    for(int i = 0; i < PAGE_TABLE_SIZE; i++){
        if (ram[(i * RAM_FRAME_SIZE)] == NULL){
            return i;
        }
    }
    return -1;
}

int findVictim(struct PCB *p){
    /*
     * Find random frame in RAM that can be replaced with new frame
     *
     * @param PCB whose code will replace the victim frame
     * @return int Frame number
     */
    int frame;
    int flag = 1;
    while(flag) {
        // Formula to get a random value between 0 and 9 inclusive
        flag = 0;
        frame = 0 + rand() / (RAND_MAX / (9 - 0 + 1) + 1);
        for(int i = 0; i < PAGE_TABLE_SIZE; i++){
            if (p->pageTable[i] == frame) {
                flag = 1;
                break;
            }
        }
        if (!flag){
            return frame;
        }
    }
}

int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame) {
    /*
     * Update the page table of the PCB in question. If a victim frame was used, then update victim PCB's page
     * table too
     *
     * @param PCB whose code will replace the victim frame
     * @return int Frame number
     */
    if (victimFrame) {
        // If we have a victim frame, then we have to find the PCB with the pageTable that points to the victim frame
        // and remove it from said pageTable before updating our current PCB's pageTable
        struct PCB *current = getHead(rq)->next;
        int found = 0;
        while (current != NULL || current != p) {
            for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
                if (current->pageTable[i] == frameNumber) {
                    current->pageTable[i] = -1;
                    p->pageTable[pageNumber] = frameNumber;
                    return 0;
                }
            }
            current = current->next;
        }
        return -1;
    } else {
        p->pageTable[pageNumber] = frameNumber;
        return 0;
    }
}