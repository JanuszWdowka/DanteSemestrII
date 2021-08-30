//
// Created by root on 4/26/21.
//

#include <stdio.h>
#include <malloc.h>
#include "matrix_utils.h"

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

struct matrix_t* matrix_create_struct(int width, int height){
    if(height < 1 || width < 1){
        return NULL;
    }
    struct matrix_t* m;
    m = (struct matrix_t*) malloc(1 * sizeof(struct matrix_t));
    if(m == NULL){
        return NULL;
    }
    m->ptr = (int**) malloc(height * sizeof(int*));
    if(m->ptr == NULL){
        free(m);
        return NULL;
    }
    for(int i = 0; i < height; ++i){
        *(m->ptr + i) = (int*) malloc(width * sizeof(int));
        if(*(m->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(m->ptr + j));
            }
            free(m->ptr);
            free(m);
            return NULL;
        }
    }
    m->width = width;
    m->height = height;
    return m;
}

void matrix_destroy_struct(struct matrix_t **m){
    if(m == NULL){
        return;
    }
    for(int i = 0; i < (*m)->height; ++i){
        free(*((*m)->ptr + i));
    }
    free((*m)->ptr);
    free(*m);
    *m = NULL;
    m = NULL;
}

struct matrix_t* matrix_transpose(const struct matrix_t *m){
    if(m == NULL || m->height < 1 || m->width < 1 || m->ptr == NULL){
        return NULL;
    }
    struct matrix_t* m2;
    m2 = (struct matrix_t*) malloc(1 * sizeof(struct matrix_t));
    if(m2 == NULL){
        return NULL;
    }
    m2->height = m->width;
    m2->width = m->height;
    m2->ptr = (int**) malloc(m2->height * sizeof(int*));
    if(m2->ptr == NULL){
        free(m2);
        return NULL;
    }
    for(int i = 0; i < m2->height; ++i){
        *(m2->ptr + i) = (int*) malloc(m2->width * sizeof(int));
        if(*(m2->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(m2->ptr + j));
            }
            free(m2->ptr);
            free(m2);
            return NULL;
        }
    }

    for(int i = 0; i < m->height; ++i){
        for(int j = 0; j < m->width; ++j){
            *(*(m2->ptr + j) + i) = *(*(m->ptr + i) + j);
        }
    }
    return  m2;
}

int matrix_save_b(const struct matrix_t *m, const char *filename){
    FILE *file;
    if(filename == NULL || m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1){
        return 1;
    }
    if((file = fopen(filename, "wb")) == NULL){
        return 2;
    }
    if(fwrite(&(m->width), sizeof(int), 1, file) == 0){
        fclose(file);
        return 3;
    }
    if(fwrite(&(m->height), sizeof(int), 1, file) == 0){
        fclose(file);
        return 3;
    }
    for(int i = 0; i < m->height; ++i){
        for(int j = 0; j < m->width; ++j){
            if(fwrite((*(m->ptr + i) + j), sizeof(int), 1, file) == 0){
                fclose(file);
                return 3;
            }
        }
    }
    fclose(file);
    return 0;
}
int matrix_save_t(const struct matrix_t *m, const char *filename){
    FILE *file;
    int size = 0;
    if(filename == NULL || m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1){
        return 1;
    }
    if((file = fopen(filename, "w")) == NULL){
        return 2;
    }
    size = fprintf(file, "%d %d", m->width, m->height);
    if(size < 2){
        fclose(file);
        return 3;
    }
    fprintf(file,"\n");
    for(int i = 0; i < m->height; ++i){
        for(int j = 0; j < m->width; ++j){
            if(!fprintf(file, "%d ", *(*(m->ptr + i) + j))){
                fclose(file);
                return 3;
            }
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}