#include "functions_and_struct.h"
#include <stdio.h>
#include <stdbool.h>

tree create_empty_tree() {
    return NULL;
}

void destroy(node *root) {
    if (root != NULL) {
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}

tree build_tree(tree left, double val, tree right) {
    tree tmp = (tree) malloc(sizeof(node));
    tmp->left = left;
    tmp->right = right;
    tmp->val = val;
    return tmp;
}

bool tree_is_empty(tree t) {
    return t == NULL;
}

double get_val(tree t) {
    return t->val;
}

tree get_left(tree t) {
    return t->left;
}

tree get_right(tree t) {
    return t->right;
}

tree insert(tree *t, double val) {
    if (tree_is_empty(*t)) {
        *t = build_tree(NULL, val, NULL);
    } else if (get_val(*t) > val) {
        (*t)->left = insert(&((*t)->left), val);
    } else if (get_val(*t) < val) {
        (*t)->right = insert(&((*t)->right), val);
    }
    return *t;
}

void print_tree(tree t, int h) {
    if (t != NULL) {
        print_tree(t->right, h + 1);
        for (int i = 0; i < h; i++) {
            printf("\t");
        }
        printf("%f\n", t->val);
        print_tree(t->left, h + 1);
    }
}

int height(tree t) {
    if (tree_is_empty(t)) {
        return 0;
    } else {
        int left_height = height(t->left);
        int right_height = height(t->right);

        return (left_height > right_height) ? left_height + 1 : right_height + 1;
    }
}

int level_width(tree t, int level) {
    if (tree_is_empty(t)) {
        return 0;
    }
    if (level == 1) {
        return 1;
    } else if (level > 1) {
        return level_width(t->left, level - 1) + level_width(t->right, level - 1);
    }
    return 0;
}

bool is_width_monotonic(tree t) {
    int h = height(t);
    for (int i = 2; i <= h; i++) {
        if (level_width(t, i) >= level_width(t, i - 1)) {
            return false;
        }
    }
    return true;
}

tree find_min(tree t) {
    while (!tree_is_empty(get_left(t))) {
        t = get_left(t);
    }
    return t;
}

//tree delete_node(tree t, double val) {
//    if (tree_is_empty(t)) {
//        return t;
//    }
//
//    if(val > t->val){
//        t->right = delete_node(t->right, val);
//    }else if(val < t->val){
//        t->left = delete_node(t->left, val);
//    }else{
//        if(t->left == 0 && t->right == 0){
//            free(t);
//            return NULL;
//        }else if(t->left == 0 || t->right == 0){
//            tree temp;
//            if(t->left == 0){
//                temp = t->right;
//            }else{
//                temp = t->left;
//            }
//            free(t);
//            return temp;
//        }else{
//            tree temp;
//            temp = find_min(t->right);
//            t->val = temp->val;
//            t->right = delete_node(t->right, temp->val);
//        }
//    }
//    return t;
//}


tree delete_node(tree t, double val) {
    if (tree_is_empty(t)) {
        return t;
    }
    if (val < get_val(t)) {
        t->left = delete_node(get_left(t), val);
    } else if (val > get_val(t)) {
        t->right = delete_node(get_right(t), val);
    } else {
        if (tree_is_empty(get_left(t))) {
            tree temp = get_right(t);
            free(t);
            return temp;
        } else if (tree_is_empty(get_right(t))) {
            tree temp = get_left(t);
            free(t);
            return temp;
        }
        tree temp = find_min(get_right(t));
        t->val = get_val(temp);
        t->right = delete_node(get_right(t), get_val(temp));
    }
    return t;
}

int search_val(tree t, double val) {
    if (tree_is_empty(t)) {
        return 0;
    } else if (t->val == val) {
        return 1;
    } else if (t->val < val) {
        if (t->right != 0) {
            search_val(t->right, val);
        } else {
            return 0;
        }
    } else if (t->val > val) {
        if (t->left != 0) {
            search_val(t->left, val);
        } else {
            return 0;
        }
    }
}

void print_menu() {
    printf("\nВыберите действие из списка, написав его номер: \n");
    printf("Введите 0, чтобы выйти.\n");
    printf("Введите 1, чтобы ввести в дерево новый элемент.\n");
    printf("Введите 2 чтобы распечатать дерево.\n");
    printf("Введите 3, чтобы удалить из дерева элемент.\n");
    printf("Введите 4, чтобы проверить, что ширина уровня бинарного дерева монотонно убывает.\n");
}
