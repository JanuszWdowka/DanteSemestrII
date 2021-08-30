#include <stdio.h>
#include <malloc.h>
#include "comparators.h"


typedef int operations(int a, int b);
int main() {
    int (**funcs) (int, int);
    int lenght;
    int* tab;
    int operation;
    funcs = malloc(4 * sizeof(int (*)(int,int)));
    if(funcs == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    *(funcs + 0) = comp_int;
    *(funcs + 1) = comp_int_abs;
    *(funcs + 2) = comp_int_length;
    *(funcs + 3) = comp_int_digits_sum;

    printf("Podaj długość tablicy: ");
    if(!scanf("%d", &lenght)){
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if(lenght < 1){
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }
    tab = (int*) malloc(lenght * sizeof(int));
    if(tab == NULL){
        free(funcs);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < lenght; ++i){
        if(!scanf("%d", (tab + i))){
            printf("Incorrect input");
            free(tab);
            free(funcs);
            return 1;
        }
    }
    printf("Podaj rodzaj operacji: ");
    if(!scanf("%d", &operation)){
        printf("Incorrect input");
        free(tab);
        free(funcs);
        return 1;
    }
    if(operation < 0 || operation > 3){
        printf("Incorrect input data");
        free(funcs);
        free(tab);
        return 2;
    }
    sort_int(tab, lenght, *(funcs + operation));
    for(int i = 0; i < lenght; ++i){
        printf("%d ", *(tab + i));
    }
    free(funcs);
    free(tab);
    return 0;
}
