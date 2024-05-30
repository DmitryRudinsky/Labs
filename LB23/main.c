#include "functions_and_struct.h"

int main() {
    tree t = create_empty_tree();
    print_menu();
    int menu_number;
    while (1) {
        printf("Введите номер меню: ");
        if (scanf("%d", &menu_number) != 1) {
            printf("Ошибка: введите число.\n");
            while (getchar() != '\n');
            continue;
        }
        if (menu_number == 0) {
            printf("Выход из программы...\n");
            destroy(t);
            exit(0);
        }
        switch (menu_number) {
            case 1: {
                double number;
                printf("Введите значение элемента: \n");
                scanf("%lf", &number);
                if (search_val(t, number) == 1) {
                    printf("Такой элемент уже содержится в дереве, попробуйте другой. \n");
                } else {
                    insert(&t, number);
                    printf("Значение элемента успешно добавлено в дерево. \n");
                }
                break;
            }
            case 2: {
                if (!tree_is_empty(t)) {
                    printf("Полученное дерево: \n");
                    print_tree(t, 0);
                } else {
                    printf("Дерево пустое. \n");
                }
                break;
            }
            case 3: {
                if (!tree_is_empty(t)) {
                    double number;
                    printf("Введите элемент, который хотите удалить:\n");
                    scanf("%lf", &number);
                    if (search_val(t, number) == 1) {
                        t = delete_node(t, number);
                        printf("Элемент %lf успешно удалён!\n", number);
                    } else {
                        printf("Такого элемента не содержится в дереве. \n");
                    }
                } else {
                    printf("Я не могу удалить элемент из пустого дерева\n");
                }
                break;
            }
            case 4: {
                if (!tree_is_empty(t)) {
                    if (is_width_monotonic(t)) {
                        printf("Ширина уровня бинарного дерева монотонно убывает.\n");
                    } else {
                        printf("Ширина уровня бинарного дерева не убывает монотонно.\n");
                    }
                } else {
                    printf("Невозможно проверить пустое дерево\n");
                }
                break;
            }
            default:
                printf("Ошибка: Неверный выбор меню. Попробуйте еще раз.\n");
        }
        print_menu();
    }
    return 0;
}