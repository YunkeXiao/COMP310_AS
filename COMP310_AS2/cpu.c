#include <stdlib.h>
#include "cpu.h"
#include "CPU.h"

struct CPU* createCPU(int quanta){
    struct CPU *cpu = malloc(sizeof(struct CPU));
    cpu->quanta = quanta;
    return cpu;
}
