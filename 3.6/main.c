#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array.h"

int main() {
    struct array_t tab;
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
    result = array_create(&tab, n);
    if(result == 1){
        printf("Incorrect input");
        return 1;
    }
    else if(result == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    while (true){
        if(!scanf("%d", &value)){
            printf("Incorrect input");
            array_destroy(&tab);
            return 1;
        }
        if(value == 0){
            break;
        }
        else if(tab.size < tab.capacity)
            array_push_back(&tab, value);
    }
    if(tab.size == tab.capacity){
        printf("Buffer is full\n");
        array_display(&tab);
    }
    else if(tab.size == 0){
        printf("Buffer is empty");
    }
    else
        array_display(&tab);
    array_destroy(&tab);
    return 0;
}

