#ifndef COMP310_AS2_PCB_H
#define COMP310_AS2_PCB_H

struct PCB{
    int PC;
    int PC_page;
    int PC_offset;
    int pages_max;
    int pageTable[10];
    int PID;
    struct PCB *next;
    struct PCB *prev;
};

#endif //COMP310_AS2_PCB_H
