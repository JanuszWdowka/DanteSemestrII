#include <stdio.h>
#include "stack.h"

int main() {
    struct stack_t* stos;
    int res;
    int whatToDo = 1;
    int error = 0;
    int value;
    res = stack_init(&stos);
    if(res != 0){
        printf("Failed to allocate memory");
        return 8;
    }
    while (whatToDo != 0){
        printf("Co chcesz zrobic? ");
        if(!scanf("%d", &whatToDo)){
            printf("Incorrect input");
            stack_destroy(&stos);
            return 1;
        }
        switch (whatToDo) {
            case 0:
                break;
            case 1:
                printf("Podaj liczbe ");
                if(!scanf("%d", &value)){
                    printf("Incorrect input");
                    stack_destroy(&stos);
                    return 1;
                }
                res = stack_push(stos, value);
                if(res == 2){
                    printf("Failed to allocate memory");
                    stack_destroy(&stos);
                    return 8;
                }
                break;
            case 2:
                res = stack_pop(stos, &error);
                if(error == 1){
                    printf("Stack is empty\n");
                }
                else
                    printf("%d\n", res);
                break;
            case 3:
                printf("%d\n", stack_empty(stos));
                break;
            case 4:
                if(stos->head == 0){
                    printf("Stack is empty\n");
                }
                else{
                    stack_display(stos);
                    printf("\n");
                }
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    }
    stack_destroy(&stos);
    return 0;
}
