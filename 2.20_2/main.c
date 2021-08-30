#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union LSB {
    const char znak[8];
};

int encode(const char *input, char *txt, const char *output);
int decode(const char * filename, char *txt, int size);

int main() {
    char c;
    char name[31]; //input file
    char out[31]; //output file in encode
    char tekst[10000];
    int result;

    for(int i = 0; i < 10000; i++){
        *(tekst + i) = 0;
    }
    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    if(!scanf("%c", &c)){
        printf("Incorrect input");
        return 1;
    }
    if(c == 'E' || c == 'e'){
        while (getchar() != '\n');
        printf("Enter a message to be encoded: ");
        fgets(tekst, 10000, stdin);
        strtok(tekst, "\n");
        printf("Enter input file name: ");
        if(!scanf("%30s", name)){
            printf("Incorrect input");
            return 1;
        }
        printf("Enter output file name: ");
        if(!scanf("%30s", out)){
            printf("Incorrect input");
            return 1;
        }
        result = encode(name, tekst, out);
        if(result == 4){
            printf("Couldn't create file");
            return 5;
        }
        else if(result == 2){
            printf("Couldn't open file");
            return 4;
        }
        else if(result == 3 || result == 1){
            printf("File corrupted");
            return 6;
        }
        else if(result == 0){
            printf("File saved");
        }
    }
    else if(c == 'D' || c == 'd'){
        printf("Enter input file name: ");
        if(!scanf("%30s", name)){
            printf("Incorrect input");
            return 1;
        }
        result = decode(name, tekst, 10000);
        if(result == 2){
            printf("Couldn't open file");
            return 4;
        }
        else if(result == 3 || result == 1){
            printf("File corrupted");
            return 6;
        }
        else if(result == 0){
            printf("%s", tekst);
        }
    }
    else{
        printf("Incorrect input data");
        return 1;
    }
    return 0;
}

int encode(const char *input, char *txt, const char *output){
    if (input == NULL || txt == NULL || output == NULL){
        return 1;
    }
    FILE *inFile;
    FILE *outFile;
    if ((inFile = fopen(input, "r")) == NULL){
        return 2;
    }
    if ((outFile = fopen(output, "w")) == NULL){
        fclose(inFile);
        return 4;
    }
    char c;
    int tmp;
    int potrzebne_znaki = strlen(txt) * 8 - 8;
    int zliczone = 0;
    c = fscanf(inFile, "%d", &tmp);
    while (c != EOF){
        if (c != 1) {
            fclose(outFile);
            fclose(inFile);
            return 3;
        }
        zliczone++;
        c = fscanf(inFile, "%d", &tmp);
    }
    if (zliczone < potrzebne_znaki){
        fclose(outFile);
        fclose(inFile);
        return 3;
    }
    fseek(inFile, 0, SEEK_SET);
    int tmp2;
    unsigned int lsb = 0;
    int len = strlen(txt);
    int znak;
    for (int i = 0; i < len; ++i){
        for (int j = 7; j >= 0; --j){
            lsb = (*(txt + i) & (1u << j)) != 0;
            fscanf(inFile, "%d" , &tmp2);
            if (lsb == 1){
                tmp2 = tmp2 | 1;
            }
            else{
                tmp2 = tmp2 & ~1;
            }
            fprintf(outFile, "%d", tmp2);
            znak = fgetc(inFile);
            while (!(znak > 47 && znak < 58) && znak != EOF){
                fprintf(outFile, "%c", (char)znak);
                znak = fgetc(inFile);
            }
            if(znak > 47 && znak < 58){
                ungetc(znak, inFile);
            }
        }
    }


    for (int i = 0; i < zliczone - potrzebne_znaki; ++i){
        fscanf(inFile, "%d" , &tmp2);
        if (tmp2 & 1){
            tmp2 = tmp2 ^ 1;
        }
        else{
            tmp2 = tmp2 & ~1;
        }
        tmp2 = tmp2 & ~1;
        fprintf(outFile, "%d", tmp2);
        znak = fgetc(inFile);
        while (!(znak > 47 && znak < 58) && znak != EOF){
            fprintf(outFile, "%c", (char)znak);
            znak = fgetc(inFile);
        }
        if(znak > 47 && znak < 58){
            ungetc(znak, inFile);
        }
        if(znak == EOF){
            break;
        }

        if(znak == EOF){
            break;
        }
    }
    fclose(outFile);
    fclose(inFile);
    return 0;
}
int decode(const char * filename, char *txt, int size){
    if (filename == NULL || txt == NULL || size <= 0){
        return 1;
    }
    FILE *file;
    FILE *tmpFile;
    int tmp;
    char c;
    int potrzebne_znaki = (size * 8) - 8;
    int zliczone = 0;
    if ((file = fopen(filename, "r")) == NULL){
        return 2;
    }
    c = fscanf(file, "%d", &tmp);
    while (c != EOF){
        if (c != 1) {
            fclose(file);
            return 3;
        }
        zliczone++;
        c = fscanf(file, "%d", &tmp);
    }
    if(zliczone < potrzebne_znaki){
        fclose(file);
        return 3;
    }
    tmpFile = tmpfile();
    tmpFile = fopen("tmp_file", "w");
    fseek(file, 0, SEEK_SET);
    zliczone = 0;
    while (fscanf(file, "%d", &tmp) != EOF && zliczone++ < potrzebne_znaki){
        fprintf(tmpFile, "%d", (tmp & 1));
    }
    tmpFile = freopen("tmp_file", "r", tmpFile);
    char *tmp2;
    union LSB lsb;
    for (int i = 0; i < size - 1; ++i) {
        fread(&lsb, sizeof(union LSB), 1, tmpFile);
        *(txt + i) = strtol(lsb.znak, &tmp2, 2);
    }
    fclose(tmpFile);
    fclose(file);
    *(txt + (size - 1)) = '\0';
    return 0;
}