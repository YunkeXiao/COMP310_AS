#ifndef COMP310_AS2_PCB_H
#define COMP310_AS2_PCB_H

struct PCB{
    int PC;
    int start;
    int end;
    struct PCB *next;
    struct PCB *prev;
};

#endif //COMP310_AS2_PCB_H
