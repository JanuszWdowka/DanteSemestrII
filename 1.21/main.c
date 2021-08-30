#include <stdio.h>

int main() {
    char name[31];
    int liczba = 0;
    int znak;
    long offset;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    FILE *plik;
    if((plik = fopen(name, "rb")) == NULL){
        printf("Couldn't open file");
        return 4;
    }


    //sprawdzanie
    znak = getc(plik);
    if(znak == 10){
        printf("File corrupted");
        fclose(plik);
        return 6;
    }
    while(znak != 10){
        if (znak != EOF && ((znak > 47 && znak < 58) || znak == 32)){

        if(znak == 32){
            offset = ftell(plik);
            if(fseek(plik, liczba, 0) == 0){
                znak = fgetc(plik);
                if(znak != -1){
                    fseek(plik, offset, 0);
                    liczba = 0;
                }
                else{
                    printf("File corrupted");
                    fclose(plik);
                    return 6;
                }
            }
            else{
                printf("File corrupted");
                fclose(plik);
                return 6;
            }
        }
        else
            liczba = liczba * 10 + (znak - 48);
        znak = getc(plik);
        }
        else{
            printf("File corrupted");
            fclose(plik);
            return 6;
        }
    }

    offset = ftell(plik);
    if(fseek(plik, liczba, 0) == 0){
        znak = fgetc(plik);
        if(znak != -1){
            fseek(plik, offset, 0);
            liczba = 0;
        }
        else{
            printf("File corrupted");
            fclose(plik);
            return 6;
        }
    }
    else{
        printf("File corrupted");
        fclose(plik);
        return 6;
    }

    //wyswietlanie
    fseek(plik, 0, 0);
    znak = getc(plik);
    while(znak != 10){
        if (znak != EOF && ((znak > 47 && znak < 58) || znak == 32)){
            if(znak == 32){
                offset = ftell(plik);
                if(fseek(plik, liczba, 0) == 0){
                    znak = fgetc(plik);
                    printf("%c", znak);
                    fseek(plik, offset, 0);
                    liczba = 0;
                }
            }
            else
                liczba = liczba * 10 + (znak - 48);
            znak = getc(plik);
        }
    }

    offset = ftell(plik);
    if(fseek(plik, liczba, 0) == 0){
        znak = fgetc(plik);
        if(znak != -1){
            printf("%c", znak);
            fseek(plik, offset, 0);
            liczba = 0;
        }
    }

    fclose(plik);
    return 0;
}
