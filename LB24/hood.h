#include "stack.h"
#include "tree_stack.h"

#ifndef C_HOOD_H
#define C_HOOD_H

void work_with_token(Token token, Operation_stack_handle operationStack, TreeStack_handle treeStack);
TreeNode * create_tree_from_stack(TreeNode *poped_node, TreeStack_handle treeStack);
Token create_zero_token();
int count_levels(TreeNode *root);
int count_operands(TreeNode *root);
int count_variables(TreeNode *root);
int count_constants(TreeNode *root);
int count_operations(TreeNode *root);

#endif //C_HOOD_H
