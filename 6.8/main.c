#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "comparators.h"

int main() {
    int lenght;
    int type;
    size_t data_type;
    printf("Enter data type: ");
    if(!scanf("%d", &type)){
        printf("Incorrect input");
        return 1;
    }
    if(type == 0){
        data_type = sizeof(int);
    }
    else if(type == 1){
        data_type = sizeof(double);
    }
    else
        data_type = sizeof(struct point_t);

    printf("Enter array size: ");
    if(!scanf("%d", &lenght)){
        printf("Incorrect input");
        return 1;
    }
    if(lenght < 1){
        printf("Incorrect input data");
        return 2;
    }

    if(type == 0){
        int* tab;
        tab = (int*) malloc(lenght * data_type);
        if(tab == NULL){
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Enter ints: ");
        for(int i = 0; i < lenght; ++i){
            if(!scanf("%d", (tab + i))){
                printf("Incorrect input");
                free(tab);
                return 1;
            }
        }
        sort(tab, lenght, data_type, comp_int);
        for(int i = 0; i < lenght; ++i){
            printf("%d ", *(tab + i));
        }
        free(tab);
    }
    else if(type == 1){
        double * tab;
        tab = (double *) malloc(lenght * data_type);
        if(tab == NULL){
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Enter doubles: ");
        for(int i = 0; i < lenght; ++i){
            if(!scanf("%lf", (tab + i))){
                printf("Incorrect input");
                free(tab);
                return 1;
            }
        }
        sort(tab, lenght, data_type, comp_double);
        for(int i = 0; i < lenght; ++i){
            printf("%lf ", *(tab + i));
        }
        free(tab);
    }
    else{
        struct point_t* tab;
        tab = (struct point_t*) malloc(lenght * data_type);
        if(tab == NULL){
            printf("Failed to allocate memory");
            return 8;
        }
        printf("Enter pointers: ");
        for(int i = 0; i < lenght; ++i){
            if(!scanf("%lf", &(tab + i)->x)){
                printf("Incorrect input");
                free(tab);
                return 1;
            }
            if(!scanf("%lf", &(tab + i)->y)){
                printf("Incorrect input");
                free(tab);
                return 1;
            }
        }
        sort(tab, lenght, data_type, comp_point);
        for(int i = 0; i < lenght; ++i){
            printf("%lf %lf\n", (tab + i)->x, (tab + i)->y);
        }
        free(tab);
    }
    return 0;
}
