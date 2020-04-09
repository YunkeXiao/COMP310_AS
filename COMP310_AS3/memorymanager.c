#include <bits/types/FILE.h>
#include <stdio.h>
#include "memorymanager.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>
#include <zconf.h>

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
    char buffer[BUFFER_SIZE];
    // Skip to correct page
    for(int i = 0; i < pageNumber * 4; i++){
        fgets(buffer, sizeof(buffer), filePointer);
    }
    for (int i = 0; i < 4; i++){
        fgets(buffer, sizeof(buffer), filePointer);
        printf("BUFFER: %s\n", buffer);
    }
    rewind(filePointer);
}