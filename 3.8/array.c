#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int array_create_struct(struct array_t **a, int N){
    if(a == NULL || N < 1 ){
        return 1;
    }
    *a = (struct array_t*) malloc(sizeof(struct array_t));
    if(a == NULL || *a == NULL){
        return 2;
    }
    (*a)->ptr = (int*) calloc(N, sizeof(int));
    if((*a)->ptr == NULL){
        free(*a);
        return 2;
    }
    (*a)->size = 0;
    (*a)->capacity = N;
    return 0;
}
void array_destroy_struct(struct array_t **a){
    if(a == NULL){
        return;
    }
    if(a != NULL || (*a)->ptr != NULL){
        free((*a)->ptr);
        free(*a);
    }
}
int array_remove_item(struct array_t *a, int value){
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->capacity < a->size || a->size < 0){
        return -1;
    }
    int x = 0;
    for(int i = 0; i < a->size; ++i){
        if(*(a->ptr + i) == value){
            a->size -= 1;
            for(int j = i; j < a->size; ++j){
                *(a->ptr + j) = *(a->ptr + j + 1);
            }
            x++;
            --i;
        }
    }
    return x;
}

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