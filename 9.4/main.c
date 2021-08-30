#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Not enough arguments");
        return 9;
    }
    int i = 1;
    while (i < argc){
        struct stack_t* stos = NULL;
        int res = 0;
        res = stack_load(&stos, *(argv + i));
        if(res == 2){
            printf("Couldn't open file %s\n", *(argv + i));
        }
        else if(res == 3){
            printf("Failed to allocate memory");
            return 8;
        }
        else{
            res = stack_save(stos, *(argv + i));
            if(res == 2){
                printf("Couldn't create file");
                stack_destroy(&stos);
                return 5;
            }
            else{
                printf("File %s saved\n", *(argv + i));
            }
        }
        stack_destroy(&stos);
        ++i;
    }
    return 0;
}
