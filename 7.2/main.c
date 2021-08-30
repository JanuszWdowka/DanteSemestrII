#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

int concatenate(char* res, int size, int howMany, ...);

int main() {
    int n;
    char** txt;
    char* res;
    txt = malloc(4 * sizeof(char*));
    if(txt == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < 4; ++i){
        *(txt + i) = malloc(1001 * sizeof(char));
        if(*(txt + i) == NULL){
            printf("Failed to allocate memory");
            for(int j = 0; j < i; ++j){
                free(*(txt + i));
            }
            free(txt);
            return 8;
        }
    }
    res = malloc(4004 * sizeof(char));
    if(res == NULL){
        printf("Failed to allocate memory");
        for(int i = 0; i < 4; ++i)
            free(*(txt + i));
        free(txt);
        return 8;
    }
    printf("Podaj liczbe tekstow do wprowadzenia: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        for(int i = 0; i < 4; ++i)
            free(*(txt + i));
        free(txt);
        free(res);
        return 1;
    }
    if(n < 2 || n > 4){
        printf("Incorrect input data");
        for(int i = 0; i < 4; ++i)
            free(*(txt + i));
        free(txt);
        free(res);
        return 2;
    }
    printf("Podaj teksty: ");
    for(int i = 0; i < n; ++i){
        while ( getchar() != '\n');
        scanf("%1000[^\n]s", *(txt + i));
    }

    if(n == 2)
        concatenate(res, 4004, n, *(txt + 0), *(txt + 1));
    else if(n == 3)
        concatenate(res, 4004, n, *(txt + 0), *(txt + 1), *(txt + 2));
    else
        concatenate(res, 4004, n, *(txt + 0), *(txt + 1), *(txt + 2), *(txt + 3));
    printf("%s", res);
    for(int i = 0; i < 4; ++i)
        free(*(txt + i));
    free(txt);
    free(res);
    return 0;
}

int concatenate(char* res, int size, int howMany, ...){
    if(res == NULL || size < 2 || howMany < 1){
        return 1;
    }
    va_list valist;
    va_start(valist, howMany);
    int leght = 0;
    char* txt;
    for (int i = 0; i < howMany; i++) {
        txt = va_arg(valist, char*);
        leght += (int)strlen(txt);
    }
    leght += howMany;
    if(leght > size)
        return 2;
    va_end(valist);
    va_start(valist, howMany);
    int x = howMany;
    *res = '\0';
    for (int i = 0; i < howMany; i++) {
        txt = va_arg(valist, char*);
        strcat(res, txt);
        if(x > 1){
            strcat(res, " ");
            --x;
        }
    }
    *(res + leght - 1) = '\0';
    va_end(valist);
    return 0;
}