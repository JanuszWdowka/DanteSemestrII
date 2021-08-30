#include <stdio.h>
#include <malloc.h>
#include "functions.h"

int main() {
    int size;
    printf("Podaj liczbe funkcji do wygenerowania: ");
    if(!scanf("%d", &size)){
        printf("Incorrect input");
        return 1;
    }
    if(size < 1){
        printf("Incorrect input data");
        return 2;
    }
    void (**funcs)(void) = easter(size, print_chicken, print_egg, print_rabbit);
    if(funcs == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < size; i++){
        (*(funcs + i))();
        printf("\n");
    }
    free(funcs);
    return 0;
}
