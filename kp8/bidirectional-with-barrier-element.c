//
// Created by Дима on 13.05.2024.
//

#include "bidirectional-with-barrier-element.h"


struct bdBarList_elem {
    double val;
    int next;
    int prev;
};

struct bdBarList {
    int head;
    int tail;
    bdBarList_elem* buffer;
    int capacity;
    int current_size;
    int last_empty;
};

struct bdBarList_iter {
    int prev;
    bdBarList_handle list;
};



bdBarList_handle bdBarList_init(int count) {
    bdBarList_handle list = malloc(sizeof(bdBarList));
    if (list == NULL) {
        return NULL;
    }
    list->head = -1;
    list->tail = -1;
    list->current_size = 0;
    list->capacity = count;
    list->buffer = malloc(sizeof(bdBarList_elem) * count);
    if (list->buffer == NULL) {
        free(list);
        return NULL;
    }

    for (int i = 0; i < count - 1; i++) {
        ((list->buffer)[i]).next = i + 1;
        ((list->buffer)[i]).prev = i - 1;
    }
    list->buffer[0].prev = -1;
    list->buffer[count - 1].next = 0;
    list->last_empty = 0;
    return list;
}


bdBarList_iter bdBarList_iter_next(bdBarList_iter list_iter) {
    if (list_iter.prev == -1) {
        return (bdBarList_iter) { list_iter.list->head, list_iter.list };
    }
    return (bdBarList_iter) { list_iter.list->buffer[list_iter.prev].next, list_iter.list };
}

bdBarList_iter bdBarList_iter_prev(bdBarList_iter list_iter) {
    if (list_iter.prev == -1) {
        return (bdBarList_iter) { list_iter.list->head, list_iter.list };
    }
    return (bdBarList_iter) { list_iter.list->buffer[list_iter.prev].prev, list_iter.list };
}

bool bdBarList_iter_equal(bdBarList_iter it1, bdBarList_iter it2) {
    return (it1.prev == it2.prev && it1.list == it2.list);
}


bdBarList_iter bdBarList_iter_begin(bdBarList_handle list) {
    return (bdBarList_iter) { -1, list };
}

bdBarList_iter bdBarList_iter_end(bdBarList_handle list) {
    return (bdBarList_iter) { list->tail, list };
}

double bdBarList_iter_val(bdBarList_iter list_iter) {
    if (list_iter.prev == -1) {
        return (list_iter.list->buffer)[list_iter.list->head].val;
    }
    else {
        return (list_iter.list->buffer)[list_iter.list->buffer[list_iter.prev].next].val;
    }
}


bool bdBarList_is_empty(bdBarList_handle list) {
    return list->current_size == 0;
}

void insert_before(bdBarList_iter* list_iter, double val) {
    if (list_iter->list->current_size == list_iter->list->capacity) {
        if (!grow_buff(list_iter->list)) {
            return;
        }
    }
    bdBarList_elem new_elem;
    new_elem.val = val;
    list_iter->list->current_size++;
    int new_index = list_iter->list->last_empty;
    list_iter->list->last_empty = list_iter->list->buffer[new_index].next;
    if (list_iter->prev == -1) {
        new_elem.next = list_iter->list->head;
        new_elem.prev = -1;
        if (list_iter->list->head != -1) {
            list_iter->list->buffer[list_iter->list->head].prev = new_index;
        }
        list_iter->list->head = new_index;
        list_iter->prev = new_index;

        if (list_iter->list->tail == -1) {
            list_iter->list->tail = new_index;
        }
    } else {
        new_elem.next = list_iter->list->buffer[list_iter->prev].next;
        new_elem.prev = list_iter->prev;
        if (list_iter->list->buffer[list_iter->prev].next != -1) {
            list_iter->list->buffer[list_iter->list->buffer[list_iter->prev].next].prev = new_index;
        }
        list_iter->list->buffer[list_iter->prev].next = new_index;
        list_iter->prev = new_index;

        if (new_elem.next == -1) {
            list_iter->list->tail = new_index;
        }
    }
    list_iter->list->buffer[new_index] = new_elem;
}


void print_list(bdBarList_handle list) {
    if (list->current_size == 0) {
        printf("Список пустой\n");
        return;
    }
    for (bdBarList_iter list_iter = bdBarList_iter_begin(list); !bdBarList_iter_equal(list_iter, bdBarList_iter_end(list)); list_iter = bdBarList_iter_next(list_iter)) {
        printf("%lf ", bdBarList_iter_val(list_iter));
    }
    printf("\n");
}

bdBarList_iter get_n_iter(int n, bdBarList_handle list) {
    bdBarList_iter iter = bdBarList_iter_begin(list);
    for (int i = 1; i < n; i++) {
        iter = bdBarList_iter_next(iter);
    }
    return iter;
}

bool grow_buff(bdBarList_handle list) {
    int old_capacity = list->capacity;
    int new_capacity = old_capacity * 2;
    bdBarList_elem* new_buff = realloc(list->buffer, new_capacity * sizeof(bdBarList_elem));
    if (new_buff != NULL) {
        list->buffer = new_buff;
        list->last_empty = old_capacity;
        for (int i = old_capacity; i < new_capacity - 1; i++) {
            list->buffer[i].next = i + 1;
            list->buffer[i].prev = i - 1;
        }
        list->capacity = new_capacity;
        list->buffer[new_capacity - 1].next = -1;
        return true;
    }
    return false;
}

void shrink_buff(bdBarList_handle list) {
    bdBarList_handle tmp = bdBarList_init(list->current_size);
    while (!bdBarList_is_empty(list)) {
        bdBarList_iter t1 = bdBarList_iter_begin(list);
        double val = bdBarList_iter_val(t1);
        bdBarList_remove(&t1);
        bdBarList_iter t2 = bdBarList_iter_end(&tmp);
        insert_before(&t2, val);
    }

    list->buffer = realloc(list->buffer, list->capacity * 2 / 3 * sizeof(bdBarList_elem));
    list->last_empty = 0;
    list->capacity = list->capacity * 2 / 3;
    while (!bdBarList_is_empty(&tmp)) {
        bdBarList_iter t1 = bdBarList_iter_begin(&tmp);
        double val = bdBarList_iter_val(t1);
        bdBarList_pop(&t1);
        bdBarList_iter t2 = bdBarList_iter_end(list);
        insert_before(&t2, val);
    }
}

void bdBarList_pop(bdBarList_iter* list_iter) {
    bdBarList_remove(list_iter);
    if (list_iter->list->current_size == list_iter->list->capacity * 4 / 9) {
        shrink_buff(list_iter->list);
    }
}

void bdBarList_remove(bdBarList_iter* list_iter) {
    bdBarList_elem* to_del;
    int tmp = list_iter->list->last_empty;

    list_iter->list->current_size--;
    if (list_iter->prev == -1) {
        to_del = &(list_iter->list->buffer[list_iter->list->head]);
        list_iter->list->last_empty = list_iter->list->head;
        int tmp = list_iter->list->buffer[list_iter->list->tail].next;
        list_iter->list->buffer[list_iter->list->tail].next = list_iter->list->head;
        if (list_iter->list->current_size == 0) {
            list_iter->list->head = -1;
            list_iter->list->tail = -1;
        }
        else {
            list_iter->list->head = to_del->next;
        }
        to_del->next = tmp;
    }
    else {
        to_del = &(list_iter->list->buffer[list_iter->list->buffer[list_iter->prev].next]);

        if (list_iter->list->current_size == 0) {
            list_iter->list->head = -1;
            list_iter->list->tail = -1;
        }
        int tmp = list_iter->list->buffer[list_iter->prev].next;
        list_iter->list->last_empty = list_iter->list->buffer[list_iter->prev].next;
        list_iter->list->buffer[list_iter->prev].next = to_del->next;
        to_del->next = list_iter->list->buffer[list_iter->list->tail].next;
        list_iter->list->buffer[list_iter->list->tail].next = tmp;
        if (to_del->next == list_iter->list->tail) {
            list_iter->list->tail = list_iter->prev;
        }
    }
}

void bdBarList_destroy(bdBarList_handle list) {
    free(list->buffer);
    free(list);
}

void del_every_kth(bdBarList_handle list, int k) {
    if (list->current_size < k) {
        printf("Слишком мало элементов списка\n");
        return;
    }
    int current_index_to_del = k;
    while (current_index_to_del <= list->current_size) {
        removeEl(list, current_index_to_del);
        current_index_to_del += k - 1;
    }
}

void insert(bdBarList_handle list, int pos, double val) {
    if(pos > list->current_size + 1) {
        printf("Слишком большой индекс\n");
        return;
    }
    bdBarList_iter temp = get_n_iter(pos, list);
    insert_before(&temp, val);
}

void removeEl(bdBarList_handle list, int pos) {
    if (pos > list->current_size || list->current_size == 0) {
        printf("Слишком большой индекс\n");
        return;
    }
    bdBarList_iter temp = get_n_iter(pos, list);
    bdBarList_pop(&temp);
}

void open_menu() {
    printf("h - открыть меню.\n");
    printf("1 [value, position] -  вставить value перед позицией position.\n");
    printf("2 [position] - удалить элемент на позиции position.\n");
    printf("3 - распечатать список.\n");
    printf("4 [k] - Удалить каждый k-й элемент\n");
}

