#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float* ptr = (float*)calloc(1, sizeof(float));
    if(ptr == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    *ptr = M_PI;
    printf("%f %p", *ptr, ( void * )ptr);
    free(ptr);
    return 0;
}
