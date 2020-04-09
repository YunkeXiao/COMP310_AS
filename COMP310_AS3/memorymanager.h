#ifndef COMP310_AS2_MEMORYMANAGER_H
#define COMP310_AS2_MEMORYMANAGER_H

int launcher(FILE *filePointer);
int countTotalPages(FILE *filePointer);
void loadPage(int pageNumber, FILE* filePointer, int frameNumber);

#endif //COMP310_AS2_MEMORYMANAGER_H
