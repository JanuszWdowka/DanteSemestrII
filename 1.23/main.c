#include <stdio.h>
#include <string.h>

int read_file(const char *filename);

int main() {
    char name[31];
    int result = 0;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    result = read_file(name);
    if(result == 0 || result == -1){
        printf("Couldn't open file");
        return 4;
    }
    printf("%d", result);
    return 0;
}

int read_file(const char *filename){
    int result = 0;
    char nazwaDoOdczytu[31];
    FILE *czytanyPlik;
    FILE *plik;

    if(filename == NULL)
        return -1;
    if((plik = fopen(filename, "rb")) == NULL)
        return 0;

    result++;

    while(fgets(nazwaDoOdczytu, 31, plik) != NULL){
        strtok(nazwaDoOdczytu, "\n");
        czytanyPlik = fopen(nazwaDoOdczytu, "rb");
        if(czytanyPlik != NULL){
            printf("%s\n", nazwaDoOdczytu);
            result += read_file(nazwaDoOdczytu);
            fclose(czytanyPlik);
        }
        else
            printf("%s\n", nazwaDoOdczytu);
    }
    fclose(plik);
    return result;
}