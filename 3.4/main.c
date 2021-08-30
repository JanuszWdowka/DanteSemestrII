#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int create_array_int(int **ptr, int N){
    if(ptr == NULL || N < 1){
        return 1;
    }
    *ptr = calloc(N, sizeof(int));
    if(*ptr == NULL){
        return 2;
    }
    return 0;
}
void destroy_array_int(int **ptr){
    if(ptr != NULL){
        free(*ptr);
        *ptr = NULL;
    }
}

int main() {
    int x = 10;
    int* ptr = &x;
    int** tofunction = &ptr;
    int n;
    int result;
    printf("Podaj rozmiar tablicy: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        return 1;
    }
    if(n < 1){
        printf("Incorrect input data");
        return 2;
    }
    result = create_array_int(tofunction, n);
    if(result == 1){
        printf("Incorrect input");
        return 8;
    }
    else if(result == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < n; ++i){
        if(!scanf("%d", (ptr + i))){
            printf("Incorrect input");
            free(ptr);
            return 1;
        }
    }
    for(int i = n - 1; i > -1; --i){
        printf("%d ", *(ptr + i));
    }
    destroy_array_int(tofunction);
    return 0;
}
