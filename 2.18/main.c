#include <stdio.h>
#include <math.h>
#include <stdlib.h>

enum figure_types{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct point_t
{
    int x;
    int y;
};

struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};

struct circle_t
{
    struct point_t c;
    float r;
};

struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};

struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

float area_triangle(const struct triangle_t *t);
float area_rectangle(const struct rectangle_t *r);
float area_circle(const struct circle_t *c);
float area_figure(const struct figure_t *f);

void display_rectangle(const struct rectangle_t *rect);
void display_triangle(const struct triangle_t *t);
void display_circle(const struct circle_t *circ);
void display_figure(struct figure_t *f);

int sort_by_area(struct figure_t **figures, int size);

int main() {
    struct figure_t figurs[50];
    int type = 1;
    int lenght = 0;
    for(int i = 0; i < 50; ++i){
        printf("Enter figure's type: ");
        if(!scanf("%d", &type)){
            printf("Incorrect input");
            return 1;
        }
        else if(type < 0 || type > 3){
            printf("Incorrect input data");
            return 2;
        }
        if(type == 0){
            break;
        }
        (figurs + i)->type = type;
        if((figurs + i)->type == 1){
            printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
            if(!scanf("%d", &(figurs + i)->triangle.p1.x)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->triangle.p1.y)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->triangle.p2.x)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->triangle.p2.y)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->triangle.p3.x)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->triangle.p3.y)){
                printf("Incorrect input");
                return 1;
            }
        }
        else if((figurs + i)->type == 2){
            printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
            if(!scanf("%d", &(figurs + i)->rect.p.x)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->rect.p.y)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->rect.width)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->rect.height)){
                printf("Incorrect input");
                return 1;
            }
        }
        else if((figurs + i)->type == 3){
            printf("Enter coordinates and radius of a circle: ");
            if(!scanf("%d", &(figurs + i)->circ.c.x)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%d", &(figurs + i)->circ.c.y)){
                printf("Incorrect input");
                return 1;
            }
            if(!scanf("%f", &(figurs + i)->circ.r)){
                printf("Incorrect input");
                return 1;
            }
        }
        lenght++;
    }
    for(int i = 0; i < lenght; ++i){
        if((figurs + i)->type == 1){
            if((figurs + i)->triangle.p1.x == (figurs + i)->triangle.p2.x && (figurs + i)->triangle.p1.y == (figurs + i)->triangle.p2.y){
                printf("Incorrect input data");
                return 2;
            }
            else if((figurs + i)->triangle.p1.x == (figurs + i)->triangle.p3.x && (figurs + i)->triangle.p1.y == (figurs + i)->triangle.p3.y){
                printf("Incorrect input data");
                return 2;
            }
            else if((figurs + i)->triangle.p2.x == (figurs + i)->triangle.p3.x && (figurs + i)->triangle.p2.y == (figurs + i)->triangle.p3.y){
                printf("Incorrect input data");
                return 2;
            }
        }
        else if((figurs + i)->type == 2){
            if((figurs + i)->rect.width < 0 || (figurs + i)->rect.height < 0){
                printf("Incorrect input data");
                return 2;
            }
        }
        else if((figurs + i)->type == 3){
            if((figurs + i)->circ.r <= 0){
                printf("Incorrect input data");
                return 2;
            }
        }
    }
    struct figure_t *ptr[50];
    for (int i = 0; i < lenght; ++i)
        *(ptr + i) = figurs + i;
    sort_by_area(ptr, lenght);
    for(int i = 0; i < lenght; i++){
        display_figure(*(ptr + i));
        printf("\n");
    }
    return 0;
}

float area_triangle(const struct triangle_t *t){
    if(t == NULL || &t->p3 == NULL || &t->p2 == NULL || &t->p1 == NULL){
        return -1;
    }
    if(t->p1.x == t->p2.x && t->p1.y == t->p2.y){
        return -1;
    }
    else if(t->p1.x == t->p3.x && t->p1.y == t->p3.y){
        return -1;
    }
    else if(t->p2.x == t->p3.x && t->p2.y == t->p3.y){
        return -1;
    }
    int number = (t->p2.x - t->p1.x) * (t->p3.y - t->p1.y) - (t->p2.y - t->p1.y) * (t->p3.x - t->p1.x);
    return 0.5 * abs(number);
}
float area_rectangle(const struct rectangle_t *r){
    if(r == NULL || &r->p == NULL){
        return -1;
    }
    if(r->width < 0 || r->height < 0){
        return -1;
    }
    return r->height * r->width;
}
float area_circle(const struct circle_t *c){
    if(c == NULL || &c->c == NULL){
        return -1;
    }
    if(c->r <= 0){
        return -1;
    }
    return c->r * c->r * M_PI;
}
float area_figure(const struct figure_t *f){
    if(f == NULL || &f->type == NULL){
        return -1;
    }
    if(f->type == TRIANGLE){
        return area_triangle(&f->triangle);
    }
    else if(f->type == RECTANGLE){
        return area_rectangle(&f->rect);
    }
    else if(f->type == CIRCLE){
        return area_circle(&f->circ);
    }
    return -1;
}

void display_rectangle(const struct rectangle_t *rect){
    if(rect == NULL){
        return;
    }
    printf("Rectangle (%d, %d), width = %d, height = %d", rect->p.x, rect->p.y, rect->width, rect->height);
    return;
}
void display_triangle(const struct triangle_t *t){
    if(t == NULL){
        return;
    }
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
    return;
}
void display_circle(const struct circle_t *circ){
    if(circ == NULL){
        return;
    }
    printf("Circle (%d, %d), radius = %f", circ->c.x, circ->c.y, circ->r);
    return;

}
void display_figure(struct figure_t *f){
    if(f == NULL){
        return;
    }
    if(f->type == TRIANGLE){
        display_triangle(&f->triangle);
    }
    else if(f->type == RECTANGLE){
        display_rectangle(&f->rect);
    }
    else if(f->type == CIRCLE){
        display_circle(&f->circ);
    }
    return;
}

int sort_by_area(struct figure_t **figures, int size){
    if(size < 1 || figures == NULL){
        return 1;
    }
    struct figure_t *temp;
    for(int i = 0; i < size; ++i){
        if(area_figure(*(figures + i)) == -1){
            return 1;
        }
    }
    for(int i = 0; i < size; ++i){
        for (int j = 0; j < size - i - 1; j++)
        {
            if (area_figure(*(figures + j)) < area_figure(*(figures + j + 1)))
            {
                temp = *(figures + j + 1);
                *(figures + j + 1) = *(figures + j);
                *(figures + j) = temp;
            }
        }
    }
    return 0;
}