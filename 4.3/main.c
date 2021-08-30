#include <stdio.h>
#include <malloc.h>

int **create_array_2d(int width, int height);
void display_array_2d(int **ptr, int width, int height);
void destroy_array_2d(int ***ptr, int height);
int create_array_2d_2(int ***ptr, int width, int height);
int sum_array_2d(int **ptr, int width, int height);
int sum_row(int *ptr, int width);

int main() {
    int** ptr = NULL;
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
    result = create_array_2d_2(&ptr, width, height);
    if(result == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    else if(result == 1){
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj liczby: ");
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(!scanf("%d", (*(ptr + i) + j))){
                printf("Incorrect input");
                destroy_array_2d(&ptr, height);
                return 1;
            }
        }
    }
    display_array_2d(ptr, width, height);
    for(int i = 0; i < height; ++i){
        printf("%d\n", sum_row(*(ptr + i), width));
    }
    printf("%d", sum_array_2d(ptr, width, height));
    destroy_array_2d(&ptr, height);
    return 0;
}

int **create_array_2d(int width, int height){
    if(height < 1 || width < 1){
        return NULL;
    }
    int** ptr = NULL;
    ptr = (int**) malloc(height * sizeof(int*));
    if(ptr == NULL){
        return NULL;
    }
    for(int i = 0; i < height; ++i){
        *(ptr + i) = (int*) malloc(width * sizeof(int));
        if(*(ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(ptr + j));
            }
            free(ptr);
            return NULL;
        }
    }
    return ptr;
}
void display_array_2d(int **ptr, int width, int height){
    if(height < 1 || width < 1 || ptr == NULL){
        return;
    }
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            printf("%d ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}
void destroy_array_2d(int ***ptr, int height){
    if(height < 1 || ptr == NULL){
        return;
    }
    for(int i = 0; i < height; ++i){
        free(*(*ptr + i));
    }
    free(*ptr);
    *ptr = NULL;
}

int create_array_2d_2(int ***ptr, int width, int height){
    if(height < 1 || width < 1 || ptr == NULL){
        return 1;
    }
    *ptr = (int**) malloc(height * sizeof(int*));
    if(*ptr == NULL){
        return 2;
    }
    for(int i = 0; i < height; ++i){
        *(*ptr + i) = (int*) malloc(width * sizeof(int));
        if(*(*ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(*ptr + j));
            }
            free(*ptr);
            return 2;
        }
    }
    return 0;
}

int sum_array_2d(int **ptr, int width, int height){
    if(ptr == NULL || width < 1 || height < 1){
        return -1;
    }
    int sum = 0;
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            sum += *(*(ptr + i) + j);
        }
    }
    return sum;
}

int sum_row(int *ptr, int width){
    if(ptr == NULL || width < 1){
        return -1;
    }
    int sum = 0;
    for(int i = 0; i < width; ++i){
        sum += *(ptr + i);
    }
    return sum;
}