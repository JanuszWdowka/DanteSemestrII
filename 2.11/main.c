#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct file_t
{
    FILE *f;
    int size;
};

int open_file(struct file_t* f, const char *filename);
struct file_t* find_min(const struct file_t* files, int size);
void close_file(struct file_t* f);

int main() {
    struct file_t files[5];
    char name[1000];
    int howMany = 0;
    char text[1000];
    int len;
    int resultOpen;

    printf("Podaj nazwy plikow:\n");
    while(true){
        if(fgets(name, 1000, stdin) == NULL || *name == '\n'){
            break;
        }
        len = strlen(name);
        *(name + len - 1) = '\0';
        resultOpen = open_file((files + howMany), name);
        if (resultOpen == 0) {
            howMany++;
        }
    }
    if (howMany == 0) {
        printf("Couldn't open file");
        return 4;
    }

    printf("Podaj teksty:\n");
    struct file_t* p;
    while (fgets(text, 1001, stdin) == NULL || *text != '\n'){
        p = find_min(files, howMany);
        fwrite(text, sizeof(char), strlen(text), p->f);
        p->size = ftell(p->f);
    }
    for (int i = 0; i < howMany; i++) {
        close_file(files + i);
    }
    return 0;
}

int open_file(struct file_t* f, const char *filename){
    FILE* file;
    if (f == NULL || filename == NULL) {
        return 1;
    }
    file = fopen(filename, "a");
    if (file == NULL) {
        return 2;
    }
    f->size = ftell(file);
    fclose(file);
    f->f = fopen(filename, "a");
    if (f->f == NULL) {
        return 2;
    }
    return 0;
}

struct file_t* find_min(const struct file_t* files, int size){
    if(files == NULL || size <= 0){
        return NULL;
    }
    int min = (files+0)->size;
    int num = 0;
    for(int i = 1; i < size; i++){
        if(min > (files + i)->size){
            min = (files + i)->size;
            num = i;
        }
    }
    return (struct file_t*)(files + num);
}

void close_file(struct file_t* f){
    if(f == NULL || f->f == NULL){
        return;
    }
    fclose(f->f);
    return;
}