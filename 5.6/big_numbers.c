//
// Created by root on 5/27/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_numbers.h"


int create(struct big_numbers_t *bn, int capacity){
    if(bn == NULL || capacity < 1){
        return 1;
    }
    bn->capacity = capacity;
    bn->size = 0;
    bn->big_number = calloc(capacity, sizeof(char*));
    if(bn->big_number == NULL){
        return 2;
    }
    return  0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity){
    if(bn == NULL || capacity < 1){
        return 1;
    }
    *bn = calloc(1, sizeof(struct big_numbers_t));
    if(*bn == NULL){
        *bn = NULL;
        return 2;
    }
    (*bn)->capacity = capacity;
    (*bn)->size = 0;
    (*bn)->big_number = calloc(capacity, sizeof(char*));
    if((*bn)->big_number == NULL){
        free(*bn);
        *bn = NULL;
        return 2;
    }
    return 0;
}

void destroy(struct big_numbers_t *bn){
    if(bn == NULL || bn->capacity < 1 || bn->size < 0)
        return;
    if(bn != NULL || bn->big_number != NULL){
        for(int i = 0; i < bn->size; ++i){
            if(*(bn->big_number + i) != NULL){
                free(*(bn->big_number + i));
            }
        }
        free(bn->big_number);
    }
    return;
}

void destroy_big_numbers(struct big_numbers_t **bn){
    if(bn == NULL || *bn == NULL || (*bn)->big_number == NULL || (*bn)->capacity < 1 || (*bn)->size < 0 || (*bn)->size > (*bn)->capacity)
        return;
    for(int i = 0; i < (*bn)->size; ++i){
        free(*((*bn)->big_number + i));
    }
    free((*bn)->big_number);
    free(*bn);
    *bn = NULL;
    return;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number){
    if(bn == NULL || big_number == NULL || bn->big_number == NULL || bn->capacity < 1 || bn->size < 0){
        return 1;
    }
    if(validate(big_number) != 0){
        return 1;
    }
    if(bn->capacity == bn->size){
        return 3;
    }
    int lenght = strlen(big_number);
    *(bn->big_number + bn->size) = calloc(lenght + 1, sizeof(char));
    if(*(bn->big_number + bn->size) == NULL)
        return 2;
    for(int i = 0; *(big_number + i) != '\0'; ++i){
        *(*(bn->big_number + bn->size) + i) = *(big_number + i);
    }
    *(*(bn->big_number + bn->size) + lenght) = '\0';
    bn->size += 1;
    return 0;
}

void display(const struct big_numbers_t *bn){
    if(bn == NULL || bn->big_number == NULL || bn->capacity < 1 || bn->size < 0 || bn->size > bn->capacity)
        return;

    for(int i = 0; i < bn->size; ++i){
        if(validate(*(bn->big_number + i)) != 0){
            return;
        }
    }
    for(int i = 0; i < bn->size; ++i){
        printf("%s\n", *(bn->big_number + i));
    }
    return;
}

int save_big_numbers_b(const struct big_numbers_t *bn, const char *filename){
    if(bn == NULL || filename == NULL || bn->size < 1 || bn->capacity < 1 || bn->size > bn->capacity || bn->big_number == NULL){
        return 1;
    }

    for(int i = 0; i < bn->size; ++i){
        if(validate(*(bn->big_number + i)) != 0){
            return 1;
        }
    }

    FILE *file;

    if((file = fopen(filename, "wb")) == NULL){
        return 2;
    }
    if(fwrite(&(bn->size), sizeof(int), 1, file) == 0){
        fclose(file);
        return 1;
    }
    for(int i = 0; i < bn->size; ++i){

        int str = strlen(*(bn->big_number + i));
        if(fwrite(&str, sizeof(int), 1, file) == 0){
            fclose(file);
            return 1;
        }
        if(fwrite(*(bn->big_number + i), str * sizeof(char), 1, file) == 0){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int load_big_numbers_b(struct big_numbers_t **bn, const char *filename){
    FILE *file;
    int res = 0;
    int size = 0;
    char c = 0;
    if(filename == NULL || bn == NULL){
        return 1;
    }
    *bn = calloc(1, sizeof(struct big_numbers_t));
    if(*bn == NULL){
        *bn = NULL;
        return 2;
    }
    if((file = fopen(filename, "rb")) == NULL){
        free(*bn);
        *bn = NULL;
        return 3;
    }


    res = fread(&size, sizeof(int), 1, file);
    if(res == 0){
        free(*bn);
        *bn = NULL;
        fclose(file);
        return 4;
    }
    if(size <= 0){
        free(*bn);
        *bn = NULL;
        fclose(file);
        return 4;
    }
    (*bn)->capacity = size;
    (*bn)->size = size;
    (*bn)->big_number = calloc(size, sizeof(char*));
    if((*bn)->big_number == NULL){
        free(*bn);
        *bn = NULL;
        fclose(file);
        return 2;
    }
    for(int i = 0; i < (*bn)->size; ++i){
        res = fread(&size, sizeof(int), 1, file);
        if(res == 0){
            /*for(int z = 0; z < i; ++z){
                free(*((*bn)->big_number + z));
            }
            free((*bn)->big_number);
            free(*bn);
            *bn = NULL;*/
            (*bn)->size = i;
            destroy_big_numbers(bn);
            fclose(file);
            return 4;
        }
        if(size <= 0){
            (*bn)->size = i;
            destroy_big_numbers(bn);
            fclose(file);
            return 4;
        }
        *((*bn)->big_number + i) = calloc(size + 1, sizeof(char));
        if(*((*bn)->big_number + i) == NULL){
            (*bn)->size = i;
            destroy_big_numbers(bn);
            fclose(file);
            return 2;
        }
        for(int j = 0; j < size; ++j){
            res = fread(&c, sizeof(c), 1, file);
            if(res == 0){
                (*bn)->size = i + 1;
                destroy_big_numbers(bn);
                fclose(file);
                return 4;
            }
            if(c <= 0){
                (*bn)->size = i + 1;
                destroy_big_numbers(bn);
                fclose(file);
                return 4;
            }
            *(*((*bn)->big_number + i) + j) = c;
        }
    }
    for(int i = 0; i < (*bn)->size; ++i){
        if(validate(*((*bn)->big_number + i)) != 0){
            destroy_big_numbers(bn);
            fclose(file);
            return 4;
        }
    }
    fclose(file);
    return 0;
}

int sort_big_numbers_asc(struct big_numbers_t *bn){
    if(bn == NULL || bn->size < 1 || bn->capacity < 1 || bn->size > bn->capacity || bn->big_number == NULL){
        return 1;
    }
    for(int i = 0; i < bn->size; ++i){
        if(validate(*(bn->big_number + i)) != 0){
            return 1;
        }
    }
    qsort(bn->big_number, bn->size, sizeof(char*), compare1);
    return 0;
}

char* total_sum_big_numbers(const struct big_numbers_t *bn, int *err_code){
    if(bn == NULL || bn->size < 1 || bn->capacity < 1 || bn->size > bn->capacity || bn->big_number == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return NULL;
    }
    for(int i = 0; i < bn->size; ++i){
        if(validate(*(bn->big_number + i)) != 0){
            if(err_code != NULL){
                *err_code = 2;
            }
            return NULL;
        }
    }
    if(err_code != NULL){
        *err_code = 0;
    }
    char * result1;
    char * result2;
    int x;
    if(bn->size == 1){
        int str = strlen(*(bn->big_number + 0));
        result1 = calloc(str + 1, sizeof(char));
        if(result1 == NULL){
            if(err_code != NULL){
                *err_code = 3;
            }
            return NULL;
        }
        int i;
        for(i = 0; i < str; ++i){
            *(result1 + i) = *(*(bn->big_number + 0) + i);
        }
        *(result1 + i) = '\0';
        return result1;
    }
    else if(bn->size == 2){
        x = add(*(bn->big_number + 0), *(bn->big_number + 1), &result1);
        if(x != 0){
            if(err_code != NULL){
                *err_code = 3;
            }
            return NULL;
        }
        return result1;
    }
    x = add(*(bn->big_number + 0), *(bn->big_number + 1), &result1);
    if(x != 0){
        if(err_code != NULL){
            *err_code = 3;
        }
        return NULL;
    }
    x = add(result1, *(bn->big_number + 2), &result2);
    if(x != 0){
        if(err_code != NULL){
            *err_code = 3;
        }
        return NULL;
    }
    int i;
    for(i = 3; i < bn->size; ++i){
        if(i % 2 == 0){
            free(result2);
            x = add(result1, *(bn->big_number + i), &result2);
            if(x != 0){
                if(err_code != NULL){
                    *err_code = 3;
                }
                free(result1);
                return NULL;
            }
        }
        else{
            free(result1);
            x = add(result2, *(bn->big_number + i), &result1);
            if(x != 0){
                if(err_code != NULL){
                    *err_code = 3;
                }
                free(result2);
                return NULL;
            }
        }
    }
    if(i % 2 == 0){
        free(result2);
        return result1;
    }
    else{
        free(result1);
        return result2;
    }
}

int validate(const char *number){
    if(number == NULL){
        return -1;
    }
    char buf;
    int x = 0;
    int i = 0;
    if(*(number + 0) == '\0' || (*(number + 0) == '0' && *(number + 1) != '\0') || (*(number + 0) == '-' && *(number + 1) == '\0'))
        return 2;
    while (*(number + i) != '\0'){
        buf = *(number + i);
        if((buf < 48 || buf > 57) && buf != 45){
            return 2;
        }
        if(buf == 45 && x == 0){
            x = -1;
        }
        else if(buf == 45 && x == -1){
            return 2;
        }
        ++i;
    }
    return 0;
}

int compare(const char* number1, const char* number2){
    if(number1 == NULL || number2 == NULL)
        return 2;
    if(validate(number1) == 2 || validate(number2) == 2)
        return 3;
    if(*(number1 + 0) == '-' && *(number2 + 0) != '-')
        return -1;
    if(*(number1 + 0) != '-' && *(number2 + 0) == '-')
        return 1;
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    if(lenght1 > lenght2){
        if(*(number1 + 0) != '-' && *(number2 + 0) != '-')
            return 1;
        else
            return -1;
    }
    if(lenght2 > lenght1){
        if(*(number1 + 0) != '-' && *(number2 + 0) != '-')
            return -1;
        else
            return 1;
    }

    int a;
    int b;
    int i = 0, j = 0;
    if(*(number1 + 0) != '-' && *(number2 + 0) != '-'){
        while (lenght1 > i && lenght2 > j){
            a = (int)*(number1 + i);
            b = (int)*(number2 + j);
            a -= 48;
            b -= 48;
            if(a > b)
                return 1;
            if(b > a)
                return -1;
            ++i;
            ++j;
        }
    }
    else{
        ++i; ++j;
        while (lenght1 > i && lenght2 > j){
            a = (int)*(number1 + i);
            b = (int)*(number2 + j);
            a -= 48;
            b -= 48;
            if(a < b)
                return 1;
            if(b < a)
                return -1;
            ++i;
            ++j;
        }
    }
    return 0;
}

int compare1(const void * number1, const void * number2){
    int res = compare(*(const char **) number1, *(const char **) number2);
    return res;
}

int subtract(const char* number1, const char* number2, char** result){
    if(number1 == NULL || number2 == NULL || result == NULL){
        return 1;
    }
    if(validate(number1) == 2 || validate(number2) == 2)
        return 2;
    if(*(number2 + 0) != '-' && *(number1 + 0) == '-'){
        int r = add(number1 + 1, number2, result);
        if(r == 0){
            int lenght = strlen(*result);
            if((*(number1 + 1) - 48 + *(number2 + 0) - 48 ) >= 10){
                void *newpointer;
                if((newpointer = (char*) realloc(*result,(lenght + 2) * sizeof(char)))  == NULL){
                    free(*result);
                    return 2;
                }
                else{
                    *result = newpointer;
                }
            }
            for(int j = lenght; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = '-';
            *(*result + lenght + 1) = '\0';
        }
        return r;
    }
    else if(*(number2 + 0) == '-' && *(number1 + 0) != '-'){
        int r = add(number1, number2 + 1, result);
        return r;
    }
    else if(*(number2 + 0) == '-' && *(number1 + 0) == '-'){
        int r = subtract(number1 + 1, number2 + 1, result);
        if(r == 0){
            if(compare(number1, number2) == 1){
                int lenght = strlen(*result);
                for(int i = 0; i < lenght - 1; ++i){
                    *(*result + i) = *(*result + i + 1);
                }
                *(*result + lenght - 1) = '\0';
            }
            else if(compare(number1, number2) == -1){
                int lenght = strlen(*result);
                for(int j = lenght; j > 0; --j){
                    *(*result + j) = *(*result + j - 1);
                }
                *(*result + 0) = '-';
                *(*result + lenght + 1) = '\0';
            }
        }
        return r;
    }
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    int diff;
    if(lenght1 >= lenght2){
        *result = calloc((lenght1 + 2), sizeof(char));
        diff = lenght1 - lenght2;
    }
    else{
        *result = calloc((lenght2 + 2), sizeof(char));
        diff = lenght2 - lenght1;
    }
    if (*result == NULL)
        return 3;
    int carry = 0;
    int j = 0;
    //odjemowanie dwóch dodatnich
    if(*(number2 + 0) != '-' && *(number1 + 0) != '-'){
        if(compare(number1, number2) == 1 || compare(number1, number2) == 0){
            j = lenght1 - 1;
            for (int i = lenght2 - 1; i >= 0; i--) {
                int sub = ((*(number1 + i + diff) - '0') - (*(number2 + i) - '0')
                           - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                    carry = 0;

                *(*result + j) = sub + '0';
                --j;
            }
            for (int i = lenght1 - lenght2 - 1; i >= 0; i--) {
                if (*(number1 + i) == '0' && carry) {
                    *(*result + j) = '9';
                    --j;
                    continue;
                }
                int sub = ((*(number1 + i) - '0') - carry);
                if (i >= 0 || sub > 0)
                    *(*result + j) = sub + '0';
                --j;
                carry = 0;
            }
            if(compare(number1, number2) == 1){
                while(*(*result + 0) == '0'){
                    int lenght = strlen(*result);
                    for(int i = 0; i < lenght - 1; ++i){
                        *(*result + i) = *(*result + i + 1);
                    }
                    *(*result + lenght - 1) = '\0';
                }
            }
            else{
                while(*(*result + 0) == '0' && *(*result + 1) == '0'){
                    int lenght = strlen(*result);
                    for(int i = 0; i < lenght - 1; ++i){
                        *(*result + i) = *(*result + i + 1);
                    }
                    *(*result + lenght - 1) = '\0';
                }
            }
        }
        else{
            j = lenght2 - 1;
            for (int i = lenght1 - 1; i >= 0; i--) {
                int sub = ((*(number2 + i + diff) - '0') - (*(number1 + i) - '0')
                           - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                    carry = 0;

                *(*result + j) = sub + '0';
                --j;
            }
            for (int i = lenght2 - lenght1 - 1; i >= 0; i--) {
                if (*(number2 + i) == '0' && carry) {
                    *(*result + j) = '9';
                    --j;
                    continue;
                }
                int sub = ((*(number2 + i) - '0') - carry);
                if (i >= 0 || sub > 0)
                    *(*result + j) = sub + '0';
                --j;
                carry = 0;
            }
            int lenght = strlen(*result);
            for(int i = lenght + 1; i > 0; --i){
                *(*result + i) = *(*result + i - 1);
            }
            while(*(*result + 0) == '0' && *(*result + 1) == '0'){
                int lenght = strlen(*result);
                for(int i = 0; i < lenght - 1; ++i){
                    *(*result + i) = *(*result + i + 1);
                }
                *(*result + lenght - 1) = '\0';
            }
            *(*result + 0) = '-';
        }
    }
    return 0;
}

int add(const char* number1, const char* number2, char** result){
    if(number1 == NULL || number2 == NULL || result == NULL){
        return 1;
    }
    if(validate(number1) == 2 || validate(number2) == 2)
        return 2;
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    int krotszy;
    if(*(number1 + 0) == '-' &&  *(number2 + 0) != '-'){

        int r = subtract(number2, number1 + 1, result);
        return r;
    }
    else if(*(number1 + 0) != '-' &&  *(number2 + 0) == '-'){

        int r = subtract(number1, number2 + 1, result);
        return r;
    }
    if(lenght1 >= lenght2){
        *result = calloc((lenght1 + 2), sizeof(char));
        krotszy = lenght2;
    }
    else{
        *result = calloc((lenght2 + 2), sizeof(char));
        krotszy = lenght1;
    }
    if (*result == NULL)
        return 3;
    //zmienne do obliczania sumy
    int w, p = 0;
    int i = 0;
    char tmp1, tmp2;
    int l;
    if(*(number1 + 0) != '-' &&  *(number2 + 0) != '-'){
        for(int j = 1; j <= krotszy; j++)
        {
            w  = (int)*(number1 + --lenght1) + (int)*(number2 + --lenght2) + p - 96;
            p  = w / 10;
            l = strlen(*result);
            if(l > 0) {
                tmp1 = *(*result + 0);
                *(*result + 0) = (char) ((w % 10) + 48);
                for (int q = 0; q < l; ++q) {
                    if ((q + 1) < l)
                        tmp2 = *(*result + q + 1);
                    *(*result + q + 1) = tmp1;
                    tmp1 = tmp2;
                }
            }
            else{
                *(*result + 0) = (char)((w % 10) + 48);
            }
            ++i;
        }
        while(lenght1)
        {
            w  = (int)*(number1 + --lenght1) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            tmp1 = *(*result + 0);
            *(*result + 0) = (char) ((w % 10) + 48);
            for (int q = 0; q < l; ++q) {
                if ((q + 1) < l)
                    tmp2 = *(*result + q + 1);
                *(*result + q + 1) = tmp1;
                tmp1 = tmp2;
            }
            ++i;
        }
        while(lenght2)
        {
            w  = (int)*(number2 + --lenght2) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            tmp1 = *(*result + 0);
            *(*result + 0) = (char) ((w % 10) + 48);
            for (int q = 0; q < l; ++q) {
                if ((q + 1) < l)
                    tmp2 = *(*result + q + 1);
                *(*result + q + 1) = tmp1;
                tmp1 = tmp2;
            }
            ++i;
        }
        if(p){
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char)(p + 48);
            ++i;
        }
    }
    else{
        int a;
        int b;
        for(int j = 1; j <= krotszy; j++)
        {
            a = (int)*(number1 + --lenght1);
            b = (int)*(number2 + --lenght2);
            if(a != '-' && b != '-'){
                w  = a + b + p - 96;
                p  = w / 10;
                l = strlen(*result);
                if(l > 0) {
                    tmp1 = *(*result + 0);
                    *(*result + 0) = (char) ((w % 10) + 48);
                    for (int q = 0; q < l; ++q) {
                        if ((q + 1) < l)
                            tmp2 = *(*result + q + 1);
                        *(*result + q + 1) = tmp1;
                        tmp1 = tmp2;
                    }
                }
                else{
                    *(*result + 0) = (char)((w % 10) + 48);
                }
                ++i;
            }
        }
        if(lenght1 == 0 && lenght2 != 0)
            lenght2++;
        else if(lenght1 != 0 && lenght2 == 0)
            lenght1++;
        while(lenght1 > 1)
        {
            w  = (int)*(number1 + --lenght1) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char) ((w % 10) + 48);
            ++i;
        }
        while(lenght2 > 1)
        {
            w  = (int)*(number2 + --lenght2) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char) ((w % 10) + 48);
            ++i;
        }
        if(p){
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char)(p + 48);
            ++i;
        }
        for(int j = i; j > 0; --j){
            *(*result + j) = *(*result + j - 1);
        }
        *(*result + 0) = '-';
        ++i;
    }
    *(*result + i) = '\0';
    return 0;
}
