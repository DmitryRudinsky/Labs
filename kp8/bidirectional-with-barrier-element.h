//
// Created by Дима on 13.05.2024.
//

#ifndef C_BIDIRECTIONAL_WITH_BARRIER_ELEMENT_H
#define C_BIDIRECTIONAL_WITH_BARRIER_ELEMENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct bdBarList bdBarList;
typedef struct bdBarList_elem bdBarList_elem;
typedef bdBarList* bdBarList_handle;
typedef struct bdBarList_iter bdBarList_iter;



bdBarList_handle bdBarList_init(int count);
bdBarList_iter bdBarList_iter_next(bdBarList_iter it);
bdBarList_iter bdBarList_iter_prev(bdBarList_iter it);
bool bdBarList_iter_equal(bdBarList_iter it1, bdBarList_iter it2);
bdBarList_iter bdBarList_iter_begin(bdBarList_handle l);
bdBarList_iter bdBarList_iter_end(bdBarList_handle l);
double bdBarList_iter_val(bdBarList_iter it);
bool bdBarList_is_empty(bdBarList_handle l);
void insert_before(bdBarList_iter* it, double val);
void print_list(bdBarList_handle l);
bdBarList_iter get_n_iter(int n, bdBarList_handle l);
bool grow_buff(bdBarList_handle l);
void shrink_buff(bdBarList_handle l);
void bdBarList_pop(bdBarList_iter* it);
void bdBarList_destroy(bdBarList_handle l);
void bdBarList_remove(bdBarList_iter* it);
void del_every_kth(bdBarList_handle l, int k);
void insert(bdBarList_handle l, int pos, double val);
void removeEl(bdBarList_handle l, int pos);
void open_menu();



#endif //C_BIDIRECTIONAL_WITH_BARRIER_ELEMENT_H
