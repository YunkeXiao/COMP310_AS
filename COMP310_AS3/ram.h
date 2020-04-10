#ifndef COMP310_AS2_RAM_H
#define COMP310_AS2_RAM_H

int addToRAM(FILE *p, int *start, int *end);
void loadRAMFrame(char* command, int frameNumber, int offset);
void initializeRAM();

#endif //COMP310_AS2_RAM_H
