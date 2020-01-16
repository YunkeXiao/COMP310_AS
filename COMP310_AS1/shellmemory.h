#ifndef COMP310_AS1_SHELLMEMORY_H
#define COMP310_AS1_SHELLMEMORY_H
#include "MEM.h"

int setValue(char* var, char* value, struct MEM* shellmemory, int* memorySize);
int printValue(char* var, struct MEM* shellmemory, int* memorySize);

#endif //COMP310_AS1_SHELLMEMORY_H
