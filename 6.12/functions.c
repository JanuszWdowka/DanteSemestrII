//
// Created by root on 5/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


void print_chicken(void){
    printf(" MM\n");
    printf("<' \\___/|\n");
    printf("  \\_  _/\n");
    printf("    ][\n");
}
void print_egg(void){
    printf("  .~~~.\n");
    printf(" /     \\\n");
    printf("(\\/\\/\\/\\)\n");
    printf(" \\     /\n");
    printf("  `~~~`\n");
}
void print_rabbit(void){
    printf(" \\\\   //\n");
    printf("  )\\-/(\n");
    printf("  /o o\\\n");
    printf(" ( =T= )\n");
    printf(" /'---'\\\n");
}

void* easter(int size, void (*funcs1) (void), void (*funcs2) (void), void (*funcs3) (void)){
    if(size < 1 || funcs1 == NULL || funcs2 == NULL || funcs3 == NULL){
        return NULL;
    }
    int x;
    time_t tt;
    srand(time(&tt));
    void (**funcs) (void);
    funcs = malloc(size * sizeof(void (*)(void)));
    if(funcs == NULL){
        return NULL;
    }
    for(int i = 0; i < size; ++i){
        x = rand() % 3;
        if(x == 0){
            *(funcs + i) = funcs1;
        }
        else if(x == 1){
            *(funcs + i) = funcs2;
        }
        else
            *(funcs + i) = funcs3;
    }
    return funcs;
}