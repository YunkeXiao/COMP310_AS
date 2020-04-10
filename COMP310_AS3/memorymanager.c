#include <bits/types/FILE.h>
#include <stdio.h>
#include "memorymanager.h"
#include "constants.h"
#include "kernel.h"
#include <math.h>
#include <stdlib.h>
#include <zconf.h>
#include "ram.h"

int launcher(FILE *filePointer){
    FILE *BSPointer;
    if (!filePointer){
        return -1;
    }
    // Check which file is to be created (p0.txt for the first program, p1.txt for the second, p3.txt for the third)
    if (access("BackingStore/p0.txt", F_OK) == -1){
        BSPointer = fopen("BackingStore/p0.txt", "w");
    } else if (access("BackingStore/p1.txt", F_OK) == -1){
        BSPointer = fopen("BackingStore/p1.txt", "w");
    } else {
        BSPointer = fopen("BackingStore/p2.txt", "w");
    }

    char inp;
    while ( (inp = (char)fgetc(filePointer)) != EOF){
        fputc(inp, BSPointer);
    }
    // Clean pointers
    rewind(filePointer);
    fclose(BSPointer);
    return 1;
}

int countTotalPages(FILE *filePointer){
    /*
     * Count the number of Pages needed by the program
     *
     * @param filePointer File pointer to the program
     * @return int Number of pages
     */
    // Invalid file pointer
    if (!filePointer){
        return -1;
    }
    int lineCount = 0;
    char buffer[BUFFER_SIZE];
    while(fgets(buffer,sizeof(buffer), filePointer)){
        lineCount++;
    }
    rewind(filePointer);
    return (lineCount + 3)/4;
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
    for(int i = 0; i < pageNumber * 4; i++){
        fgets(buffer, sizeof(buffer), filePointer);
    }
    for (int i = 0; i < 4; i++){
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
    for(int i = 0; i < 10; i++){
        if (ram[i * 4] == NULL){
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
    while(1) {
        // Formula to get a random value between 0 and 9 inclusive
        frame = 0 + rand() / (RAND_MAX / (9 - 0 + 1) + 1);
        if (frame != p->PC_page){
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
        while (current != getTail(rq)) {
            for (int i = 0; i < 10; i++) {
                if (current->pageTable[i] == frameNumber) {
                    current->pageTable[i] = -1;
                    current = getTail(rq);
                    found = 1;
                } else {
                    current = current->next;
                }
            }
        }
        if(!found){
            return -1;
        }
    }
    p->pageTable[pageNumber] = frameNumber;
    return 0;
}