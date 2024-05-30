//e
// Created by Дима on 18.05.2024.
//

#ifndef C_INTERFACE_H
#define C_INTERFACE_H
#include "TableStruct.h"


void print_menu();
char* create_double_string(double double1, double double2);
void push_elem(Table_handle table, double key, double value);
int find_elem_by_key(Table_handle table, double key);

#endif //C_INTERFACE_H
