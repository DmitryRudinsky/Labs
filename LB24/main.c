#include "hood.h"

int main() {

//    char *current_expression = "(A + 10) - 155 * B ^ 2";
//    char *current_expression = "(A + 10) - (155 * B) ^ 2";
//    char *current_expression = "1 + 10 - 155 * 2 ^ 2";
    char *current_expression = "A * 12 + 3 - (B / 4) * 3 + 42 / 2 - 10 + (C + (D - 4))";
//    char *current_expression = "A * 12) ++ 3 - (B / 4) * 3 + 42 / 2 AA - 10 + (C + (D - 4))";

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
    }

    print_operation_stack(operationStack);
    print_tree_stack(treeStack);

    int levels = count_levels(*treeStack->node);
    int operands = count_operands(*treeStack->node);
    int variables = count_variables(*treeStack->node);
    int constants = count_constants(*treeStack->node);
    int operations = count_operations(*treeStack->node);

    printf("Число уровней дерева выражения: %d\n", levels);
    printf("Количество операндов: %d\n", operands);
    printf("Количество переменных: %d\n", variables);
    printf("Количество констант: %d\n", constants);
    printf("Количество операций: %d\n", operations);

    destroy_operationStack(operationStack);
    destroy_treeStack(treeStack);
    free(expression_without_spaces);
    return 0;
}