#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include "shell.h"
#include "constants.h"
#include "ram.h"

int main(){
    int start, end;
    FILE *p = fopen("script1.txt", "r");
    addToRAM(p, &start, &end);
//    shellUI();
}

