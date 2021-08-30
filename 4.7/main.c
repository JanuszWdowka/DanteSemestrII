#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "image_utils.h"

int main() {
    struct image_t* image;
    struct image_t* image2 = NULL;
    int error = 0;
    int result;
    int x;
    int y;
    int c;
    int value;
    const char* extension = "_modified";
    char* name = (char*) calloc(40, sizeof(char));
    if(name == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter file name: ");
    scanf("%39s", name);
    image = load_image_t(name, &error);
    if(error == 2){
        free(name);
        printf("Couldn't open file");
        return 4;
    }
    else if(error == 3){
        free(name);
        printf("File corrupted");
        return 6;
    }
    else if(error == 4){
        free(name);
        printf("Failed to allocate memory");
        return 8;
    }
    while ((c = getchar()) != '\n' && c != EOF) { }
    printf("How many subimages you want to draw: ");
    if(!scanf("%d", &value)){
        printf("Incorrect input");
        destroy_image(&image);
        free(name);
        return 1;
    }
    if(value < 1){
        printf("Incorrect input data");
        destroy_image(&image);
        free(name);
        return 2;
    }
    char* namex = (char*) calloc(40, sizeof(char));
    if(namex == NULL){
        destroy_image(&image);
        free(name);
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < value; ++i){
        printf("Enter a name of a subimage: ");
        scanf("%39s", namex);
        while ((c = getchar()) != '\n' && c != EOF) { }
        if(image2 != NULL)
            destroy_image(&image2);
        image2 = load_image_t(namex, &error);
        if(error == 2){
            printf("Couldn't open file\n");
            continue;
        }
        else if(error == 3){
            printf("File corrupted\n");
            continue;
        }
        else if(error == 4){
            free(namex);
            printf("Failed to allocate memory");
            destroy_image(&image);
            free(name);
            return 8;
        }
        printf("Enter coordinates (x, y): ");
        if(!scanf("%d ", &x)){
            printf("Incorrect input");
            destroy_image(&image2);
            destroy_image(&image);
            free(name);
            free(namex);
            return 1;
        }
        if(!scanf("%d", &y)){
            printf("Incorrect input");
            destroy_image(&image2);
            destroy_image(&image);
            free(name);
            free(namex);
            return 1;
        }
        if(x < 0 || y < 0){
            printf("Incorrect input data\n");
            continue;
        }
        if(x >= image->width || y >= image->height){
            printf("Incorrect input data\n");
            continue;
        }
        if(image2->width > image->width || image2->height > image->height){
            printf("Incorrect input data\n");
            continue;
        }
        if(x + image2->width > image->width || y + image2->height > image->height){
            printf("Incorrect input data\n");
            continue;
        }
        draw_image(image, image2, x, y);
    }
    destroy_image(&image2);
    free(namex);

    char* zaq;
    zaq = (char*) malloc(100 * sizeof(char));
    int n = 0;
    for(int i = strlen(name) - 1; i > 0; --i){
        if(*(name + i) == '.'){
            n = i;
            break;
        }
    }
    strncpy(zaq, name, n);
    *(zaq + n) = '\0';
    strcat(zaq, extension);
    strcat(zaq, name + n);
    result = save_image_t(zaq, image);
    if(result == 2 || result == 3){
        printf("Couldn't create file\n");
        free(zaq);
        destroy_image(&image);
        free(name);
        return 5;
    }
    printf("File saved");
    destroy_image(&image);
    free(zaq);
    free(name);
    return 0;
}
