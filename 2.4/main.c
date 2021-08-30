#include <stdio.h>
#include <math.h>
#include <ctype.h>

struct point_t {
    int x;
    int y;
};

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);
int load_point_t(const char *filename, struct point_t* p1, struct point_t* p2, struct point_t* tmp1, struct point_t* tmp2);

int main() {
    char filename[100];
    struct point_t p1;
    struct point_t p2;
    struct point_t tmp1;
    struct point_t tmp2;
    int result = 0;
    printf("Podaj sciezke do pliku:\n");
    if(!scanf("%99s", filename)){
        printf("Incorect input");
        return 1;
    }
    result = load_point_t(filename, &p1, &p2, &tmp1, &tmp2);
    if(result == 2){
        printf("Couldn't open file");
        return 4;
    }
    else if(result == 1 || result == 3){
        printf("File corrupted");
        return 6;
    }
    printf("%d %d %d %d", p1.x, p1.y, p2.x, p2.y);
    return 0;
}

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code){
    if(p1 == NULL || p2 == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return -1;
    }
    if(err_code != NULL){
        *err_code = 0;
    }
    double dx = (*p1).x - (*p2).x;
    double dy = (*p1).y - (*p2).y;
    return sqrt(dx*dx + dy*dy);
}

int load_point_t(const char *filename, struct point_t* p1, struct point_t* p2, struct point_t* tmp1, struct point_t* tmp2){
    FILE *file;
    if(filename == NULL || p1 == NULL || p2 == NULL || tmp1 == NULL || tmp2 == NULL){
        return 1;
    }
    if((file = fopen(filename, "r")) == NULL){
        return 2;
    }
    char z = getc(file);
    while (z != EOF){
        if(!isdigit(z)){
            if(z != 10 && z != 32 && z != 45){
                fclose(file);
                return 3;
            }
        }
        z = getc(file);
    }
    fseek(file, 0, SEEK_SET);
    if(fscanf(file, "%d %d", &p1->x, &p1->y) != 2){
        fclose(file);
        return 3;
    }
    getc(file);
    if(fscanf(file, "%d %d", &p2->x, &p2->y) != 2){
        fclose(file);
        return 3;
    }

    fseek(file, 0, SEEK_SET);
    int pozycjaDoCofniecia;
    int error = 0;
    while (fscanf(file, "%d %d", &tmp1->x, &tmp1->y) == 2){
        pozycjaDoCofniecia = ftell(file);
        while (fscanf(file, "%d %d", &tmp2->x, &tmp2->y) == 2){
            if(distance(p1, p2, &error) > distance(tmp1, tmp2, &error)){
                p1->x = tmp1->x;
                p1->y = tmp1->y;
                p2->x = tmp2->x;
                p2->y = tmp2->y;
            }
        }
        fseek(file, pozycjaDoCofniecia, SEEK_SET);
    }

    fclose(file);
    return 0;
}