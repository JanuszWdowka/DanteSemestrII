#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    int n = 0;
    char* txt = NULL;
    char* moreTxt = NULL;
    int x = 50;
    int error = 0;
    txt = realloc(txt, sizeof(char) * x);
    if(txt == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj tekst:\n");
    while ((c = getc(stdin)) != '\n' && c != EOF) {
        *(txt + n) = c;
        ++n;
        if(n == x) {
            x += 50;
            moreTxt = realloc(txt, sizeof(char) * x);
            if(moreTxt == NULL){
                *(txt + n - 1) = '\0';
                error = 1;
                break;
            }
            else{
                txt = moreTxt;
            }
        }
    }
    if(error == 0){
        if(n == x) {
            x += 50;
            moreTxt = realloc(txt, sizeof(char) * x);
            if(moreTxt == NULL){
                *(txt + n - 1) = '\0';
            }
            else{
                txt = moreTxt;
                *(txt + n) = '\0';
            }
        }
        else
            *(txt + n) = '\0';
    }
    printf("%s", txt);
    free(txt);
    return 0;
}
