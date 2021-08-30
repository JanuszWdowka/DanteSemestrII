//
// Created by root on 6/4/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_init(struct stack_t **stack){
    if(stack == NULL){
        return 1;
    }
    *stack = calloc(1, sizeof(struct stack_t));
    if(*stack == NULL)
        return 2;
    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, double value){
    if(stack == NULL)
        return 1;
    struct node_t *nptr = malloc(1 * sizeof(struct node_t));
    if(nptr == NULL){
        return 2;
    }
    nptr->data = value;
    nptr->next = stack->head;
    stack->head = nptr;
    return 0;
}

void stack_display(const struct stack_t* stack){
    if(stack == NULL){
        return;
    }
    struct node_t *temp;
    temp = stack->head;
    while (temp != NULL)
    {
        printf("%f ", temp->data);
        temp = temp->next;
    }
}
double stack_pop(struct stack_t* stack, int *err_code){
    if(err_code != NULL){
        *err_code = 0;
    }
    double x = 0;
    if (stack == NULL || stack->head == NULL)
    {
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }
    else
    {
        struct node_t *temp;
        temp = stack->head;
        x = stack->head->data;
        stack->head = stack->head->next;
        free(temp);
    }
    return x;
}
void stack_destroy(struct stack_t** stack){
    if(stack == NULL || *stack == NULL)
        return;
    struct node_t *temp;
    struct node_t *tempDel;
    temp = (*stack)->head;
    while (temp != NULL)
    {
        tempDel = temp;
        temp = temp->next;
        free(tempDel);
    }
    free(*stack);
}
int stack_empty(const struct stack_t* stack){
    if(stack == NULL)
        return 2;
    if(stack->head == NULL)
        return 1;
    else
        return 0;
}

int stack_size(const struct stack_t* stack){
    if(stack == NULL){
        return -1;
    }
    struct node_t *temp;
    temp = stack->head;
    int x = 0;
    while (temp != NULL)
    {
        x++;
        temp = temp->next;
    }
    return x;
}
