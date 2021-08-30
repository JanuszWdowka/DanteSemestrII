#include <stdio.h>
#include "int_operations.h"


typedef int operations(int a, int b);
int main() {
    operations *fun[4] = {add_int, sub_int, div_int, mul_int};
    int a, b;
    int type;
    printf("Enter numbers: ");
    if(!scanf("%d", &a)){
        printf("Incorrect input");
        return 1;
    }
    if(!scanf("%d", &b)){
        printf("Incorrect input");
        return 1;
    }
    printf("Choose an operation: ");
    if(!scanf("%d", &type)){
        printf("Incorrect input");
        return 1;
    }
    if(type < 0 || type > 3){
        printf("Incorrect input data");
        return 2;
    }
    int result;
    result = (*(fun + type))(a, b);
    printf("Result: %d", result);
    return 0;
}
