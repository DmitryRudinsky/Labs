//
// Created by Дима on 17.05.2024.
//
#include "TableStruct.h"
#include "Interface.h"

int main(){
    printf("Программа начинает работу\n");
    Table_handle table = table_init(16);
    char command;
    print_menu();
    while (scanf(" %c", &command) != EOF) {
        switch (command) {
            case 'h': {
                print_menu();
                break;
            }
            case '0':{
                printf("Завершаем программу...");
                destroy_table(table);
                exit(0);
            }
            case '1': {
                double key;
                double value;
                scanf("%lf %lf", &key, &value);
                push_elem(table, key, value);
                break;
            }
            case '2': {
                heapSort(table, table->current_size);
                break;
            }
            case '3': {
                print_table(table);
                break;
            }
            case '4': {
                double key;
                scanf("%lf", &key);
                if(find_elem_by_key(table, key) == -1){
                    printf("Элементов с таким ключём нет\n");
                    break;
                }else{
                    printf("Индекс элемента с ключём %lf: %d\n", key, find_elem_by_key(table, key));
                }
                break;
            }
            default:
                printf("Ошибка: Неверный выбор меню. Попробуйте еще раз.\n");
        }
    }
}