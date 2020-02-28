#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "CPU.h"
#include "shell.h"
#include "kernel.h"

struct CPU *createCPU(int quanta){
    /*
     * Create new CPU
     * @param quanta size
     */
    struct CPU *new_cpu = malloc(sizeof(struct CPU));
    cpu->quanta = quanta;
    return new_cpu;
}

int run(int quanta, int end){
    for (int time = 0; time < quanta; time++){
        memset(cpu->IR, '\0', 1000);
        strcpy(cpu->IR, ram[cpu->IP]);
        processInput(cpu->IR);

        if (time == end){
            return 1;
        } else {
            cpu->IP++;
        }
    }
    return 0;
}
