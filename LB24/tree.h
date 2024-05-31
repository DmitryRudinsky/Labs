//
// Created by Дима on 30.05.2024.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#ifndef C_TREE_H
#define C_TREE_H

typedef enum {
    NONE,
    INT,
    COMBINED,
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    RAISE_TO_POWER,
    UNARY_MINUS,
    OPENING_BRACKET,
    CLOSING_BRACKET,
    LAST_SPACE
} Token_type;

typedef struct {
    Token_type type;
    int value;
    char name[50];
}Token;


typedef struct {
    Token token;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

char* remove_spaces(const char* input_string);
Token_type determine_type_of_char(char symbol);
int str_to_int(const char *str);
int char_to_int(char c);
Token create_token(const char **expr_ptr);
TreeNode* create_tree_node(Token token);
bool is_valid_expression(const char *expression);
bool is_int_or_comb(Token_type tokenType);

#endif //C_TREE_H
