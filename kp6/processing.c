#include <stdio.h>
#include "srtuct.h"
#include "lab.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    exitWithError("Invalid number of arguments were provided", 1);
  }
  FILE *in = openFileFromArg(argv, 1, "r");
  structs st;
  int count = 0;
  long long int count_sum_five = 0;
  while (fread(&st, sizeof(st), 1, in)) {
    checkStdErr(in);
    if(st.score == 5){
        const int count = st.grade11 + st.grade12;
        count_sum_five += count;
    }
    count++;
  }
  checkStdErr(in);
  if (count == 0) {
    exitWithError("File is empty", 4);
  }
  fseek(in, 0, SEEK_SET);
  double average =  count_sum_five;
  double above_average_count = 0;
  while (fread(&st, sizeof(st), 1, in)) {
    checkStdErr(in);
      if(st.score == 5){
          const int score = st.white;
          above_average_count += score;
      }
  }
  checkStdErr(in);
  printf("The total number of A's in the two classes is %d, and %d is the number of white children who received a 5. This means that the percentage of A's among whites is %lf proccent", average, above_average_count, (above_average_count / average) * 100);
  fclose(in);
  return 0;
}
