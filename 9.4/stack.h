//
// Created by root on 6/6/21.
//

#ifndef INC_9_4_STACK_H
#define INC_9_4_STACK_H

struct stack_t
{
    char *sentence;
    struct stack_t *prev;
};

int stack_push(struct stack_t **stack, char *value);
char *stack_pop(struct stack_t **stack, int *err_code);
void stack_destroy(struct stack_t **stack);
int stack_load(struct stack_t **stack, const char *filename);
int stack_save(const struct stack_t *stack, const char *filename);

#endif //INC_9_4_STACK_H
