#include "stdio.h"
#include "stdlib.h"

typedef struct {
    double *buf;
    int size;
    int buf_size;
} stack_dbl;

void sd_push(stack_dbl *s, double el){
    if (s -> buf_size == s -> size){
        double *number = realloc(s -> buf, sizeof (double) * s-> size * 3/2);
    }
}

int main(){
    return 0;
}