//
// Created by root on 6/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_push(struct stack_t **stack, char *value){
    if(stack == NULL || value == NULL)
        return 1;
    struct stack_t *nptr = malloc(1 * sizeof(struct stack_t));
    if(nptr == NULL){
        return 2;
    }
    nptr->sentence = value;
    nptr->prev = *stack;
    *stack = nptr;
    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code){
    if(err_code != NULL){
        *err_code = 0;
    }
    char* x = NULL;
    if (stack == NULL || *stack == NULL || (*stack)->sentence == NULL)
    {
        if(err_code != NULL){
            *err_code = 1;
        }
        return NULL;
    }
    else
    {
        struct stack_t *temp;
        temp = *stack;
        x = (*stack)->sentence;
        *stack = (*stack)->prev;
        free(temp);
    }
    return x;
}

void stack_destroy(struct stack_t** stack){
    if(stack == NULL || *stack == NULL)
        return;
    struct stack_t *temp;
    struct stack_t *tempDel;
    temp = *stack;
    while (temp != NULL)
    {
        tempDel = temp;
        temp = temp->prev;
        free(tempDel->sentence);
        free(tempDel);
    }
    *stack = NULL;
}

int stack_load(struct stack_t **stack, const char *filename){
    if(stack == NULL || *stack != NULL || filename == NULL){
        return 1;
    }
    FILE *file;
    if((file = fopen(filename, "r")) == NULL){
        return 2;
    }
    char znak;
    int position = 0;
    int position2 = 0;
    znak = fgetc(file);
    while(znak != EOF){
        if(znak == '.'){
            position2 = ftell(file);
            char* sentence = NULL;
            sentence = calloc(position2 - position + 1, sizeof(char ));
            if(sentence == NULL){
                stack_destroy(stack);
                fclose(file);
                return 3;
            }
            fseek(file, position, 0);
            int i = 0;
            while (position != position2){
                znak = fgetc(file);
                *(sentence + i) = znak;
                i++;
                position++;
            }
            *(sentence + i) = '\0';
            int res = stack_push(stack, sentence);
            if(res == 2){
                stack_destroy(stack);
                free(sentence);
                fclose(file);
                return 3;
            }
        }
        znak = fgetc(file);
    }
    fclose(file);
    return 0;
}

int stack_save(const struct stack_t *stack, const char *filename){
    if(stack == NULL || filename == NULL || stack->sentence == NULL){
        return 1;
    }
    FILE *file;
    if((file = fopen(filename, "w")) == NULL){
        return 2;
    }
    struct stack_t *temp;
    temp = (struct stack_t*) stack;
    while (temp != NULL)
    {
        fprintf(file, "%s", temp->sentence);
        temp = temp->prev;
    }
    fclose(file);
    return 0;
}
