//
// Created by root on 6/3/21.
//

#ifndef INC_9_1_STACK_H
#define INC_9_1_STACK_H

struct stack_t
{
    int head;
    int capacity;
    int *data;
};

int stack_init(struct stack_t **stack, int N);
int stack_push(struct stack_t *stack, int value);
int stack_pop(struct stack_t *stack, int *err_code);
void stack_display(const struct stack_t *stack);
void stack_free(struct stack_t *stack);

#endif //INC_9_1_STACK_H
