#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int array_create(struct array_t *a, int N){
    if(a == NULL || N < 1 ){
        return 1;
    }
    a->ptr = (int*) calloc(N, sizeof(int));
    if(a->ptr == NULL){
        return 2;
    }
    a->size = 0;
    a->capacity = N;
    return 0;
}
int array_push_back(struct array_t *a, int value){
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->capacity < a->size || a->size < 0){
        return 1;
    }
    if(a->capacity > a->size) {
        *(a->ptr + a->size) = value;
        a->size += 1;
    }
    else
        return 2;
    return 0;
}
void array_display(const struct array_t *a){
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->capacity < a->size || a->size < 1){
        return;
    }
    for(int i = 0; i < a->size; ++i){
        printf("%d ", *(a->ptr + i));
    }
}
void array_destroy(struct array_t *a){
    if(a == NULL){
        return;
    }
    if(a != NULL || a->ptr != NULL){
        free(a->ptr);
    }
}
