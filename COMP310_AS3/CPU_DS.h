#ifndef COMP310_AS2_CPU_H
#define COMP310_AS2_CPU_H

#include "constants.h"

struct CPU{
    int IP;
    int offset;
    char IR[INSTRUCTION_BUFFER_SIZE];
    int quanta;
};

#endif //COMP310_AS2_CPU_H
