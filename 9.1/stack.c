//
// Created by root on 6/3/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_init(struct stack_t **stack, int N){
    if(stack == NULL || N < 1){
        return 1;
    }
    *stack = calloc(1, sizeof(struct stack_t));
    if(*stack == NULL)
        return 2;
    (*stack)->head = 0;
    (*stack)->capacity = N;
    (*stack)->data = calloc(N, sizeof(int));
    if((*stack)->data == NULL){
        free(*stack);
        *stack = NULL;
        return 2;
    }
    return 0;
}
int stack_push(struct stack_t *stack, int value){
    if(stack == NULL || stack->head < 0 || stack->capacity < 1 || stack->data == NULL || stack->head > stack->capacity){
        return 1;
    }
    if(stack->capacity > stack->head) {
        *(stack->data + stack->head) = value;
        stack->head += 1;
    }
    else{
        void *newpointer;
        if((newpointer = (int*) realloc(stack->data,(stack->capacity * 2) * sizeof(int))) == NULL){
            return 2;
        }
        else{
            stack->data = newpointer;
            stack->capacity *= 2;
            *(stack->data + stack->head) = value;
            stack->head += 1;
        }
    }
    return 0;
}
int stack_pop(struct stack_t *stack, int *err_code){
    if(err_code != NULL){
        *err_code = 0;
    }
    if(stack == NULL || stack->head < 0 || stack->capacity < 1 || stack->data == NULL || stack->head > stack->capacity){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }
    if(stack->head == 0){
        if(err_code != NULL){
            *err_code = 2;
        }
        return 2;
    }
    int ToReturn = *(stack->data + stack->head - 1);
    *(stack->data + stack->head - 1) = 0;
    stack->head -= 1;
    return ToReturn;
}
void stack_display(const struct stack_t *stack){
    if(stack == NULL || stack->head < 0 || stack->capacity < 1 || stack->data == NULL || stack->head > stack->capacity){
        return;
    }
    for(int i = stack->head - 1; i >= 0; --i){
        printf("%d ", *(stack->data + i));
    }
}
void stack_free(struct stack_t *stack){
    if(stack == NULL){
        return;
    }
    if(stack != NULL || stack->data != NULL){
        free(stack->data);
    }
    free(stack);
}