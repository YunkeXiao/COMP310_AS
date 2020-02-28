#include <stdlib.h>
#include "cpu.h"
#include "CPU.h"

struct CPU *createCPU(int quanta){
    /*
     * Create new CPU
     * @param quanta size
     */
    struct CPU *cpu = malloc(sizeof(struct CPU));
    cpu->quanta = quanta;
    return cpu;
}
