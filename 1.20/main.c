#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main() {
    //otwieranie plikow
    char name[31];
    FILE *plikOdczyt;
    FILE *plikZapis;
    char c;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    while((c = getchar()) != '\n' && c != EOF);
    if((plikOdczyt = fopen(name, "rb")) == NULL){
        printf("Couldn't open file");
        return 4;
    }
    //zmienie do wypeniania pliku out
    int znak;
    long long sum = 0;
    long long liczba = 0;
    bool czyBylaLiczba = false;
    int ilosc = 0;

    znak = getc(plikOdczyt);
    while(znak != EOF){
        if((znak > 47 && znak < 58) || znak == 10 || znak == 32 || znak == 45){
            if(znak == 32 || znak == 10){
                if(czyBylaLiczba == false){
                    czyBylaLiczba = true;
                    ilosc = liczba;
                    liczba = 0;
                    break;
                }
            }
            else{
                liczba = liczba * 10 + znak - 48;
            }
        }
        znak = getc(plikOdczyt);
    }

    if(ilosc < 1) {
        printf("File corrupted");
        fclose(plikOdczyt);
        return 6;
    }

    znak = getc(plikOdczyt);
    int doduj;
    while(znak != EOF && ilosc != 0){
        if((znak > 47 && znak < 58) || znak == 32 || znak == 10 || znak == 45){
            if(znak == 32 || znak == 10){
                if(doduj == -1){
                    liczba = 0;
                    doduj = 1;
                    goto xd;
                }
                if(liczba > 0){
                    ilosc--;
                    sum += liczba;
                    liczba = 0;
                }
            }
            else if(znak == 45){
                doduj = -1;
            }
            else{
                liczba = liczba * 10 + znak - 48;
            }
        }
        else{
            printf("File corrupted");
            fclose(plikOdczyt);
            return 6;
        }
        xd:
        znak = getc(plikOdczyt);
    }
    if(ilosc != 0){
        sum += liczba;
        ilosc--;
    }

    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    while((c = getchar()) != '\n' && c != EOF);
    if((plikZapis = fopen(name, "wb")) == NULL){
        fclose(plikOdczyt);
        printf("Couldn't create file");
        return 5;
    }


    if(ilosc == 0)
        fprintf(plikZapis,"%lld\n", sum);
    else
        fprintf(plikZapis,"%d", -1);

    //koniec
    printf("File saved");

    fclose(plikOdczyt);
    fclose(plikZapis);
    return 0;
}