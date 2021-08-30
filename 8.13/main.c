#include <stdio.h>
#include <stdint.h>
#include "functions.h"

int main() {
    int data_type = 0;
    unsigned int a = 0;
    unsigned short b = 0;
    unsigned long c = 0;
    int setUp = 0;
    int notSet = 0;

    printf("Enter data type: ");
    if(!scanf("%d", &data_type)){
        printf("Incorrect input");
        return 1;
    }
    if(data_type == 0){
        printf("Enter number: ");
        if(!scanf("%u", &a)){
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(a, &setUp, &notSet);
        printf("%d\n%d\n", setUp, notSet);
        DISPLAY_BITS(a);
        printf("\n");
        REVERSE_BITS(&a);
        DISPLAY_BITS(a);
    }
    else if(data_type == 1){
        printf("Enter number: ");
        if(!scanf("%hu", &b)){
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(b, &setUp, &notSet);
        printf("%d\n%d\n", setUp, notSet);
        DISPLAY_BITS(b);
        printf("\n");
        REVERSE_BITS(&b);
        DISPLAY_BITS(b);
    }
    else if(data_type == 2){
        printf("Enter number: ");
        if(!scanf("%lu", &c)){
            printf("Incorrect input");
            return 1;
        }
        COUNT_BITS(c, &setUp, &notSet);
        printf("%d\n%d\n", setUp, notSet);
        DISPLAY_BITS(c);
        printf("\n");
        REVERSE_BITS(&c);
        DISPLAY_BITS(c);
    }
    else{
        printf("Incorrect input data");
        return 2;
    }
    return 0;
}
