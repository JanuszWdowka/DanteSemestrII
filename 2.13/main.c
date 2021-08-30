#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);

int main() {
    char name[31];
    struct message_t message[100];
    char wiadomosc[3000];
    int result = 0;
    for(int i = 0; i < 3000; ++i){
        *(wiadomosc + i) = 0;
    }
    printf("Enter file name: ");
    scanf("%30s", name);
    result = load_data(message, 100, name);
    if(result == -2){
        printf("Couldn't open file");
        return 4;
    }
    else if(result == -3){
        printf("File corrupted");
        return 6;
    }
    decode_message(message, 100, wiadomosc, 3000);
    printf("%s", wiadomosc);
    return 0;
}

int load_data(struct message_t *cp, int size, const char *filename){
    FILE *file;
    unsigned int n = 0;
    int result;
    if(cp == NULL || size < 1 || filename == NULL){
        return -1;
    }
    if((file = fopen(filename, "rb")) == NULL){
        return -2;
    }
    if (fread(&n, sizeof(unsigned int), 1, file) != 1) {
        fclose(file);
        return -3;
    }
    if(n % sizeof(struct message_t) != 0){
        fclose(file);
        return -3;
    }
    n /= sizeof(struct message_t);
    if (n > (unsigned int) size)
        n = size;
    else
        result = n;

    int structsize = sizeof(struct message_t);
    while (n-- > 0 && fread(cp++, structsize, 1, file) == 1);

    if (feof(file) || ferror(file)){
        fclose(file);
        return -3;
    }
    fclose(file);

    return result;
}
int decode_message(const struct message_t *cp, int size, char *msg, int text_size){
    if(cp == NULL || size < 1 || msg == NULL || text_size < 1){
        return 1;
    }
    unsigned char* IloscTekstu = (unsigned char*) cp;
    int howMuch = 0;
    int j = 0;
    while (isdigit(*IloscTekstu) == 0 && isalpha(*IloscTekstu) == 0){
        IloscTekstu++;
    }
    while (true) {
        if (j == size) {
            *msg = '\0';
            break;
        }
        j++;
        IloscTekstu++;
        if (howMuch + 7 >= text_size - 1) {
            memmove(msg, IloscTekstu, text_size - 1 - howMuch);
            msg += text_size - 1 - howMuch;
            *msg = '\0';
            break;
        }
        memmove(msg, IloscTekstu, 7);
        howMuch += 7;

        msg += 7;
        IloscTekstu += 19;
        if (howMuch + 4 >= text_size) {
            memmove(msg, IloscTekstu, text_size - howMuch - 1);
            msg += text_size - 1 - howMuch;
            *msg = '\0';
            break;
        }
        memmove(msg, IloscTekstu, 4);
        howMuch += 4;
        if (howMuch >= text_size) {
            *msg = '\0';
            break;
        }
        msg += 4;
        IloscTekstu += 4;
        if (*IloscTekstu == '\0' || *(IloscTekstu - 1) == '\0') {
            *msg = '\0';
            break;
        }
    }

    return 0;
}