#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "big_numbers.h"

int main() {
    char* name;
    struct big_numbers_t* bn;
    int res;
    char c;
    char* sum;
    const char* extension = "_sorted";
    name = calloc(31, sizeof(char));
    if(name == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pliku: ");
    scanf("%30s", name);
    while ((c = getchar()) != '\n' && c != EOF) { }
    res = load_big_numbers_b(&bn, name);
    if(res == 2){
        free(name);
        printf("Failed to allocate memory");
        return 8;
    }
    else if(res == 3){
        free(name);
        printf("Couldn't open file");
        return 4;
    }
    else if(res == 4){
        free(name);
        printf("File corrupted");
        return 7;
    }
    sort_big_numbers_asc(bn);
    char* zaq;
    zaq = (char*) calloc(100, sizeof(char));
    if(zaq == NULL){
        free(name);
        destroy_big_numbers(&bn);
        printf("Failed to allocate memory");
        return 8;
    }
    int n = 0;
    for(int i = strlen(name) - 1; i > 0; --i){
        if(*(name + i) == '.'){
            n = i;
            break;
        }
    }
    if(n == 0)
        n = strlen(name);
    strncpy(zaq, name, n);
    *(zaq + n) = '\0';
    strcat(zaq, extension);
    strcat(zaq, name + n);
    res = save_big_numbers_b(bn, zaq);
    if(res == 1 || res == 2){
        printf("Couldn't create file\n");
    }
    else
        printf("File saved\n");
    sum = total_sum_big_numbers(bn, &res);
    if(res != 0){
        printf("Error");
        free(zaq);
        free(name);
        destroy_big_numbers(&bn);
    }
    else{
        printf("%s", sum);
        free(zaq);
        free(name);
        free(sum);
        destroy_big_numbers(&bn);
    }
    return 0;
}
