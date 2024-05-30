//
// Created by Дима on 30.05.2024.
//

#include "hood.h"

void add_token_to_operations(Operation_stack_handle operationStack, Token token) {
    if (token.type == INT || token.type == COMBINED) {
        printf("Неправильный тип токена\n");
        return;
    } else {
        operationStack_push(operationStack, token);
    }
}

void add_token_to_treeStack(TreeStack_handle treeStack, Token token) {
    if (token.type == INT || token.type == COMBINED) {
        TreeNode *tree_node = create_tree_node(token);
        treeStack_push(treeStack, tree_node);
    } else {
        printf("Неправильный тип токена\n");
        return;
    }
}