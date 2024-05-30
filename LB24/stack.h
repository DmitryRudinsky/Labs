//
// Created by Дима on 29.05.2024.
//

#include "tree.h"

#ifndef C_STACK_H
#define C_STACK_H


typedef struct {
    Token *tokens;
    size_t size;
    size_t capacity;
} Operation_stack;

typedef Operation_stack* Operation_stack_handle;

Operation_stack_handle operationStack_init(int cap);
void destroy_operationStack(Operation_stack_handle operationStack);
bool operationStack_is_empty(Operation_stack_handle operationStack);
bool need_to_grow(Operation_stack_handle operationStack);
void grow_operationStack_buffer(Operation_stack_handle operationStack);
void operationStack_push(Operation_stack_handle operationStack, Token token);
void shrink_operationStack_buffer(Operation_stack_handle operationStack);
bool need_to_shrink(Operation_stack_handle operationStack);
Token operationStack_pop(Operation_stack_handle operationStack);
Token get_last_token(Operation_stack_handle operationStack);
void print_operation_stack(Operation_stack_handle stack);


#endif //C_STACK_H
