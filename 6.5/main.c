#include <stdio.h>
#include <stdlib.h>
#include "char_operations.h"


typedef char operations(char);
int main() {
    char* txt;
    char* new_txt = NULL;
    operations *funcs[4] = {lower_to_upper, upper_to_lower, space_to_dash, reverse_letter};
    int option;
    txt = malloc(1001 * sizeof(char));
    if(txt == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj tekst: ");
    scanf("%1000[^\n]s", txt);
    while ( getchar() != '\n' );
    printf("Podaj rodzaj operacji: ");
    if(!scanf("%d", &option)){
        printf("Incorrect input");
        free(txt);
        return 1;
    }
    if(option < 0 || option > 3){
        printf("Incorrect input data");
        free(txt);
        return 2;
    }
    new_txt = letter_modifier(txt, *(funcs + option));
    if(new_txt == NULL){
        printf("Failed to allocate memory");
        free(txt);
        return 8;
    }
    printf("%s", new_txt);
    free(txt);
    free(new_txt);
    return 0;
}
