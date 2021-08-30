#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array.h"

int main() {
    struct array_t* tab;
    struct array_t** pTab = &tab;
    int n = 0;
    int result;
    int value = 0;
    printf("Podaj rozmiar tablicy: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        return 1;
    }
    if(n < 1){
        printf("Incorrect input data");
        return 2;
    }
    result = array_create_struct(pTab, n);
    if(result == 1){
        printf("Incorrect input");
        return 1;
    }
    else if(result == 2){
        printf("Failed to allocate memory");
        return 8;
    }

    int WhatToDo = 1;
    int c;
    while (WhatToDo != 0){
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf("Co chcesz zrobic: ");
        if(!scanf("%d", &WhatToDo)){
            printf("Incorrect input");
            array_destroy_struct(pTab);
            return 1;
        }
        switch (WhatToDo) {
            case 1:
                printf("Podaj kolejne liczby, które mają zostać dodane do tablicy: ");
                while (tab->size < n){
                    if(!scanf("%d", &value)){
                        printf("Incorrect input");
                        array_destroy_struct(pTab);
                        return 1;
                    }
                    if(value == 0){
                        break;
                    }
                    else if(tab->size < tab->capacity)
                        array_push_back(tab, value);
                }
                if(tab->size == tab->capacity){
                    printf("Buffer is full\n");
                    array_display(tab);
                    printf("\n");
                }
                else if(tab->size == 0){
                    printf("Buffer is empty");
                    printf("\n");
                }
                else{
                    array_display(tab);
                    printf("\n");
                }
                break;
            case 2:
                printf("Podaj kolejne liczby, które mają zostać usuniete z tablicy: ");
                while (true){
                    if(!scanf("%d", &value)){
                        printf("Incorrect input");
                        array_destroy_struct(pTab);
                        return 1;
                    }
                    if(value == 0){
                        break;
                    }
                    array_remove_item(tab, value);
                }
                if(tab->size == 0){
                    printf("Buffer is empty");
                    printf("\n");
                }
                else{
                    array_display(tab);
                    printf("\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Incorrect input data");
                printf("\n");
                break;
        }
    }
    array_destroy_struct(pTab);
    return 0;
}

