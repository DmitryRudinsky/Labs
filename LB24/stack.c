#include "stack.h"

Operation_stack_handle operationStack_init(int cap){
    Operation_stack_handle operationStack = malloc(sizeof(Operation_stack));
    operationStack->capacity = cap;
    operationStack->size = 0;
    operationStack->tokens = malloc(sizeof(Token) * cap);
    return operationStack;
}

void destroy_operationStack(Operation_stack_handle operationStack) {
    if (operationStack) {
        free(operationStack->tokens);
        free(operationStack);
    }
}

bool operationStack_is_empty(Operation_stack_handle operationStack){
    return operationStack->size == 0;
}

bool need_to_grow(Operation_stack_handle operationStack){
    return operationStack->capacity < operationStack->size * 2;
}

void grow_operationStack_buffer(Operation_stack_handle operationStack){
    operationStack->capacity *= 2;
    operationStack->tokens = realloc(operationStack->tokens, sizeof(Token) * operationStack->capacity);
    if(operationStack->tokens == NULL){
        printf("Ошибка в записи памяти\n");
        exit(EXIT_FAILURE);
    }
}

void operationStack_push(Operation_stack_handle operationStack, Token token){
    if(need_to_grow(operationStack)){
        grow_operationStack_buffer(operationStack);
    }
    operationStack->tokens[operationStack->size] = token;
    operationStack->size++;
}

void shrink_operationStack_buffer(Operation_stack_handle operationStack) {
    size_t new_capacity = operationStack->capacity / 2;
    if (new_capacity < 1) {
        new_capacity = 1;
    }

    operationStack->tokens = realloc(operationStack->tokens, sizeof(Token) * new_capacity);
    if (operationStack->tokens == NULL) {
        printf("Ошибка в записи памяти при уменьшении буфера\n");
        exit(EXIT_FAILURE);
    }
    operationStack->capacity = new_capacity;
}

bool need_to_shrink(Operation_stack_handle operationStack){
    return operationStack->size < operationStack->capacity / 4;
}

Token operationStack_pop(Operation_stack_handle operationStack) {
    if (operationStack->size == 0) {
        printf("Ошибка: попытка извлечения из пустого стека\n");
        exit(EXIT_FAILURE);
    }
    Token token = operationStack->tokens[operationStack->size - 1];
    operationStack->size--;
    if (need_to_shrink(operationStack) && !operationStack_is_empty(operationStack)) {
        shrink_operationStack_buffer(operationStack);
    }
    return token;
}

Token get_last_token(Operation_stack_handle operationStack){
    return operationStack->tokens[operationStack->size - 1];
}

void print_operation_stack(Operation_stack_handle stack) {
    printf("Operation Stack (size: %zu, capacity: %zu):\n", stack->size, stack->capacity);
    for (size_t i = 0; i < stack->size; ++i) {
        Token token = stack->tokens[i];
        printf("Token %zu: ", i + 1);
        switch (token.type) {
            case INT:
                printf("Type: INT, Value: %d\n", token.value);
                break;
            case PLUS:
                printf("Type: PLUS, Symbol: +\n");
                break;
            case MINUS:
                printf("Type: MINUS, Symbol: -\n");
                break;
            case MULTIPLICATION:
                printf("Type: MULTIPLICATION, Symbol: *\n");
                break;
            case DIVISION:
                printf("Type: DIVISION, Symbol: /\n");
                break;
            case RAISE_TO_POWER:
                printf("Type: RAISE_TO_POWER, Symbol: ^\n");
                break;
            case UNARY_MINUS:
                printf("Type: UNARY_MINUS, Symbol: !\n");
                break;
            case OPENING_BRACKET:
                printf("Type: OPENING_BRACKET, Symbol: (\n");
                break;
            case CLOSING_BRACKET:
                printf("Type: CLOSING_BRACKET, Symbol: )\n");
                break;
            case COMBINED:
                printf("Type: COMBINED, Name: %s\n", token.name);
                break;
            default:
                printf("Type: NONE\n");
                break;
        }
    }
}