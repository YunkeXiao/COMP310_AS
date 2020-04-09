#include <string.h>
#include <stdio.h>

void formatBuffer(char* buffer) {
    /*
     * We need the end of buffer to be a newline when reading a file in the 'run' command
     *
     * @param buffer Buffer string
     * @return string Formatted buffer
     */
    int length = (int)strlen(buffer);
    if (buffer[length - 1] != '\n'){
        buffer[length] = '\n';
        buffer[length + 1] = '\0';
    }
}