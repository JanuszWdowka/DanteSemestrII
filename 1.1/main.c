#include <stdio.h>

int main() {
    char name[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    FILE *plik;
    if((plik = fopen(name, "r")) == NULL){
        printf("Couldn't open file");
        return 4;
    }
    int znak;
    znak = getc(plik);
    if (znak == EOF){
        printf("nothing to show");
        fclose(plik);
        return 0;
    }
    while(znak != EOF){
        printf("%c", znak);
        znak = getc(plik);
    }
    fclose(plik);
    return 0;
}
