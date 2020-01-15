#include <string.h>
#include <stdio.h>

#define MEM_SIZE 1000

struct MEM{
    char* var;
    char* value;
};

struct MEM shellMemory[MEM_SIZE];
int* memorySize = 0;

int setValue(char* var, char* value, struct MEM* shellmemory, int* memorySize){
    /*
     * Look for {var} in {shellmemory}. If not found, then we create a new {MEM} struct and add it to {shellmemory}
     * If found, the simply update the value of the {MEM} struct.
     *
     * @param: var
     * @param: value
     * @param: shellmemory Array storing all var:value pairs.
     * @param: memorySize Int representing the number of pairs in the shellmemory.
     * @return: int Error code
     */
    struct MEM* data;
    for(int i = 0; i < *memorySize; i++){
        data = (shellmemory + sizeof(data) * i);
        if (strcmp(data->var, var) == 0){
            data->value = value;
            return 0;
        }
    }
    // If memory size has reached maximum capacity, return appropriate error code
    if (*memorySize == MEM_SIZE){
        return 3;
    }

    struct MEM newData;
    newData.var = var;
    newData.value = value;

    shellmemory[*memorySize] = newData;
    *memorySize += 1;
    return 0;
}

int printValue(char* var, char* value, struct MEM* shellmemory, int* memorySize){
    /*
     * Look for {var} in {shellmemory}. If found, return its paired {value} otherwise return an error code
     *
     * @param: var
     * @param: value
     * @param: shellmemory Array storing all var:value pairs.
     * @param: memorySize Int representing the number of pairs in the shellmemory.
     * @return: int Error code
     */
    struct MEM* data;
    for(int i = 0; i < *memorySize; i++){
        data = (shellmemory + sizeof(data) * i);
        if (strcmp(data->var, var) == 0){
            printf("\n%s\n", data->value);
            return 0;
        }
    }
    return 4;
}