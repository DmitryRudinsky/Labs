
#include "queue.h"

void init_queue(Queue_handle q) {
    q->first = 0;
    q->capacity = 10;
    q->size = 0;
    q->buff = (double *) malloc(q->capacity * sizeof(double));
    if (q->buff == NULL) {
        fprintf(stderr, "Не удалось выделить память...\n");
        exit(EXIT_FAILURE);
    }
}


void destroy_queue(Queue_handle q) {
    free(q->buff);
    q->buff = NULL;
    q->capacity = 0;
    q->first = 0;
    q->size = 0;
    free(q);
}

int queue_size(Queue_handle q) {
    return q->size;
}

bool queue_is_empty(Queue_handle q) {
    return queue_size(q) == 0;
}


bool grow_buffer(Queue_handle q) {
    int new_cap = q->capacity * 3 / 2;
    double *new_buff = realloc(q->buff, sizeof(double) * new_cap);
    if (new_buff == NULL) {
        return false;
    }
    q->buff = new_buff;
    for (int i = 0; i < (q->capacity - q->first); i++) {
        q->buff[new_cap - 1 - i] = q->buff[q->capacity - 1 - i];
    }
    q->first = new_cap - q->capacity;
    q->capacity = new_cap;
    return true;
}

bool queue_push(Queue_handle q, double val) {
    if (q->size == q->capacity) {
        if (!grow_buffer(q)) {
            return false;
        }
    }
    q->buff[(q->first + q->size) % q->capacity] = val;
    q->size++;
    return true;
}

bool shrink_buffer(Queue_handle q) {
    if (q->size < q->capacity / 4) {
        int new_cap = q->capacity / 2;
        double *new_buff = (double *) malloc(sizeof(double) * new_cap);
        if (new_buff == NULL) {
            fprintf(stderr, "Не удалось выделить память");
            return false;
        }

        for (int i = 0; i < q->size; i++) {
            new_buff[i] = q->buff[(q->first + i) % q->capacity];
        }

        free(q->buff);
        q->buff = new_buff;
        q->capacity = new_cap;
        q->first = 0;
    }
    return true;
}

bool queue_pop(Queue_handle q) {
    if (queue_is_empty(q)) {
        printf("Очередь и так пустая\n");
        return false;
    }
    q->first = (q->first + 1) % q->capacity;
    q->size--;
    shrink_buffer(q);
    return true;
}

void print_queue(Queue_handle q) {
    if (queue_is_empty(q)) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь: ");
    int index = q->first;
    for (int i = 0; i < q->size; ++i) {
        printf("%.2f ", q->buff[index]);
        index = (index + 1) % q->capacity;
    }
    printf("\n");
}

void find_and_shift(Queue_handle q) {
    if (q->size < 2) {
        return;
    }
    Queue_handle temp_queue = (Queue_handle) malloc(sizeof(Queue));
    init_queue(temp_queue);
    double prev = q->buff[q->first];
    queue_pop(q);
    queue_push(temp_queue, prev);
    bool found = false;
    double element_to_shift = 0;
    while (!queue_is_empty(q)) {
        double current = q->buff[q->first];
        queue_pop(q);
        if (!found && current < prev) {
            element_to_shift = current;
            found = true;
        } else {
            queue_push(temp_queue, current);
        }
        prev = current;
    }
    if (!found) {
        while (!queue_is_empty(temp_queue)) {
            double val = temp_queue->buff[temp_queue->first];
            queue_pop(temp_queue);
            queue_push(q, val);
        }
        destroy_queue(temp_queue);
        return;
    }
    init_queue(q);
    bool inserted = false;
    while (!queue_is_empty(temp_queue)) {
        double val = temp_queue->buff[temp_queue->first];
        queue_pop(temp_queue);
        if (!inserted && element_to_shift < val) {
            queue_push(q, element_to_shift);
            inserted = true;
        }
        queue_push(q, val);
    }
    if (!inserted) {
        queue_push(q, element_to_shift);
    }
    destroy_queue(temp_queue);
}

void insertion_sort_queue(Queue_handle q) {
    if (q->size < 2) {
        return;
    }
    for (int i = 1; i < q->size; i++) {
        find_and_shift(q);
    }
}

void print_menu() {
    printf("h - помощь\n");
    printf("0 - завершить программу\n");
    printf("1 <value> - добавить элемент в очередь\n");
    printf("2 - удалить элемент из очереди\n");
    printf("3 - вывести очередь\n");
    printf("4 - отсортировать очередь при помощи метода вставки\n");
}
