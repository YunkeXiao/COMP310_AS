#ifndef COMP310_AS1_SHELL_H
#define COMP310_AS1_SHELL_H

int shellUI();
int parseInput(char* input, char** words);
int runFile(char* fileName, char** running_files);
int processInput(char* input);

#endif
