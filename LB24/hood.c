//
// Created by Дима on 30.05.2024.
//

#include "hood.h"


void work_with_token(Token token, Operation_stack_handle operationStack, TreeStack_handle treeStack) {
    if (token.type == INT || token.type == COMBINED) {
        TreeNode *current_node = create_tree_node(token);
        treeStack_push(treeStack, current_node);
    }

    if (token.type == CLOSING_BRACKET) {
        while (!operationStack_is_empty(operationStack)) {
            Token last_token = operationStack_pop(operationStack);
            if (last_token.type == OPENING_BRACKET) {
                break;
            }
        }
    } else {
        while (!operationStack_is_empty(operationStack)) {
            Token last_token = get_last_token(operationStack);
            if (last_token.type == OPENING_BRACKET || last_token.type == NONE) {
                break;
            }
            if ((token.type == PLUS || token.type == MINUS) &&
                (last_token.type == PLUS || last_token.type == MINUS || last_token.type == MULTIPLICATION || last_token.type == DIVISION || last_token.type == RAISE_TO_POWER)) {
                operationStack_pop(operationStack);
            } else if ((token.type == MULTIPLICATION || token.type == DIVISION) &&
                       (last_token.type == MULTIPLICATION || last_token.type == DIVISION || last_token.type == RAISE_TO_POWER)) {
                operationStack_pop(operationStack);
            } else if (token.type == RAISE_TO_POWER && last_token.type == RAISE_TO_POWER) {
                operationStack_pop(operationStack);
            } else {
                break;
            }
        }
        operationStack_push(operationStack, token);
    }
}
