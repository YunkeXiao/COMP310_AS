#ifndef COMP310_AS2_PCB_H
#define COMP310_AS2_PCB_H

#include "constants.h"

struct PCB{
    int PC; // Current instruction
    int PC_page; // Current page
    int PC_offset; // Frame offset
    int pages_max;
    int pageTable[PAGE_TABLE_SIZE];
    int PID;
    int end;
    struct PCB *next;
    struct PCB *prev;
};

#endif //COMP310_AS2_PCB_H
