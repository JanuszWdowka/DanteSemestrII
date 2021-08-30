#include <stdio.h>
#include "circular_buffer.h"

int main() {
    struct circular_buffer_t* circular;
    struct circular_buffer_t** pCircular = &circular;
    int n = 0;
    int result;
    int value = 0;
    printf("Podaj rozmiar bufora: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        return 1;
    }
    if(n < 1){
        printf("Incorrect input data");
        return 2;
    }
    result = circular_buffer_create_struct(pCircular, n);
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
    int error = 0;
    while (WhatToDo != 0){
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf("Co chcesz zrobic: ");
        if(!scanf("%d", &WhatToDo)){
            printf("Incorrect input");
            circular_buffer_destroy_struct(pCircular);
            return 1;
        }
        switch (WhatToDo) {
            case 1:
                printf("Podaj liczbe ");
                if(!scanf("%d", &value)){
                    printf("Incorrect input");
                    circular_buffer_destroy_struct(pCircular);
                    return 1;
                }
                circular_buffer_push_back(circular, value);
                break;
            case 2:
                result = circular_buffer_pop_back(circular, &error);
                if(error == 2){
                    printf("Buffer is empty\n");
                }
                else
                    printf("%d\n", result);
                break;
            case 3:
                result = circular_buffer_pop_front(circular, &error);
                if(error == 2){
                    printf("Buffer is empty\n");
                }
                else
                    printf("%d\n", result);
                break;
            case 4:
                if(circular_buffer_empty(circular)){
                    printf("Buffer is empty\n");
                }
                else{
                    circular_buffer_display(circular);
                    printf("\n");
                }
                break;
            case 5:
                printf("%d\n", circular_buffer_empty(circular));
                break;
            case 6:
                printf("%d\n", circular_buffer_full(circular));
                break;
            case 0:
                break;
            default:
                printf("Incorrect input data");
                printf("\n");
                break;
        }
    }

    circular_buffer_destroy_struct(pCircular);
    return 0;
}
