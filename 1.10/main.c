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
    int doduj = 1;
    bool czyBylaLiczbaWWierszu = false;
    bool czyBylaLiczba = false;

    while(znak != EOF){
        if((znak > 47 && znak < 58)){
            czyBylaLiczba = true;
            break;
        }
        znak = getc(plikOdczyt);
    }
    if(czyBylaLiczba == false){
        fclose(plikOdczyt);
        printf("File corrupted");
        return 6;
    }

    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", name);
    while((c = getchar()) != '\n' && c != EOF);
    if((plikZapis = fopen(name, "wb")) == NULL){
        fclose(plikOdczyt);
        printf("Couldn't create file");
        return 5;
    }

    fseek(plikOdczyt, 0, 0);
    znak = getc(plikOdczyt);

    while(znak != EOF){
        if((znak > 47 && znak < 58) || znak == 32 || znak == 45){
            if(znak == 32 || znak == 10){
                if(doduj == -1 && liczba != 0){
                    liczba *= doduj;
                }
                czyBylaLiczba = true;
                sum += liczba;
                liczba = 0;
                doduj = 1;
            }
            else if(znak == 45){
                doduj = -1;
            }
            else{
                liczba = liczba * 10 + znak - 48;
                czyBylaLiczbaWWierszu = true;
            }
        }
        else if(znak == 10){
            if(liczba != 0){
                if(doduj == -1 && liczba != 0){
                    liczba *= doduj;
                }
                czyBylaLiczba = true;
                sum += liczba;
                liczba = 0;
                doduj = 1;
            }
            if(czyBylaLiczbaWWierszu){
                fprintf(plikZapis,"%lld\n", sum);
                sum = 0;
                czyBylaLiczbaWWierszu = false;
            }
        }
        else{
            if(doduj == -1)
                doduj = 1;
        }
        znak = getc(plikOdczyt);
    }

    if(doduj == -1){
        liczba *= doduj;
    }
    sum += liczba;
    if(czyBylaLiczbaWWierszu){
        fprintf(plikZapis,"%lld\n", sum);
    }

    //koniec
    printf("File saved");

    fclose(plikOdczyt);
    fclose(plikZapis);
    return 0;
}
