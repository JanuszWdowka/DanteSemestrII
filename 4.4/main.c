#include <stdio.h>
#include <malloc.h>

struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

int main() {
    struct matrix_t matrix;
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
    result = matrix_create(&matrix, width, height);
    if(result == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    else if(result == 1){
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj liczby: ");
    result = matrix_read(&matrix);
    if(result == 2){
        printf("Incorrect input");
        return 1;
    }
    matrix_display(&matrix);
    matrix_destroy(&matrix);
    return 0;
}

int matrix_create(struct matrix_t *m, int width, int height){
    if(height < 1 || width < 1 || m == NULL){
        return 1;
    }
    if(m == NULL){
        return 2;
    }
    m->ptr = (int**) malloc(height * sizeof(int*));
    if(m->ptr == NULL){
        return 2;
    }
    for(int i = 0; i < height; ++i){
        *(m->ptr + i) = (int*) malloc(width * sizeof(int));
        if(*(m->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(m->ptr + j));
            }
            free(m->ptr);
            return 2;
        }
    }
    m->height = height;
    m->width = width;
    return 0;
}
int matrix_read(struct matrix_t *m){
    if(m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1){
        return 1;
    }
    for(int i = 0; i < m->height; ++i){
        for(int j = 0; j < m->width; ++j){
            if(!scanf("%d", (*(m->ptr + i) + j))){
                matrix_destroy(m);
                return 2;
            }
        }
    }
    return 0;
}
void matrix_display(const struct matrix_t *m){
    if(m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1){
        return;
    }
    for(int i = 0; i < m->height; ++i){
        for(int j = 0; j < m->width; ++j){
            printf("%d ", *(*(m->ptr + i) + j));
        }
        printf("\n");
    }
}
void matrix_destroy(struct matrix_t *m){
    if(m == NULL){
        return;
    }
    for(int i = 0; i < m->height; ++i){
        free(*(m->ptr + i));
    }
    free(m->ptr);
}