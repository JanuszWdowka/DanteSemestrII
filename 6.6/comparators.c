#include <stdlib.h>
#include "comparators.h"

int comp_int(int a, int b){
    if(a > b)
        return 1;
    else if(b > a)
        return -1;
    else
        return 0;
}
int comp_int_abs(int a, int b){
    if(abs(a) > abs(b))
        return 1;
    else if(abs(b) > abs(a))
        return -1;
    else
        return 0;
}
int comp_int_length(int a, int b){
    int x = 0;
    int y = 0;
    while (a != 0){
        x++;
        a = a / 10;
    }
    while (b != 0){
        y++;
        b = b / 10;
    }
    if(x > y)
        return 1;
    else if(y > x)
        return -1;
    else
        return 0;
}
int comp_int_digits_sum(int a, int b){
    int x = 0;
    int y = 0;
    a = abs(a);
    b = abs(b);
    while (a != 0){
        x += a % 10;
        a = a / 10;
    }
    while (b != 0){
        y += b % 10;
        b = b / 10;
    }
    if(x > y)
        return 1;
    else if(y > x)
        return -1;
    else
        return 0;
}

int sort_int(int* ptr, int lenght, int (*fun)(int, int)){
    if(ptr == NULL || lenght < 1 || fun == NULL)
        return 1;
    int tmp;
    for(int i = 0; i < lenght; i++) {
        for (int j = 1; j < lenght - i; j++) {
            if ((fun(*(ptr + j - 1), *(ptr + j))) == 1) {
                tmp = *(ptr + j);
                *(ptr + j) = *(ptr + j - 1);
                *(ptr + j - 1) = tmp;
            }
        }
    }
    return 0;
}