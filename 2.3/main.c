#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int save_points_b(const char *filename, const struct point_t* p, unsigned int N);
struct point_t* read(struct point_t* p);

int main() {
    struct point_t tab[100];
    char name[31];
    int howMany;
    int result = 0;
    printf("Podaj liczbe punktow: ");
    if(!scanf("%d", &howMany)){
        printf("Incorrect input");
        return 1;
    }
    if(howMany < 1){
        printf("Incorrect input data");
        return 2;
    }
    printf("Podaj punkty:\n");
    for(int i = 0; i < howMany && i < 100; ++i){
        if(read((tab + i)) == NULL){
            printf("Incorrect input");
            return 1;
        }
    }
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    if(howMany > 100){
        howMany = 100;
    }
    result = save_points_b(name, tab, (unsigned int)howMany);
    if(result == 1){
        printf("Incorrect input");
        return 1;
    }
    else if(result == 2 || result == 3){
        printf("Couldn't create file");
        return 5;
    }
    printf("File saved");
    return 0;
}

struct point_t* read(struct point_t* p){
    if(p == NULL){
        return NULL;
    }

    if(!scanf("%d", &p->x)){
        return NULL;
    }
    if(!scanf("%d", &p->y)){
        return NULL;
    }
    return p;
}

int save_points_b(const char *filename, const struct point_t* p, unsigned int N){
    if(filename == NULL || p == NULL || N < 1){
        return 1;
    }
    FILE *plik;
    int size = 0;
    if((plik = fopen(filename, "w")) == NULL){
        return 2;
    }
    for(int i = 0; i < (int)N; ++i){
        size = fwrite(&*(p + i), sizeof(&p), 1, plik);
        if(size == 0){
            fclose(plik);
            return 3;
        }
    }
    fclose(plik);
    return 0;
}