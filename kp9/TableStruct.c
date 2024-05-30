//
// Created by Дима on 17.05.2024.
//

#include "TableStruct.h"


Table_handle table_init(int cap){
    Table_handle table = malloc(sizeof (Table));
    table->capacity = cap;
    table->current_size = 0;
    table->isSorted = false;
    table->data_keys = malloc(sizeof (Key) * cap);
    table->data_values = malloc(sizeof (Value) * cap);
    return table;
}

bool is_table_empty(Table_handle table){
    return table->current_size == 0;
}

void destroy_table(Table_handle table){
    free(table->data_keys);
    free(table->data_values);
    free(table);
}

void grow_buff(Table_handle table){
    table->capacity *= 2;
    table->data_keys = realloc(table->data_keys, sizeof (Table) * table->capacity);
    table->data_values = realloc(table->data_values, sizeof (Table) * table->capacity);
    if (table->data_keys == NULL && table->data_values == NULL) {
        perror("Ошибка в перезаписывание памяти");
        exit(EXIT_FAILURE);
    }
}

void * push_elem_to_table(Table_handle table, char *key_and_value){
    if(table->capacity <= table->current_size + 1){
        grow_buff(table);
    }
    int result = sscanf(key_and_value, "%lf/%lf", &table->data_keys[table->current_size].dbl, &table->data_values[table->current_size].el_value);
    if (result != 2) {
        printf("Неправильно введены значения\n");
        return NULL;
    }
    table->current_size += 1;
    table->isSorted = false;
}

int string_len(double value){
    char buffer[64];
    int length = snprintf(buffer, sizeof(buffer), "%f", value);
    if (length < 0) {
        perror("snprintf");
        return 1;
    }
    return length;
}


char* add_spaces(int n) {
    char *space_string = malloc(n + 1);
    if (space_string == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        space_string[i] = ' ';
    }
    space_string[n] = '\0';
    return space_string;
}



void print_table(Table_handle table){
    if(is_table_empty(table)){
        printf("Таблица пустая\n");
        return;
    }
    printf("|Key                               |Value                           |\n");
    printf("|##################################|################################|\n");
    int table_size = table->current_size;
    for(int i = 0; i < table_size; i++){
        int key_len = 34 - string_len(table->data_keys[i].dbl);
        char *spaces = add_spaces(key_len);
        printf("%lf %s %lf\n", table->data_keys[i].dbl, spaces, table->data_values[i].el_value);
    }
    printf("\n");
}

void print_line_by_index(Table_handle table, int index){
    if(index < 0){
        printf("Индекс должен быть больше нуля\n");
        return;
    }
    Key_handle key = &table->data_keys[index];
    Value_handle value = &table->data_values[index];
    int key_len = 34 - string_len(key->dbl);
    char *spaces = add_spaces(key_len);
    printf("|Key                               |Value                           |\n");
    printf("|##################################|################################|\n");
    printf("%lf %s %lf\n",key->dbl, spaces, value->el_value);
    printf("\n");
}

double get_value_by_index(Table_handle table, int index){
    return table->data_values[index].el_value;
}

double get_key_by_index(Table_handle table, int index){
    return table->data_keys[index].dbl;
}

int keycmp(Table_handle table, int index1, int index2){
    if(table->data_keys[index1].dbl > table->data_keys[index2].dbl){
        return -1;
    }else if(table->data_keys[index1].dbl < table->data_keys[index2].dbl){
        return 1;
    }
    return 0;
}

void swap_table_elements(Table_handle table, int index1, int index2) {
    Value temp_value = table->data_values[index1];
    Key temp_keys = table->data_keys[index1];
    table->data_keys[index1] = table->data_keys[index2];
    table->data_values[index1] = table->data_values[index2];
    table->data_keys[index2] = temp_keys;
    table->data_values[index2] = temp_value;
}

void heapify(Table_handle table, int data_size, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < data_size && keycmp(table, left, largest) == -1){
        largest = left;
    }
    if(right < data_size && keycmp(table, right, largest) == -1){
        largest = right;
    }
    if(largest != i){
        swap_table_elements(table, i, largest);
        heapify(table, data_size, largest);
    }
}

void heapSort(Table_handle table, int data_size){
    for(int i = data_size / 2 - 1; i >= 0; i--){
        heapify(table, data_size, i);
    }
    for (int i = data_size - 1; i >= 0; i--){
        swap_table_elements(table, 0, i);
        heapify(table, i, 0);
    }
    table->isSorted = true;
}

int search_elem(Table_handle table, double required_key) {
    int left = 0;
    int right = table->current_size - 1;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;

        if (table->data_keys[middle].dbl < required_key) {
            left = middle + 1;
        } else if (table->data_keys[middle].dbl > required_key) {
            right = middle - 1;
        } else {
            return table->data_values[middle].el_value;
        }
    }

    return -1;
}