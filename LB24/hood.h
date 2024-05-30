//
// Created by Дима on 30.05.2024.
//

#include "stack.h"
#include "tree_stack.h"

#ifndef C_HOOD_H
#define C_HOOD_H

void add_token_to_operations(Operation_stack_handle operationStack, Token token);
void add_token_to_treeStack(TreeStack_handle treeStack, Token token);

#endif //C_HOOD_H
