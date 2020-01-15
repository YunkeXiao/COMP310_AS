#ifndef COMP310_AS1_SHELLMEMORY_H
#define COMP310_AS1_SHELLMEMORY_H

int setValue(char* var, char* value, struct MEM* shellmemory, int* memorySize);
int printValue(char* var, char* value, struct MEM* shellmemory, int* memorySize);

extern struct MEM* shellMemory;
extern int* memorySize;

#endif //COMP310_AS1_SHELLMEMORY_H
