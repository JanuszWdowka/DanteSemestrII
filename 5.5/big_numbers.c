//
// Created by root on 5/26/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_numbers.h"


int create(struct big_numbers_t *bn, int capacity){
    if(bn == NULL || capacity < 1){
        return 1;
    }
    bn->capacity = capacity;
    bn->size = 0;
    bn->big_number = calloc(capacity, sizeof(char*));
    if(bn->big_number == NULL){
        return 2;
    }
    return  0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity){
    if(bn == NULL || capacity < 1){
        return 1;
    }
    *bn = calloc(1, sizeof(struct big_numbers_t));
    if(*bn == NULL){
        *bn = NULL;
        return 2;
    }
    (*bn)->capacity = capacity;
    (*bn)->size = 0;
    (*bn)->big_number = calloc(capacity, sizeof(char*));
    if((*bn)->big_number == NULL){
        free(*bn);
        *bn = NULL;
        return 2;
    }
    return 0;
}

void destroy(struct big_numbers_t *bn){
    if(bn == NULL || bn->capacity < 1 || bn->size < 0)
        return;
    if(bn != NULL || bn->big_number != NULL){
        for(int i = 0; i < bn->size; ++i){
            if(*(bn->big_number + i) != NULL){
                free(*(bn->big_number + i));
            }
        }
        free(bn->big_number);
    }
    return;
}

void destroy_big_numbers(struct big_numbers_t **bn){
    if(bn == NULL || *bn == NULL || (*bn)->big_number == NULL || (*bn)->capacity < 1 || (*bn)->size < 0 || (*bn)->size > (*bn)->capacity)
        return;
    for(int i = 0; i < (*bn)->size; ++i){
        free(*((*bn)->big_number + i));
    }
    free((*bn)->big_number);
    free(*bn);
    *bn = NULL;
    return;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number){
    if(bn == NULL || big_number == NULL || bn->big_number == NULL || bn->capacity < 1 || bn->size < 0){
        return 1;
    }
    if(validate(big_number) != 0){
        return 1;
    }
    if(bn->capacity == bn->size){
        return 3;
    }
    int lenght = strlen(big_number);
    *(bn->big_number + bn->size) = calloc(lenght + 1, sizeof(char));
    if(*(bn->big_number + bn->size) == NULL)
        return 2;
    for(int i = 0; *(big_number + i) != '\0'; ++i){
        *(*(bn->big_number + bn->size) + i) = *(big_number + i);
    }
    *(*(bn->big_number + bn->size) + lenght) = '\0';
    bn->size += 1;
    return 0;
}

void display(const struct big_numbers_t *bn){
    if(bn == NULL || bn->big_number == NULL || bn->capacity < 1 || bn->size < 0 || bn->size > bn->capacity)
        return;

    for(int i = 0; i < bn->size; ++i){
        if(validate(*(bn->big_number + i)) != 0){
            return;
        }
    }
    for(int i = 0; i < bn->size; ++i){
        printf("%s\n", *(bn->big_number + i));
    }
    return;
}

int validate(const char *number){
    if(number == NULL){
        return -1;
    }
    char buf;
    int x = 0;
    int i = 0;
    if(*(number + 0) == '\0' || (*(number + 0) == '0' && *(number + 1) != '\0') || (*(number + 0) == '-' && *(number + 1) == '\0'))
        return 2;
    while (*(number + i) != '\0'){
        buf = *(number + i);
        if((buf < 48 || buf > 57) && buf != 45){
            return 2;
        }
        if(buf == 45 && x == 0){
            x = -1;
        }
        else if(buf == 45 && x == -1){
            return 2;
        }
        ++i;
    }
    return 0;
}