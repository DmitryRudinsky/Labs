#ifndef C_FUNCTIONS_AND_STRUCT_H
#define C_FUNCTIONS_AND_STRUCT_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct node node;

struct node{
    double val;
    node* left;
    node* right;
};

typedef node* tree;


tree create_empty_tree();
void destroy(tree t);
tree build_tree(tree left, double val, tree right);
bool tree_is_empty(tree t);
double get_val(tree t);
tree get_left(tree t);
tree get_right(tree t);
tree insert(tree *t, double val);
void print_tree(tree t, int h);
int height(tree t);
int level_width(tree t, int level);
bool is_width_monotonic(tree t);
tree delete_node(tree t, double val);
int search_val(tree t, double val);
void print_menu();

#endif //C_FUNCTIONS_AND_STRUCT_H
