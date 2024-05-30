//
// Created by Дима on 30.05.2024.
//

#include "tree.h"
#ifndef C_TREE_STACK_H
#define C_TREE_STACK_H



typedef struct {
    TreeNode **node;
    size_t size;
    size_t capacity;
}TreeStack;

typedef TreeStack* TreeStack_handle;

TreeStack_handle treeStack_init(int cap);
void destroy_treeStack(TreeStack_handle treeStack);
bool treeStack_is_empty(TreeStack_handle treeStack);
bool need_to_grow_treeStack(TreeStack_handle treeStack);
void grow_treeStack_buffer(TreeStack_handle treeStack);
void treeStack_push(TreeStack_handle treeStack, TreeNode *node);
void shrink_treeStack_buffer(TreeStack_handle treeStack);
bool need_to_shrink_treeStack(TreeStack_handle treeStack);
TreeNode *treeStack_pop(TreeStack_handle treeStack);
TreeNode *get_last_treeNode(TreeStack_handle treeStack);
void print_tree_stack(TreeStack_handle treeStack);
void print_tree(TreeNode* node, int level);


#endif //C_TREE_STACK_H
