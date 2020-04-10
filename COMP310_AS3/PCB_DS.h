#ifndef COMP310_AS2_PCB_H
#define COMP310_AS2_PCB_H

struct PCB{
    int PC; // Current instruction
    int PC_page; // Current page
    int PC_offset; // Frame offset
    int pages_max;
    int pageTable[10];
    int PID;
    struct PCB *next;
    struct PCB *prev;
};

#endif //COMP310_AS2_PCB_H
