#include <stdio.h>
#include "srtuct.h"
#include "lab.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        exitWithError("Invalid number of arguments were provided", 1);
    }
    FILE* in = openFileFromArg(argv, 1, "r");
    FILE* out = openFileFromArg(argv, 2, "w");
    int total_written = 0;
    structs st;
    while (fscanf(in, "%[^,],%d,%d,%d,%d,%d,%d,%d",
                  st.exam_subject, &st.score, &st.grade11, &st.grade12,
                  &st.male, &st.female, &st.white, &st.black) == 8) {
        checkStdErr(in);
        const size_t written = fwrite(&st, sizeof(st), 1, out);
        checkStdErr(out);
        total_written++;
        if (written != 1) {
            exitWithError("Error while writing data to file", 3);
        }
    }
    checkStdErr(in);
    printf("Written %d records to %s", total_written, argv[2]);
    fclose(in);
    fclose(out);
    return 0;
}