#include <stdio.h>
#include <stdlib.h>
#include <math.h>



float* create_array(int N){
    float* ptr;
    if(N < 1){
        return NULL;
    }
    ptr = (float *)calloc(N, sizeof(float ));
    if(ptr == NULL){
        return NULL;
    }
    return ptr;
}

int main() {
    float* ptr;
    int n;
    printf("Podaj rozmiar tablicy: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        return 1;
    }
    if(n < 1){
        printf("Incorrect input data");
        return 2;
    }
    if((ptr = create_array(n)) == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < n; ++i){
        if(!scanf("%f", (ptr + i))){
            printf("Incorrect input");
            free(ptr);
            return 1;
        }
    }
    for(int i = n - 1; i > -1; --i){
        printf("%f ", *(ptr + i));
    }
    free(ptr);
    return 0;
}
