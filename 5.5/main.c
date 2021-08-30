#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_numbers.h"

int main() {
    struct big_numbers_t* arr;
    char* num;
    int res;
    int lenght = 0;
    res = create_big_numbers(&arr, 10);
    if(res == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    num = calloc(201, sizeof(char));
    if(num == NULL){
        destroy_big_numbers(&arr);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < 10; ++i){

        fgets(num, 201 * sizeof(char), stdin);
        if (*num == '\n'){
            break;
        }

        lenght = strlen(num);
        if(lenght == 200){
            if(*(num + lenght - 1) != '\n'){
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }
            }
        }
        else
            *(num + lenght - 1) = '\0';
        res = add_big_number(arr, num);
        if(res == 2){
            printf("Failed to allocate memory\n");
            break;
        }
        if(res == 1){
            printf("Incorrect input\n");
            --i;
        }
    }
    if(arr->size == 10){
        printf("Buffer is full\n");
    }
    if(arr->size == 0){
        printf("Buffer is empty");
    }
    display(arr);
    destroy_big_numbers(&arr);
    free(num);
    return 0;
}
