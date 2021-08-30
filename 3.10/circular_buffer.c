#include <stdio.h>
#include <malloc.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N){
    if(a == NULL || N < 1 ){
        return 1;
    }
    a->ptr = (int*) calloc(N, sizeof(int));
    if(a->ptr == NULL){
        return 2;
    }
    a->full = 0;
    a->end = 0;
    a->begin = 0;
    a->capacity = N;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
    if(cb == NULL || N < 1 ){
        return 1;
    }
    *cb = (struct circular_buffer_t*) malloc(sizeof(struct circular_buffer_t));
    if(cb == NULL || *cb == NULL){
        return 2;
    }
    (*cb)->ptr = (int*) calloc(N, sizeof(int));
    if((*cb)->ptr == NULL){
        free(*cb);
        return 2;
    }
    (*cb)->full = 0;
    (*cb)->end = 0;
    (*cb)->begin = 0;
    (*cb)->capacity = N;
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a){
    if(a == NULL){
        return;
    }
    if(a != NULL || a->ptr != NULL){
        free(a->ptr);
    }
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a){
    if(a == NULL){
        return;
    }
    if(a != NULL || (*a)->ptr != NULL){
        free((*a)->ptr);
        free(*a);
    }
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    if(cb == NULL || cb->ptr == NULL || cb->capacity < 1 || cb->full > 2 || cb->begin < 0 || cb->end < 0 || cb->end >= cb->capacity || cb->begin >= cb->capacity){
        return 1;
    }
    *(cb->ptr + cb->end) = value;
    cb->end += 1;
    if(cb->end == cb->capacity){
        cb->end = 0;
    }
    if(cb->end == cb->begin){
        cb->full = 1;
    }
    if(cb->full == 1){
        cb->begin = cb->end;
    }
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
    if(err_code != NULL){
        *err_code = 0;
    }
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->full > 2 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity){
        if(err_code != NULL){
            *err_code = 1;
            return *err_code;
        }
        return 1;
    }
    if(a->begin == a->end && a->full == 0){
        if(err_code != NULL){
            *err_code = 2;
            return *err_code;
        }
        return 2;
    }
    int ToReturn = *(a->ptr + a->begin);
    *(a->ptr + a->begin) = 0;
    a->full = 0;
    a->begin += 1;
    if(a->begin == a->capacity)
        a->begin = 0;
    return ToReturn;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){
    if(err_code != NULL){
        *err_code = 0;
    }
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->full > 2 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity){
        if(err_code != NULL){
            *err_code = 1;
            return *err_code;
        }
        return 1;
    }
    if(a->begin == a->end && a->full == 0){
        if(err_code != NULL){
            *err_code = 2;
            return *err_code;
        }
        return 2;
    }
    if(a->end == 0)
        a->end = a->capacity;
    int ToReturn = *(a->ptr + a->end - 1);
    *(a->ptr + a->end - 1) = 0;
    a->end -= 1;
    a->full = 0;
    return ToReturn;
}

int circular_buffer_empty(const struct circular_buffer_t *a){
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->full > 2 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity){
        return -1;
    }
    if(a->begin == a->end && a->full != 1){
        return 1;
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a){
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->full > 2 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity){
        return -1;
    }
    if(a->begin == a->end && a->full == 1){
        return 1;
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a){
    if(a == NULL || a->ptr == NULL || a->capacity < 1 || a->full > 2 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity){
        return;
    }
    if(a->begin == a->end && a->full == 0){
        return;
    }
    if(a->begin < a->end && a->full == 0){
        for(int i = a->begin; i < a->end; ++i){
            printf("%d ", *(a->ptr + i));
        }
    }
    else if(a->begin > a->end && a->full == 0){
        for(int i = a->begin; i < a->capacity; ++i){
            printf("%d ", *(a->ptr + i));
        }
        for(int i = 0; i < a->end; ++i){
            printf("%d ", *(a->ptr + i));
        }
    }
    else if(a->begin < a->end && a->full == 1){

        for(int i = a->end; i < a->capacity; ++i){
            printf("%d ", *(a->ptr + i));
        }
        for(int i = 0; i < a->end; ++i){
            printf("%d ", *(a->ptr + i));
        }
    }
    else{
        for(int i = a->begin; i < a->capacity; ++i){
            printf("%d ", *(a->ptr + i));
        }
        for(int i = 0; i < a->begin; ++i){
            printf("%d ", *(a->ptr + i));
        }
    }
}
