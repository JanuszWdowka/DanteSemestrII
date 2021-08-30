#include <stdio.h>
#include <malloc.h>
#include "matrix_utils.h"


int main() {
    struct matrix_t* matrix;
    int width;
    int height;
    int result;

    printf("Podaj szerokość i wysokość: ");
    if(!scanf("%d", &width)){
        printf("Incorrect input");
        return 1;
    }
    if(!scanf("%d", &height)){
        printf("Incorrect input");
        return 1;
    }
    if(height < 1 || width < 1){
        printf("Incorrect input data");
        return 2;
    }
    matrix = matrix_create_struct(width, height);
    if(matrix == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    result = matrix_read(matrix);
    if(result == 2){
        free(matrix);
        printf("Incorrect input");
        return 1;
    }
    char* name = (char*) calloc(40, sizeof(char));
    if(name == NULL){
        matrix_destroy_struct(&matrix);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj sciezke do pliku:\n");
    scanf("%39s", name);
    struct matrix_t* m2;
    m2 = matrix_transpose(matrix);
    if(m2 == NULL){
        matrix_destroy_struct(&matrix);
        free(name);
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < 40; ++i){
        if(*(name + i) == '\0') {
            if (*(name + i - 4) == '.' && *(name + i - 3) == 't' && *(name + i - 2) == 'x' && *(name + i - 1) == 't') {
                result = matrix_save_t(m2, name);
                if (result == 1 || result == 2 || result == 3) {
                    matrix_destroy_struct(&matrix);
                    matrix_destroy_struct(&m2);
                    free(name);
                    printf("Couldn't create file");
                    return 5;
                } else {
                    printf("File saved");
                }
                break;
            }
            else if (*(name + i - 4) == '.' && *(name + i - 3) == 'b' && *(name + i - 2) == 'i' &&
                     *(name + i - 1) == 'n') {
                result = matrix_save_b(m2, name);
                if (result == 1 || result == 2 || result == 3) {
                    matrix_destroy_struct(&matrix);
                    matrix_destroy_struct(&m2);
                    free(name);
                    printf("Couldn't create file");
                    return 5;
                } else {
                    printf("File saved");
                }
                break;
            }
            else {
                matrix_destroy_struct(&matrix);
                matrix_destroy_struct(&m2);
                free(name);
                printf("Unsupported file format");
                return 7;
            }
        }
    }
    free(name);
    matrix_destroy_struct(&m2);
    matrix_destroy_struct(&matrix);
    return 0;
}

