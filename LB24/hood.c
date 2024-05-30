//
// Created by Дима on 30.05.2024.
//

#include "hood.h"


void work_with_token(Token token, Operation_stack_handle operationStack, TreeStack_handle treeStack) {
    if (token.type != INT && token.type != COMBINED) {
        if (token.type == CLOSING_BRACKET) {
            // Перемещаем операторы из стека операций в стек дерева до открывающей скобки
            while (!operationStack_is_empty(operationStack)) {
                Token last_token = operationStack_pop(operationStack);
                if (last_token.type == OPENING_BRACKET) {
                    break;
                }
                TreeNode *right = treeStack_pop(treeStack);
                TreeNode *left = treeStack_pop(treeStack);
                TreeNode *new_node = create_tree_node(last_token);
                new_node->left = left;
                new_node->right = right;
                treeStack_push(treeStack, new_node);
            }
        } else {
            Token last_token = get_last_token(operationStack);
            if (last_token.type == NONE || last_token.type == OPENING_BRACKET) {
                operationStack_push(operationStack, token);
            } else if (last_token.type == PLUS || last_token.type == MINUS) {
                if (token.type == PLUS || token.type == MINUS) {
                    operationStack_pop(operationStack);
                    operationStack_push(operationStack, token);
                } else {
                    operationStack_push(operationStack, token);
                }
            } else if (last_token.type == MULTIPLICATION || last_token.type == DIVISION) {
                if (token.type == PLUS || token.type == MINUS || token.type == MULTIPLICATION || token.type == DIVISION) {
                    operationStack_pop(operationStack);
                    operationStack_push(operationStack, token);
                } else {
                    operationStack_push(operationStack, token);
                }
            } else if (last_token.type == RAISE_TO_POWER) {
                if (token.type != UNARY_MINUS) {
                    operationStack_pop(operationStack);
                    operationStack_push(operationStack, token);
                } else {
                    operationStack_push(operationStack, token);
                }
            } else if (last_token.type == UNARY_MINUS) {
                operationStack_pop(operationStack);
                operationStack_push(operationStack, token);
            }
        }
    } else {
        TreeNode *new_node = create_tree_node(token);
        treeStack_push(treeStack, new_node);
    }
}