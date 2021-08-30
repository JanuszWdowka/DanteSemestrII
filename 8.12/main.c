#include <stdio.h>
#include "functions.h"

int main() {
    int data_type;
    float  c, d;
    int a, b;

    printf("Enter data type: ");
    if(!scanf("%d", &data_type)){
        printf("Incorrect input");
        return 1;
    }
    if(data_type == 0){
        printf("Enter numbers: ");
        if(!scanf("%d", &a)){
            printf("Incorrect input");
            return 1;
        }
        if(!scanf("%d", &b)){
            printf("Incorrect input");
            return 1;
        }
        printf("%d\n %d\n %d\n %d", SQR(a), SQR(b), MAX(a, b), MIN(a, b));
    }
    else if(data_type == 1){
        printf("Enter numbers: ");
        if(!scanf("%f", &c)){
            printf("Incorrect input");
            return 1;
        }
        if(!scanf("%f", &d)){
            printf("Incorrect input");
            return 1;
        }
        printf("%f\n %f\n %f\n %f", SQR(c), SQR(d), MAX(c, d), MIN(c, d));
    }
    else{
        printf("Incorrect input data");
        return 2;
    }
    return 0;
}
