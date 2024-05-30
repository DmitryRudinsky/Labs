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
        Token tk = create_token(&ptr);
        if (tk.type == INT) {
            printf("Token type: %d, Token value: %d\n", tk.type, tk.value);
            add_token_to_treeStack(treeStack, tk);
        } else if (tk.type == COMBINED) {
            printf("Token type: %d, Token name: %s\n", tk.type, tk.name);
            add_token_to_treeStack(treeStack, tk);
        } else {
            printf("Token type: %d\n", tk.type);
            add_token_to_operations(operationStack, tk);
        }
    }
    print_operation_stack(operationStack);

    print_tree_stack(treeStack);


    free(expression_without_spaces);
    return 0;
}