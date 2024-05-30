//
// Created by Дима on 13.05.2024.
//

#include "bidirectional-with-barrier-element.h"

int main(void) {
    printf("Программа начинает работу\n");
    bdBarList_handle l = bdBarList_init(100);
    char command;
    open_menu();
    while (scanf(" %c", &command) != EOF) {
        switch (command) {
            case 'h': {
                open_menu();
                break;
            }
            case '1': {
                double val;
                int pos;
                scanf("%lf %d", &val, &pos);
                insert(l, pos, val);
                break;
            }
            case '2': {
                int pos;
                scanf("%d", &pos);
                removeEl(l, pos);
                break;
            }
            case '3': {
                print_list(l);
                break;
            }
            case '4': {
                int k;
                scanf("%d", &k);
                del_every_kth(l, k);
                break;
            }
            default:
                printf("Ошибка: Неверный выбор меню. Попробуйте еще раз.\n");
        }
    }
}

