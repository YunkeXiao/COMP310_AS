#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "shell.h"
#include "constants.h"
#include "ram.h"
#include "pcb.h"
#include "PCB.h"

int main(){
    struct PCB *pcb;
    pcb = makePCB(20, 50);
//    FILE *p = fopen("script1.txt", "r");
//    addToRAM(p, &start, &end);
//    shellUI();
}

