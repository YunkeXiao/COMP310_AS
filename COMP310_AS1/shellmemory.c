#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "MEM.h"

#define MEM_SIZE 1000

int setValue(char* var, char* value, struct MEM* shellMemory, int* memorySizePtr){
    /*
     * Look for {var} in {shellMemory}. If not found, then we create a new {MEM} struct and add it to {shellMemory}
     * If found, the simply update the value of the {MEM} struct.
     *
     * @param: var
     * @param: value
     * @param: shellMemory Array storing all var:value pairs.
     * @param: memorySize Int representing the number of pairs in the shellMemory.
     * @return: int Error code
     *
     */
    struct MEM* data;
    for(int i = 0; i < *memorySizePtr; i++){
        data = &shellMemory[i];
        if (strcmp(data->var, var) == 0){
            data->value = value;
            return 0;
        }
    }
    // If memory size has reached maximum capacity, return appropriate error code
    if (*memorySizePtr == MEM_SIZE){
        return 3;
    }

    struct MEM newData = {.var = var, .value = value};
    shellMemory[*memorySizePtr] = newData;
    *memorySizePtr += 1;
    return 0;
}

int printValue(char* var, struct MEM* shellMemory, int* memorySizePtr){
    /*
     * Look for {var} in {shellMemory}. If found, return its paired {value} otherwise return an error code
     *
     * @param: var
     * @param: value
     * @param: shellMemory Array storing all var:value pairs.
     * @param: memorySize Int representing the number of pairs in the shellMemory.
     * @return: int Error code
     */
    struct MEM data;
    for(int i = 0; i < *memorySizePtr; i++){
        data = shellMemory[i];
        if (strcmp(data.var, var) == 0){
            printf("VAR: %s\nVALUE: %s\n", data.var, data.value);
            return 0;
        }
    }
    return 4;
}
