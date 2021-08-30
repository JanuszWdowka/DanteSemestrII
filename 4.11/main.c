#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include "format_type.h"

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

//co zrobić: sprawdzić alokacje pamięci w load, napisać statistic rowa
int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);

int main() {
    struct statistic_t* stats;
    int **D;
    int result = 0;
    char* name = (char*) calloc(40, sizeof(char));
    if(name == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pliku: ");
    scanf("%39s", name);

    for(int i = 0; i < 40; ++i){
        if(*(name + i) == '\0' || i == 39) {
            if (*(name + i - 4) == '.' && *(name + i - 3) == 't' && *(name + i - 2) == 'x' && *(name + i - 1) == 't') {
                result = load(name, &D, fmt_text);
                if (result == 1 || result == 2) {
                    free(name);
                    printf("Couldn't open file");
                    return 4;
                }
                else if(result == 3){
                    free(name);
                    printf("File corrupted");
                    return 6;
                }
                else if(result == 4){
                    free(name);
                    printf("Failed to allocate memory");
                    return 8;
                }
                break;
            }
            else if (*(name + i - 4) == '.' && *(name + i - 3) == 'b' && *(name + i - 2) == 'i' &&
                     *(name + i - 1) == 'n') {
                result = load(name, &D, fmt_binary);
                if (result == 1 || result == 2) {
                    free(name);
                    printf("Couldn't open file");
                    return 4;
                }
                else if(result == 3){
                    free(name);
                    printf("File corrupted");
                    return 6;
                }
                else if(result == 4){
                    free(name);
                    printf("Failed to allocate memory");
                    return 8;
                }
                break;
            }
            else {
                free(name);
                printf("Unsupported file format");
                return 7;
            }
        }
    }
    //display(D);
    result = statistics_row(D, &stats);
    if(result == -2){
        destroy(&D);
        free(name);
    }
    for(int i = 0; i < result; ++i){
        printf("%d %d %d %.2f %.2f\n", (stats + i)->min, (stats + i)->max, (stats + i)->range, (stats + i)->avg, (stats + i)->standard_deviation);
    }
    free(stats);
    destroy(&D);
    free(name);
    return 0;
}


void display(int **ptr){
    if(ptr == NULL){
        return;
    }
    for(int i = 0; *(ptr + i) != NULL; ++i){
        for(int j = 0; *(*(ptr + i) + j) != -1; ++j){
            printf("%d ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}

int save(const char *filename, int **ptr, enum save_format_t format){
    FILE *file;
    if(filename == NULL || ptr == NULL){
        return 1;
    }
    if(format == fmt_text){
        if((file = fopen(filename, "w")) == NULL){
            return 2;
        }
        for(int i = 0; *(ptr + i) != NULL; ++i){
            for(int j = 0; *(*(ptr + i) + j) != -1; ++j){
                if(!fprintf(file, "%d ", *(*(ptr + i) + j))){
                    fclose(file);
                    return 1;
                }
            }
            if(!fprintf(file, "%d", -1)){
                fclose(file);
                return 1;
            }
            fprintf(file,"\n");
        }
    }
    else if(format == fmt_binary){
        int x = -1;
        if((file = fopen(filename, "wb")) == NULL){
            return 2;
        }
        for(int i = 0; *(ptr + i) != NULL; ++i){
            for(int j = 0; *(*(ptr + i) + j) != -1; ++j){
                if(fwrite((*(ptr + i) + j), sizeof(int), 1, file) == 0){
                    fclose(file);
                    return 1;
                }
            }
            if(fwrite(&x, sizeof(int), 1, file) == 0){
                fclose(file);
                return 1;
            }
        }
    }
    else{
        return 1;
    }
    fclose(file);
    return 0;
}

int load(const char *filename, int ***ptr, enum save_format_t format){
    FILE *file;
    int lines = 0;
    int inLine = 0;
    int size = 0;
    if(filename == NULL || ptr == NULL){
        return 1;
    }
    if(format == fmt_text){
        if((file = fopen(filename, "r")) == NULL){
            return 2;
        }
        int doduj = 1;
        int liczba = 0;
        char znak = getc(file);
        if(znak == EOF){
            fclose(file);
            return 3;
        }
        while(znak != EOF){ // obliczanie ile jest wierszy
            if((znak > 47 && znak < 58) || znak == 10 || znak == 32 || znak == 45){
                if(znak == 32 || znak == 10){
                    if(doduj == -1){
                        liczba *= doduj;
                    }
                    if(liczba == -1){
                        lines++;
                    }
                    liczba = 0;
                    doduj = 1;
                }
                else if(znak == 45){
                    doduj = -1;
                }
                else{
                    liczba = liczba * 10 + znak - 48;
                }
            }
            else{
                fclose(file);
                return 3;
            }
            znak = getc(file);
        }
        if(lines == 0){
            fclose(file);
            return 3;
        }
        *ptr = (int**) malloc((lines + 1) * sizeof(int*));
        if(*ptr == NULL){
            fclose(file);
            return 4;
        }
        *(*ptr + lines) = NULL;
        fseek(file, 0, SEEK_SET);
        lines = 0;
        znak = getc(file);
        while(znak != EOF){//alokacja dla wiersza
            if((znak > 47 && znak < 58) || znak == 10 || znak == 32 || znak == 45){
                if(znak == 32 || znak == 10){
                    if(doduj == -1){
                        liczba *= doduj;
                    }
                    inLine++;
                    if(liczba == -1){
                        *(*ptr + lines) = (int*) malloc(inLine * sizeof(int));
                        if(*(*ptr + lines) == NULL){
                            for(int i = 0; i < lines; ++i){
                                free(*(*ptr + i));
                            }
                            free(*ptr);
                            *ptr = NULL;
                            fclose(file);
                            return 4;
                        }
                        lines++;
                        inLine = 0;
                    }
                    liczba = 0;
                    doduj = 1;
                }
                else if(znak == 45){
                    doduj = -1;
                }
                else{
                    liczba = liczba * 10 + znak - 48;
                }
            }
            else{
                fclose(file);
                return 3;
            }
            znak = getc(file);
        }
        fseek(file, 0, SEEK_SET);
        inLine = 0;
        lines = 0;
        znak = getc(file);
        liczba = 0;
        while(znak != EOF){//przypisanie warotosci
            if((znak > 47 && znak < 58) || znak == 10 || znak == 32 || znak == 45){
                if(znak == 32 || znak == 10){
                    if(doduj == -1){
                        liczba *= doduj;
                    }
                    *(*(*ptr + lines) + inLine) = liczba;
                    inLine++;
                    if(liczba == -1){
                        lines++;
                        inLine = 0;
                    }
                    liczba = 0;
                    doduj = 1;
                }
                else if(znak == 45){
                    doduj = -1;
                }
                else{
                    liczba = liczba * 10 + znak - 48;
                }
            }
            else{
                fclose(file);
                return 3;
            }
            znak = getc(file);
        }
    }
    else if(format == fmt_binary){
        if((file = fopen(filename, "rb")) == NULL){
            return 2;
        }
        int liczba;
        int position = 0;
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        if(size == 0){
            fclose(file);
            return 3;
        }
        fseek(file, 0, SEEK_SET);
        while(true){//pamieć ile wierszy
            size = fread(&liczba, sizeof(int), 1, file);
            if(size == 0){
                fclose(file);
                return 3;
            }
            if(liczba == -1){
                lines++;
            }
            position = ftell(file);
            size = fread(&liczba, sizeof(int), 1, file);
            if(size == 0){
                break;
            }
            else{
                fseek(file, position, SEEK_SET);
            }
        }
        if(lines == 0){
            fclose(file);
            return 3;
        }
        *ptr = (int**) malloc((lines + 1) * sizeof(int*));
        if(*ptr == NULL){
            fclose(file);
            return 4;
        }
        *(*ptr + lines) = NULL;
        fseek(file, 0, SEEK_SET);
        lines = 0;
        while(true){//pamiec ile w wierszu
            size = fread(&liczba, sizeof(int), 1, file);
            if(size == 0){
                fclose(file);
                return 3;
            }
            inLine++;
            if(liczba == -1){
                *(*ptr + lines) = (int*) malloc(inLine * sizeof(int));
                if(*(*ptr + lines) == NULL){
                    for(int i = 0; i < lines; ++i){
                        free(*(*ptr + i));
                    }
                    free(*ptr);
                    *ptr = NULL;
                    fclose(file);
                    return 4;
                }
                lines++;
                inLine = 0;
            }
            position = ftell(file);
            size = fread(&liczba, sizeof(int), 1, file);
            if(size == 0){
                break;
            }
            else{
                fseek(file, position, SEEK_SET);
            }
        }
        fseek(file, 0, SEEK_SET);
        inLine = 0;
        lines = 0;
        int foo;
        while(true){//wprowadzanie wartości
            size = fread(&foo, sizeof(int), 1, file);
            *(*(*ptr + lines) + inLine) = foo;
            if(size == 0){
                fclose(file);
                return 3;
            }
            inLine++;
            if(foo == -1){
                lines++;
                inLine = 0;
            }
            position = ftell(file);
            size = fread(&liczba, sizeof(int), 1, file);
            if(size == 0){
                break;
            }
            else{
                fseek(file, position, SEEK_SET);
            }
        }
    }
    else{
        return 1;
    }
    fclose(file);
    return 0;
}

int statistics_row(int **ptr, struct statistic_t **stats){
    if(ptr == NULL || stats == NULL){
        return -1;
    }
    int rows = 0;
    int size = 0;
    double to_standard_deviation = 0;
    for(int i = 0; *(ptr + i) != NULL; ++i){
        rows++;
    }
    *stats = (struct statistic_t*) malloc(rows * sizeof(struct statistic_t));
    if(*stats == NULL){
        return -2;
    }
    for(int i = 0; *(ptr + i) != NULL; ++i){
        for(int j = 0; *(*(ptr + i) + j) != -1; ++j){
            size++;
        }
        if(size == 0){
            (*stats + i)->min = -1;
            (*stats + i)->max = -1;
            (*stats + i)->avg = -1;
            (*stats + i)->range = -1;
            (*stats + i)->standard_deviation = -1;
            continue;
        }
        (*stats + i)->min = *(*(ptr + i) + 0);
        (*stats + i)->max = *(*(ptr + i) + 0);
        (*stats + i)->avg = 0;
        for(int x = 0; *(*(ptr + i) + x) != -1; ++x){
            (*stats + i)->avg += (float)*(*(ptr + i) + x);
            if(*(*(ptr + i) + x) > (*stats + i)->max){
                (*stats + i)->max = *(*(ptr + i) + x);
            }
            else if(*(*(ptr + i) + x) < (*stats + i)->min){
                (*stats + i)->min = *(*(ptr + i) + x);
            }
        }
        (*stats + i)->avg = (*stats + i)->avg / size;
        (*stats + i)->range = (*stats + i)->max - (*stats + i)->min;
        for(int x = 0; *(*(ptr + i) + x) != -1; ++x) {
            to_standard_deviation += pow((double) ((double) *(*(ptr + i) + x) - (*stats + i)->avg), 2);
        }
        to_standard_deviation = to_standard_deviation / size;
        (*stats + i)->standard_deviation = sqrt(to_standard_deviation);
        size = 0;
        to_standard_deviation = 0;
    }
    return rows;
}

void destroy(int ***ptr){
    if(ptr == NULL){
        return;
    }
    int i = 0;
    while(*(*ptr + i) != NULL){
        free(*(*ptr + i));
        ++i;
    }
    free(*ptr);
    *ptr = NULL;
}
