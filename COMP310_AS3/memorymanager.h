#ifndef COMP310_AS2_MEMORYMANAGER_H
#define COMP310_AS2_MEMORYMANAGER_H

#include "PCB_DS.h"

int launcher(FILE *filePointer);
int countTotalPages(FILE *filePointer);
void loadPage(int pageNumber, FILE* filePointer, int frameNumber);
int findFrame();
int findVictim(struct PCB *p);
int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame);

#endif //COMP310_AS2_MEMORYMANAGER_H
