
#include <string.h>
#include <malloc.h>
#include "comparators.h"

int comp_int(const void * a, const void * b){
    if(a == NULL || b == NULL){
        return 0;
    }
    if(*((int *) a)  > *((int *) b))
        return 1;
    else if(*((int *) b) > *((int *) a))
        return -1;
    else
        return 0;
}
int comp_double(const void * a, const void * b){
    if(a == NULL || b == NULL){
        return 0;
    }
    if(*((double *) a) > *((double *) b))
        return 1;
    else if(*((double *) b) > *((double *) a))
        return -1;
    else
        return 0;
}
int comp_point(const void * a, const void * b){
    if(a == NULL || b == NULL){
        return 0;
    }
    if((*((struct point_t*) a)).x > (*((struct point_t*) b)).x)
        return 1;
    else if((*((struct point_t*) b)).x > (*((struct point_t*) a)).x)
        return -1;
    else{
        if((*((struct point_t*) a)).y > (*((struct point_t*) b)).y)
            return 1;
        else if((*((struct point_t*) b)).y > (*((struct point_t*) a)).y)
            return -1;
    }
    return 0;
}
int sort(void* ptr, int size, size_t sizeo, int comparator(const void *ptr1, const void *ptr2)){
    if(ptr == NULL || comparator == NULL || size < 1){
        return 1;
    }
    char *bound = ((char *) ptr) + (size * sizeo);
    char *p = malloc(sizeo);
    if(p == NULL){
        return 1;
    }


    for (char *element1 = ptr; element1 < (bound - sizeo); element1 += sizeo) {
        for (char *element2 = element1 + sizeo; element2 < bound; element2 += sizeo) {
            if (comparator(element1, element2) > 0) {
                memcpy(p, element1, sizeo);
                memcpy(element1, element2, sizeo);
                memcpy(element2, p, sizeo);
            }
        }
    }
    free(p);
    return 0;
}