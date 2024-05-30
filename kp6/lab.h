#ifndef LAB_H_
#define LAB_H_

#include <stdio.h>
#include <stdlib.h>

void exitWithError(char *message, int errno);
FILE *openFileFromArg(char *argv[], int argIdx, char *mode);
void checkStdErr(FILE* file);

#endif LAB_H_
