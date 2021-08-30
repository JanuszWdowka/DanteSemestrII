#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

int save_point_b(const char *filename, const struct point_t* p);
int load_point_b(const char *filename, struct point_t* p);
int save_point_t(const char *filename, const struct point_t* p);
int load_point_t(const char *filename, struct point_t* p);
struct point_t* set(struct point_t* p, int x, int y);

void show(const struct point_t* p);

int main() {
    struct point_t one;
    int result = 0;
    char name[31];
    char c;
    char type;
    srand(time(NULL));
    set(&one, rand() % 100, rand() % 100);
    show(&one);
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    for(int i = 0; i < 31; ++i){
        if(*(name + i) == '\0') {
            if (*(name + i - 4) == '.' && *(name + i - 3) == 't' && *(name + i - 2) == 'x' && *(name + i - 1) == 't') {
                result = save_point_t(name, &one);
                if (result == 1 || result == 2 || result == 3) {
                    printf("Couldn't create file");
                    return 5;
                } else {
                    printf("File saved");
                    type = 't';
                }
                break;
            }
            else if (*(name + i - 4) == '.' && *(name + i - 3) == 'b' && *(name + i - 2) == 'i' &&
                       *(name + i - 1) == 'n') {
                result = save_point_b(name, &one);
                if (result == 1 || result == 2 || result == 3) {
                    printf("Couldn't create file");
                    return 5;
                } else {
                    printf("File saved");
                    type = 'b';
                }
                break;
            }
            else {
                printf("Unsupported file format");
                return 7;
            }
        }
    }
    while (getchar() != '\n');
    printf("\nDo you want to read the file(Y\\N)?");
    scanf("%c", &c);
    if(c == 'y' || c == 'Y'){
        if(type == 't'){
            result = load_point_t(name, &one);
            if(result == 2){
                printf("Couldn't open file");
                return 4;
            }
            else if(result == 1 || result == 3){
                printf("File corrupted");
                return 6;
            }
            show(&one);
        }
        else if(type == 'b'){
            result = load_point_b(name, &one);
            if(result == 2){
                printf("Couldn't open file");
                return 4;
            }
            else if(result == 1 || result == 3){
                printf("File corrupted");
                return 6;
            }
            show(&one);
        }
    }
    else if(c == 'n' || c == 'N'){
        return 0;
    }
    else{
        printf("Incorrect input");
        return 1;
    }
    return 0;
}

int save_point_b(const char *filename, const struct point_t* p){
    FILE *file;
    int size = 0;
    if(filename == NULL || p == NULL){
        return 1;
    }
    if((file = fopen(filename, "wb")) == NULL){
        return 2;
    }
    size = fwrite(p, sizeof(&p), 1, file);
    if(size == 0){
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}

int load_point_b(const char *filename, struct point_t* p){
    FILE *file;
    int size = 0;
    if(filename == NULL || p == NULL){
        return 1;
    }
    if((file = fopen(filename, "rb")) == NULL){
        return 2;
    }
    size = fread(p, sizeof(&p), 1, file);
    if(size == 0){
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}

int save_point_t(const char *filename, const struct point_t* p){
    FILE *file;
    int size = 0;
    if(filename == NULL || p == NULL){
        return 1;
    }
    if((file = fopen(filename, "w")) == NULL){
        return 2;
    }
    size = fprintf(file, "%d %d", (*p).x, (*p).y);
    if(size < 2){
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}

int load_point_t(const char *filename, struct point_t* p){
    FILE *file;
    int size = 0;
    if(filename == NULL || p == NULL){
        return 1;
    }
    if((file = fopen(filename, "r")) == NULL){
        return 2;
    }
    size = fscanf(file, "%d %d", &p->x, &p->y);
    if(size < 2){
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}

struct point_t* set(struct point_t* p, int x, int y){
    if(p == NULL){
        return NULL;
    }
    p->x = x;
    p->y = y;
    return p;
}

void show(const struct point_t* p){
    if(p == NULL)
    {
        return;
    }
    printf("x = %d y = %d\n", (*p).x, (*p).y);
}
