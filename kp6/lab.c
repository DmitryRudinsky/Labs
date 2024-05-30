#include "lab.h"


void exitWithError(char* message, int errorCode) {
    fprintf(stderr, "%s\n", message);
    exit(errorCode);
}

FILE* openFileFromArg(char* argv[], int argIdx, char* mode) {
  FILE* file = fopen(argv[argIdx], mode);
  if (file == NULL) {
      exitWithError("Provided path is not a readable file", 2);
  }
  return file;
}

void checkStdErr(FILE* file) {
  if(ferror(file)) {
      exitWithError("Error while reading/writing file", 8);
  }
}
