//
// Created by Дима on 25.05.2024.
//

#ifndef C_QUEUE_H
#define C_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue Queue;
typedef Queue* Queue_handle;


struct Queue {
    int first;
    int size;
    int capacity;
    double* buff;
};

void init_queue(Queue_handle q);
void destroy_queue(Queue_handle q);
int queue_size(Queue_handle q);
bool queue_is_empty(Queue_handle q);
bool grow_buffer(Queue_handle q);
bool queue_push(Queue_handle q, double val);
bool shrink_buffer(Queue_handle q);
bool queue_pop(Queue_handle q);
void print_queue(Queue_handle q);
void find_and_shift(Queue_handle q);
void insertion_sort_queue(Queue_handle q);
void print_menu();

#endif //C_QUEUE_H
