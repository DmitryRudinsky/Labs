//
// Created by Дима on 29.05.2024.
//
#include "hood.h"

int main() {

    char *current_expression = "(A + 10) - 155 * B ^ 2";

    if (is_valid_expression(current_expression)) {
        printf("Выражение корректное.\n");
    } else {
        printf("Выражение некорректное.\n");
        return 0;
    }

    char *expression_without_spaces = remove_spaces(current_expression);
    const char *ptr = expression_without_spaces;
    Operation_stack_handle operationStack = operationStack_init(10);
    TreeStack_handle treeStack = treeStack_init(10);

    while (*ptr != '\0') {
        Token token = create_token(&ptr);
        work_with_token(token, operationStack, treeStack);
        print_operation_stack(operationStack);
    }

    print_tree_stack(treeStack);


    free(expression_without_spaces);
    return 0;
}