#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <malloc.h>

char* concatenate(int howMany, ...);

int main() {
    int n;
    char** txt;
    char* res = NULL;
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
                free(*(txt + j));
            }
            free(txt);
            return 8;
        }
    }
    printf("Podaj liczbe tekstow do wprowadzenia: ");
    if(!scanf("%d", &n)){
        printf("Incorrect input");
        for(int i = 0; i < 4; ++i)
            free(*(txt + i));
        free(txt);
        return 1;
    }
    if(n < 2 || n > 4){
        printf("Incorrect input data");
        for(int i = 0; i < 4; ++i)
            free(*(txt + i));
        free(txt);
        return 2;
    }
    printf("Podaj teksty: ");
    for(int i = 0; i < n; ++i){
        while ( getchar() != '\n');
        scanf("%1000[^\n]s", *(txt + i));
    }

    if(n == 2)
        res = concatenate(n, *(txt + 0), *(txt + 1));
    else if(n == 3)
        res = concatenate(n, *(txt + 0), *(txt + 1), *(txt + 2));
    else
        res = concatenate(n, *(txt + 0), *(txt + 1), *(txt + 2), *(txt + 3));
    if(res == NULL){
        printf("Failed to allocate memory");
        for(int j = 0; j < 4; ++j){
            free(*(txt + j));
        }
        free(txt);
        return 8;
    }
    printf("%s", res);
    for(int i = 0; i < 4; ++i)
        free(*(txt + i));
    free(txt);
    free(res);
    return 0;
}

char* concatenate(int howMany, ...){
    if(howMany < 1){
        return NULL;
    }
    char* res;
    va_list valist;
    va_start(valist, howMany);
    int leght = 0;
    char* txt;
    for (int i = 0; i < howMany; i++) {
        txt = va_arg(valist, char*);
        leght += (int)strlen(txt);
    }
    leght += howMany;
    va_end(valist);

    res = malloc(leght * sizeof(char));
    if(res == NULL){
        return NULL;
    }
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
    return res;
}
