#ifndef COMP310_AS2_CPU1_H
#define COMP310_AS2_CPU1_H

#include "PCB_DS.h"

struct CPU* createCPU(int quanta);
int run(int quanta, int end);

void setIP(struct CPU *cpu, int ip);
int getIP(struct CPU *cpu);
int getQuanta(struct CPU *cpu);

#endif //COMP310_AS2_CPU_H
