#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

int operations(struct stack_t *stos);
double oblicz(char c, double a, double b);

int main() {
    int res;
    struct stack_t* stos;
    res = stack_init(&stos);
    if(res != 0){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter expression: ");
    int x = operations(stos);
    if(x == 1){
        printf("Incorrect input");
        stack_destroy(&stos);
        return 1;
    }
    else if(x == 2){
        printf("Incorrect expression");
        stack_destroy(&stos);
        return 2;
    }
    else if(x == 3){
        printf("Failed to allocate memory");
        stack_destroy(&stos);
        return 8;
    }
    if(stack_size(stos) != 1){
        printf("Incorrect expression");
        stack_destroy(&stos);
        return 2;
    }
    printf("%f", stos->head->data);
    stack_destroy(&stos);
    return 0;
}

int operations(struct stack_t *stos){
    double a = 0;
    double b = 0;
    char c = 0;
    int error = 0;
    int res = 0;
    char lastchar = 0;
    while ((c = getchar()) != '\n') {
        if (isdigit(c)){
            if(isdigit(lastchar)){
                a = stack_pop(stos, &error);
                stack_push(stos, oblicz('*', a, 10));
                a = stack_pop(stos, &error);
                if(a >= 0)
                    stack_push(stos, oblicz('+', a, (double)(c - '0')));
                else
                    stack_push(stos, oblicz('+', a, (double)((c - '0') * (-1))));
            }
            else{
                if(lastchar != '-')
                    res = stack_push(stos, (double)(c - '0'));
                else
                    res = stack_push(stos, (double)((c - '0') * (-1)));
                if(res == 2){
                    return 3;
                }
            }
        }
        else if (c == '+' || c == '*' || c == '/'){
            if (stack_size(stos) < 2)
                return 2;
            b = stack_pop(stos, &error);
            a = stack_pop(stos, &error);
            stack_push(stos, oblicz(c, a, b));
        }
        else if(c == ' '){
            if(lastchar == '-'){
                if (stack_size(stos) < 2)
                    return 2;
                b = stack_pop(stos, &error);
                a = stack_pop(stos, &error);
                stack_push(stos, oblicz(lastchar, a, b));
            }
            lastchar = ' ';
            continue;
        }
        else if(c != '-'){
            return 1;
        }
        lastchar = c;
    }
    if(lastchar == '-'){
        if (stack_size(stos) < 2)
            return 2;
        b = stack_pop(stos, &error);
        a = stack_pop(stos, &error);
        stack_push(stos, oblicz(lastchar, a, b));
    }
    return 0;
}

double oblicz(char c, double a, double b){
    switch(c) {
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return a + b;
    }
}

