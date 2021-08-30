//
// Created by root on 4/28/21.
//

#include <stdio.h>
#include <bits/types/FILE.h>
#include <malloc.h>
#include "image_utils.h"

struct image_t* load_image_t(const char *filename, int *err_code){
    FILE *file;
    int size = 0;
    if(err_code != NULL){
        *err_code = 0;
    }
    if(filename == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return NULL;
    }
    if((file = fopen(filename, "r")) == NULL){
        if(err_code != NULL){
            *err_code = 2;
        }
        return NULL;
    }
    struct image_t* image;
    image = (struct image_t*) malloc(1 * sizeof(struct image_t));
    if(image == NULL){
        if(err_code != NULL){
            *err_code = 4;
        }
        fclose(file);
        return NULL;
    }
    fgets(image->type, 3, file);
    if(*(image->type + 0) != 'P' || *(image->type + 1) != '2'){
        if(err_code != NULL){
            *err_code = 3;
        }
        fclose(file);
        free(image);
        return NULL;
    }
    size = fscanf(file, "%d %d", &image->width, &image->height);
    if(size < 2){
        if(err_code != NULL){
            *err_code = 3;
        }
        free(image);
        fclose(file);
        return NULL;
    }
    if(image->width < 1 || image->height < 1){
        if(err_code != NULL){
            *err_code = 3;
        }
        free(image);
        fclose(file);
        return NULL;
    }
    if(!fscanf(file, "%d", &size)){
        if(err_code != NULL){
            *err_code = 3;
        }
        free(image);
        fclose(file);
        return NULL;
    }
    if(size != 255){
        if(err_code != NULL){
            *err_code = 3;
        }
        free(image);
        fclose(file);
        return NULL;
    }
    image->ptr = (int**) malloc(image->height * sizeof(int*));
    if(image->ptr == NULL){
        if(err_code != NULL){
            *err_code = 4;
        }
        fclose(file);
        free(image);
        return NULL;
    }
    for(int i = 0; i < image->height; ++i){
        *(image->ptr + i) = (int*) malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(image->ptr + j));
            }
            if(err_code != NULL){
                *err_code = 4;
            }
            fclose(file);
            free(image->ptr);
            free(image);
            return NULL;
        }
    }
    for(int i = 0; i < image->height; ++i){
        for(int j = 0; j < image->width; ++j){
            size = fscanf(file,"%d ",(*(image->ptr + i) + j));
            if(size < 1){
                destroy_image(&image);
                fclose(file);
                if(err_code != NULL){
                    *err_code = 3;
                }
                return NULL;
            }
            if(*(*(image->ptr + i) + j) < 0){
                destroy_image(&image);
                fclose(file);
                if(err_code != NULL){
                    *err_code = 3;
                }
                return NULL;
            }
        }
    }
    fclose(file);
    return image;
}

int save_image_t(const char * filename, const struct image_t *m1){
    FILE *file;
    int size = 0;
    if(filename == NULL || m1 == NULL || m1->ptr == NULL || m1->width < 1 || m1->height < 1){
        return 1;
    }
    if(*(m1->type + 0) != 'P' || *(m1->type + 1) != '2'){
        return 1;
    }
    if((file = fopen(filename, "w")) == NULL){
        return 2;
    }
    for(int i = 0; i < 2; ++i){
        if(!fprintf(file, "%c", *(m1->type + i))){
            fclose(file);
            return 3;
        }
    }
    fprintf(file,"\n");
    size = fprintf(file, "%d %d", m1->width, m1->height);
    if(size < 2){
        fclose(file);
        return 3;
    }
    fprintf(file,"\n");
    fprintf(file,"255");
    fprintf(file,"\n");
    for(int i = 0; i < m1->height; ++i){
        for(int j = 0; j < m1->width; ++j){
            if(!fprintf(file, "%d ", *(*(m1->ptr + i) + j))){
                fclose(file);
                return 3;
            }
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}

void destroy_image(struct image_t **m){
    if(m == NULL){
        return;
    }
    for(int i = 0; i < (*m)->height; ++i){
        free(*((*m)->ptr + i));
    }
    free((*m)->type);
    free((*m)->ptr);
    *m = NULL;
    m = NULL;
}

struct image_t* image_flip_horizontal(const struct image_t *m1){
    if(m1 == NULL || m1->ptr == NULL || m1->width < 1 || m1->height < 1){
        return NULL;
    }
    if(*(m1->type + 0) != 'P' || *(m1->type + 1) != '2'){
        return NULL;
    }
    struct image_t* image;
    image = (struct image_t*) malloc(1 * sizeof(struct image_t));
    if(image == NULL){
        return NULL;
    }
    *(image->type + 0) = *(m1->type + 0);
    *(image->type + 1) = *(m1->type + 1);
    *(image->type + 2) = *(m1->type + 2);
    image->height = m1->height;
    image->width = m1->width;
    image->ptr = (int**) malloc(image->height * sizeof(int*));
    if(image->ptr == NULL){
        free(image);
        return NULL;
    }
    for(int i = 0; i < image->height; ++i){
        *(image->ptr + i) = (int*) malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(image->ptr + j));
            }
            free(image->ptr);
            free(image);
            return NULL;
        }
    }

    for(int i = m1->height - 1, k = 0; i >= 0; --i, ++k){
        for(int j = 0; j < m1->width; ++j){
            *(*(image->ptr + k) + j) = *(*(m1->ptr + i) + j);
        }
    }
    return image;
}
struct image_t* image_flip_vertical(const struct image_t *m1){
    if(m1 == NULL || m1->ptr == NULL || m1->width < 1 || m1->height < 1){
        return NULL;
    }
    if(*(m1->type + 0) != 'P' || *(m1->type + 1) != '2'){
        return NULL;
    }
    struct image_t* image;
    image = (struct image_t*) malloc(1 * sizeof(struct image_t));
    if(image == NULL){
        return NULL;
    }
    *(image->type + 0) = *(m1->type + 0);
    *(image->type + 1) = *(m1->type + 1);
    *(image->type + 2) = *(m1->type + 2);
    image->height = m1->height;
    image->width = m1->width;
    image->ptr = (int**) malloc(image->height * sizeof(int*));
    if(image->ptr == NULL){
        free(image);
        return NULL;
    }
    for(int i = 0; i < image->height; ++i){
        *(image->ptr + i) = (int*) malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(image->ptr + j));
            }
            free(image->ptr);
            free(image);
            return NULL;
        }
    }

    for(int i = 0; i < m1->height; ++i){
        for(int j = m1->width - 1, k = 0; j >= 0; --j, ++k){
            *(*(image->ptr + i) + k) = *(*(m1->ptr + i) + j);
        }
    }
    return image;
}
struct image_t* image_negate(const struct image_t *m1){
    if(m1 == NULL || m1->ptr == NULL || m1->width < 1 || m1->height < 1){
        return NULL;
    }
    if(*(m1->type + 0) != 'P' || *(m1->type + 1) != '2'){
        return NULL;
    }
    struct image_t* image;
    image = (struct image_t*) malloc(1 * sizeof(struct image_t));
    if(image == NULL){
        return NULL;
    }
    *(image->type + 0) = *(m1->type + 0);
    *(image->type + 1) = *(m1->type + 1);
    *(image->type + 2) = *(m1->type + 2);
    image->height = m1->height;
    image->width = m1->width;
    image->ptr = (int**) malloc(image->height * sizeof(int*));
    if(image->ptr == NULL){
        free(image);
        return NULL;
    }
    for(int i = 0; i < image->height; ++i){
        *(image->ptr + i) = (int*) malloc(image->width * sizeof(int));
        if(*(image->ptr + i) == NULL){
            for(int j = 0; j < i; ++j){
                free(*(image->ptr + j));
            }
            free(image->ptr);
            free(image);
            return NULL;
        }
    }

    for(int i = 0; i < m1->height; ++i){
        for(int j = 0; j < m1->width; ++j){
            *(*(image->ptr + i) + j) = 255 - *(*(m1->ptr + i) + j);
        }
    }
    return image;
}

const int* image_get_pixel(const struct image_t *img, int x, int y){
    if(img == NULL || img->ptr == NULL || img->width < 1 || img->height < 1){
        return NULL;
    }
    if(*(img->type + 0) != 'P' || *(img->type + 1) != '2'){
        return NULL;
    }
    if(x < 0 || y < 0){
        return NULL;
    }
    if(x >= img->width || y >= img->height){
        return NULL;
    }
    return  (*(img->ptr + y) + x);

}
int* image_set_pixel(struct image_t *img, int x, int y){
    if(img == NULL || img->ptr == NULL || img->width < 1 || img->height < 1){
        return NULL;
    }
    if(*(img->type + 0) != 'P' || *(img->type + 1) != '2'){
        return NULL;
    }
    if(x < 0 || y < 0){
        return NULL;
    }
    if(x >= img->width || y >= img->height){
        return NULL;
    }
    return  (*(img->ptr + y) + x);
}

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value){
    if(img == NULL || img->ptr == NULL || img->width < 1 || img->height < 1 || rect == NULL || rect->p.x < 0 || rect->p.y < 0 || rect->width < 1 || rect->height < 1 || value > 255 || value < 0){
        return 1;
    }
    if(*(img->type + 0) != 'P' || *(img->type + 1) != '2'){
        return 1;
    }
    if(rect->p.x >= img->width || rect->p.y >= img->height){
        return 1;
    }

    if(rect->width > img->width || rect->height > img->height){
        return 1;
    }

    if(rect->p.x + rect->width > img->width || rect->p.y + rect->height > img->height){
        return 1;
    }

    for(int j = rect->p.x; j < img->width && j < rect->p.x + rect->width; ++j){
        *(*(img->ptr + rect->p.y) + j) = value;
    }

    for(int j = rect->p.x; j < img->width && j < rect->p.x + rect->width; ++j){
        *(*(img->ptr + rect->p.y + rect->height - 1) + j) = value;
    }

    for(int i = rect->p.y; i < img->height && i < rect->p.y + rect->height; ++i){
        *(*(img->ptr + i) + rect->p.x) = value;
    }

    for(int i = rect->p.y; i < img->height && i < rect->p.y + rect->height; ++i){
        *(*(img->ptr + i) + rect->p.x + rect->width - 1) = value;
    }
    return 0;
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty){
    if(img == NULL || img->ptr == NULL || img->width < 1 || img->height < 1 || src == NULL || src->ptr == NULL || src->width < 1 || src->height < 1 || desty < 0 || destx < 0){
        return 1;
    }
    if(*(img->type + 0) != 'P' || *(img->type + 1) != '2'){
        return 1;
    }
    if(*(src->type + 0) != 'P' || *(src->type + 1) != '2'){
        return 1;
    }

    if(src->width > img->width || src->height > img->height){
        return 1;
    }
    if(destx + src->width > img->width || desty + src->height > img->height){
        return 1;
    }
    for(int i = 0; i < src->height; ++i){
        for(int j = 0; j < src->width; ++j){
            if(*(*(src->ptr + i) + j) < 0){
                return 1;
            }
        }
    }
    for(int i = desty, k = 0; k < src->height; ++i, ++k){
        for(int j = destx, l = 0; l < src->width; ++j, ++l){
            *(*(img->ptr + i) + j) = *(*(src->ptr + k) + l);
        }
    }
    return 0;
}