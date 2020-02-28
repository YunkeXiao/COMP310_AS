#ifndef COMP310_AS2_CPU1_H
#define COMP310_AS2_CPU1_H

#include "constants.h"

struct CPU{
    int IP;
    char IR[INSTRUCTION_BUFFER_SIZE];
    int quanta;
};

#endif //COMP310_AS2_CPU_H
