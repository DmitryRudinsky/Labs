//
// Created by Дима on 30.05.2024.
//

#include "tree_stack.h"

TreeStack_handle treeStack_init(int cap){
    TreeStack_handle treeStack = malloc(sizeof(TreeStack));
    if (treeStack == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для стека\n");
        exit(EXIT_FAILURE);
    }
    treeStack->node = malloc(sizeof(TreeNode) * cap);
    if (treeStack->node == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для массива узлов\n");
        free(treeStack);
        exit(EXIT_FAILURE);
    }
    treeStack->capacity = cap;
    treeStack->size = 0;
    return treeStack;
}

void destroy_treeStack(TreeStack_handle treeStack){
    if(treeStack){
        free(treeStack->node);
        free(treeStack);
    }
}

bool treeStack_is_empty(TreeStack_handle treeStack){
    return treeStack->size == 0;
}

bool need_to_grow_treeStack(TreeStack_handle treeStack) {
    return treeStack->capacity < treeStack->size * 2;
}


void grow_treeStack_buffer(TreeStack_handle treeStack) {
    treeStack->capacity *= 2;
    treeStack->node = realloc(treeStack->node, sizeof(TreeNode *) * treeStack->capacity);
    if (treeStack->node == NULL) {
        printf("Ошибка в записи памяти\n");
        exit(EXIT_FAILURE);
    }
}

void treeStack_push(TreeStack_handle treeStack, TreeNode *node) {
    if (need_to_grow_treeStack(treeStack)) {
        grow_treeStack_buffer(treeStack);
    }
    treeStack->node[treeStack->size] = node;
    treeStack->size++;
}

void shrink_treeStack_buffer(TreeStack_handle treeStack) {
    size_t new_capacity = treeStack->capacity / 2;
    if (new_capacity < 1) {
        new_capacity = 1;
    }

    treeStack->node = realloc(treeStack->node, sizeof(TreeNode *) * new_capacity);
    if (treeStack->node == NULL) {
        printf("Ошибка в записи памяти при уменьшении буфера\n");
        exit(EXIT_FAILURE);
    }
    treeStack->capacity = new_capacity;
}

bool need_to_shrink_treeStack(TreeStack_handle treeStack) {
    return treeStack->size < treeStack->capacity / 4;
}

TreeNode *treeStack_pop(TreeStack_handle treeStack) {
    if (treeStack->size == 0) {
        printf("Ошибка: попытка извлечения из пустого стека\n");
        exit(EXIT_FAILURE);
    }
    TreeNode *node = treeStack->node[treeStack->size - 1];
    treeStack->size--;
    if (need_to_shrink_treeStack(treeStack) && !treeStack_is_empty(treeStack)) {
        shrink_treeStack_buffer(treeStack);
    }
    return node;
}

TreeNode *get_last_treeNode(TreeStack_handle treeStack) {
    if (treeStack->size == 0) {
        printf("Ошибка: стек пуст\n");
        exit(EXIT_FAILURE);
    }
    return treeStack->node[treeStack->size - 1];
}

TreeNode *get_penultimate_treeNode(TreeStack_handle treeStack) {
    if (treeStack->size == 0) {
        printf("Ошибка: стек пуст\n");
        exit(EXIT_FAILURE);
    }
    return treeStack->node[treeStack->size - 2];
}




void print_tree_stack(TreeStack_handle treeStack) {
    printf("Tree Stack (size: %zu, capacity: %zu):\n", treeStack->size, treeStack->capacity);
    for (size_t i = 0; i < treeStack->size; ++i) {
        TreeNode *tree = treeStack->node[i];
        printf("Tree %zu:\n", i + 1);
        print_tree(tree, 0);
        printf("\n");
    }
}

void print_tree(TreeNode *node, int level) {
    if (node == NULL) {
        return;
    }

    print_tree(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("\t");
    }

    if (node->token.type == INT) {
        printf("%d\n", node->token.value);
    } else if (node->token.type == COMBINED) {
        printf("%s\n", node->token.name);
    } else {
        printf("%s\n", node->token.name);
    }

    print_tree((TreeNode *) node->left, level + 1);
}

