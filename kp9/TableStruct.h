//
// Created by Дима on 17.05.2024.
//

#ifndef C_TABLESTRUCT_H
#define C_TABLESTRUCT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct Key Key;
typedef Key* Key_handle;
typedef struct Value Value;
typedef Value* Value_handle;
typedef struct Table Table;
typedef Table* Table_handle;

struct Key {
    double dbl;
};

struct Value {
    double el_value;
};

struct Table {
    Key *data_keys;
    Value *data_values;
    int current_size;
    int capacity;
    bool isSorted;
};


Table_handle table_init(int cap);
bool is_table_empty(Table_handle table);
void destroy_table(Table_handle table);
void grow_buff(Table_handle table);
int string_len(double value);
char* add_spaces(int n);
void * push_elem_to_table(Table_handle table, char *key_and_value);
void print_table(Table_handle table);
void print_line_by_index(Table_handle table, int index);
double get_value_by_index(Table_handle table, int index);
double get_key_by_index(Table_handle table, int index);
int keycmp(Table_handle table, int index1, int index2);
void swap_table_elements(Table_handle table, int index1, int index2);
void heapify(Table_handle table, int data_size, int i);
void heapSort(Table_handle table, int data_size);
int search_elem(Table_handle table, double required_key);

#endif //C_TABLESTRUCT_H
