

#include "stdio.h"
#include "queue.h"

int main() {
    printf("Hello world\n");
    Queue_handle q = (Queue_handle) malloc(sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для очереди\n");
        return EXIT_FAILURE;
    }
    init_queue(q);
    char command;
    print_menu();
    while (scanf(" %c", &command) != EOF) {
        switch (command) {
            case 'h': {
                print_menu();
                break;
            }
            case '0': {
                printf("Завершаем программу...");
                destroy_queue(q);
                exit(0);
            }
            case '1': {
                double value;
                scanf("%lf", &value);
                queue_push(q, value);
                break;
            }
            case '2': {
                queue_pop(q);
                break;
            }
            case '3': {
                print_queue(q);
                break;
            }
            case '4': {
                insertion_sort_queue(q);
                break;
            }
            default:
                printf("Ошибка: Неверный выбор меню. Попробуйте еще раз.\n");
        }
    }
}