//
// Created by Дима on 18.05.2024.
//

#include "Interface.h"

void print_menu(){
    printf("h - помощь\n");
    printf("0 - завершить программу\n");
    printf("1 [key, value] - добавить элемент в таблицу\n");
    printf("2 - отсортировать таблицу\n");
    printf("3 - вывести таблицу\n");
    printf("4 [key] - найти элемемент в таблице по ключу\n");
}


char* create_double_string(double double1, double double2){
    int buffer_size = 60;
    char *result = (char *)malloc(buffer_size * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    snprintf(result, buffer_size, "%.2f/%.2f", double1, double2);
    return result;
}

void push_elem(Table_handle table, double key, double value){
    char *key_and_value = create_double_string(key, value);
    push_elem_to_table(table, key_and_value);
}

int find_elem_by_key(Table_handle table, double key){
    if (table->isSorted == false){
        printf("Таблица не была отсортирована\n");
        return -1;
    }else{
        return search_elem(table, key);
    }
}