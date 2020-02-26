#ifndef COMP310_AS1_SHELLMEMORY_H
#define COMP310_AS1_SHELLMEMORY_H
#include "MEM.h"

void initializeShellMemory();
int setValue(char* var, char* value, int* memorySize);
int printValue(char* var, int* memorySize);

#endif //COMP310_AS1_SHELLMEMORY_H
