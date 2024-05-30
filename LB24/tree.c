//
// Created by Дима on 30.05.2024.
//

#include "tree.h"

char *remove_spaces(const char *input_string) {
    int input_length = strlen(input_string);
    int count = 0;
    for (int i = 0; i < input_length; i++) {
        if (input_string[i] != ' ') {
            count++;
        }
    }

    char *result = (char *) malloc(count + 1);
    if (result == NULL) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    for (int i = 0; i < input_length; i++) {
        if (input_string[i] != ' ') {
            result[j++] = input_string[i];
        }
    }
    result[j] = '\0';

    return result;
}

Token_type determine_type_of_char(char symbol) {
    if (symbol == '+') {
        return PLUS;
    } else if (symbol == '-') {
        return MINUS;
    } else if (symbol == '*') {
        return MULTIPLICATION;
    } else if (symbol == '/') {
        return DIVISION;
    } else if (symbol == '^') {
        return RAISE_TO_POWER;
    } else if (symbol == '!') {
        return UNARY_MINUS;
    } else if (symbol == '(') {
        return OPENING_BRACKET;
    } else if (symbol == ')') {
        return CLOSING_BRACKET;
    } else if (isdigit(symbol)) {
        return INT;
    } else if (isalpha(symbol)) {
        return COMBINED;
    } else {
        return NONE;
    }
}

int str_to_int(const char *str) {
    char *endptr;
    errno = 0;
    long result = strtol(str, &endptr, 10);
    if (endptr == str) {
        fprintf(stderr, "Ошибка: в строке не найдены целочисленные данные\n");
        exit(EXIT_FAILURE);
    }
    return (int) result;
}

int char_to_int(char c) {
    if (!isdigit(c)) {
        fprintf(stderr, "Ошибка: символ не является цифрой\n");
        exit(EXIT_FAILURE);
    }
    return c - '0';
}

Token create_token(const char **expr_ptr) {
    const char *expr = *expr_ptr;
    Token token;
    token.name[0] = '\0';
    token.value = 0;

    if (isdigit(*expr)) {
        char buffer[50];
        int i = 0;
        while (isdigit(*expr)) {
            buffer[i++] = *expr;
            expr++;
        }
        buffer[i] = '\0';
        token.type = INT;
        token.value = strtol(buffer, NULL, 10);
    } else if (isalpha(*expr)) {
        int i = 0;
        while (isalnum(*expr)) {
            token.name[i++] = *expr;
            expr++;
        }
        token.name[i] = '\0';
        token.type = COMBINED;
    } else {
        token.type = determine_type_of_char(*expr);
        if (token.type != NONE) {
            token.name[0] = *expr;
            token.name[1] = '\0';
            expr++;
        }
    }

    *expr_ptr = expr;
    return token;
}

TreeNode* create_tree_node(Token token) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        perror("Ошибка выделения памяти для TreeNode");
        exit(EXIT_FAILURE);
    }
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}


bool is_valid_expression(const char *expression) {
    int open_brackets = 0;
    bool last_was_operator = false;
    bool last_was_open_bracket = false;
    char prev_char = '\0';

    for (const char *ptr = expression; *ptr != '\0'; ++ptr) {
        char current_char = *ptr;
        Token_type type = determine_type_of_char(current_char);

        if (type == NONE && !isspace(current_char)) {
            fprintf(stderr, "Ошибка: недопустимый символ '%c'\n", current_char);
            return false;
        }

        if (type == OPENING_BRACKET) {
            open_brackets++;
            last_was_operator = false;
            last_was_open_bracket = true;
        } else if (type == CLOSING_BRACKET) {
            if (open_brackets == 0 || last_was_operator || last_was_open_bracket) {
                fprintf(stderr, "Ошибка: неправильное использование скобок\n");
                return false;
            }
            open_brackets--;
            last_was_operator = false;
            last_was_open_bracket = false;
        } else if (type == PLUS || type == MINUS || type == MULTIPLICATION || type == DIVISION ||
                   type == RAISE_TO_POWER) {
            if (last_was_operator || last_was_open_bracket) {
                fprintf(stderr, "Ошибка: два оператора подряд или оператор после открывающей скобки\n");
                return false;
            }
            last_was_operator = true;
        } else if (type == INT || type == COMBINED) {
            last_was_operator = false;
            last_was_open_bracket = false;
        }

        prev_char = current_char;
    }

    if (open_brackets != 0) {
        fprintf(stderr, "Ошибка: несоответствие количества открывающихся и закрывающихся скобок\n");
        return false;
    }

    if (last_was_operator) {
        fprintf(stderr, "Ошибка: выражение не может заканчиваться оператором\n");
        return false;
    }

    return true;
}