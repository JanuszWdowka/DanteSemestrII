#include <stdio.h>
#include <stdarg.h>


int stats(int *sum, float *avg, int num,...) ;


int main() {
    int n;
    int sum = 0;
    float avg = 0;
    int tab[3];
    for(int i = 0; i < 3; ++i){
        tab[i] = 0;
    }
    printf("Enter number of elements: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        return 1;
    }
    if(n < 1 || n > 3){
        printf("Incorrect input data");
        return 2;
    }
    printf("Enter numbers: ");
    for(int i = 0; i < n; ++i){
        if(!scanf("%d", (tab + i))){
            printf("Incorrect input");
            return 1;
        }
    }
    if(n == 1)
        stats(&sum, &avg, n, tab[0]);
    else if(n == 2)
        stats(&sum, &avg, n, tab[0], tab[1]);
    else
        stats(&sum, &avg, n, tab[0], tab[1], tab[2]);
    printf("%d %f", sum, avg);
    return 0;
}

int stats(int *sum, float *avg, int num,...)  {
    if(sum == NULL || avg == NULL){
        return 1;
    }
    va_list valist;
    *sum = 0;
    *avg = 0;
    if(num < 1){
        return 1;
    }
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
        *sum += va_arg(valist, int);
    }
    va_end(valist);
    *avg = *sum / (float)num;
    return 0;
}