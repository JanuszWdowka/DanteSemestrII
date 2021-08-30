#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int validate(const char *number);
int compare(const char* number1, const char* number2);

int main() {
    char* number1;
    char* number2;
    char* result;
    int x;
    number1 = malloc(201 * sizeof(char));
    if(number1 == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    number2 = malloc(201 * sizeof(char));
    if(number2 == NULL){
        printf("Failed to allocate memory");
        free(number1);
        return 8;
    }
    printf("Podaj pierwsza liczbe: ");
    scanf("%200s", number1);
    while (getchar() != '\n');
    printf("Podaj druga liczbe: ");
    scanf("%200s", number2);
    while (getchar() != '\n');
    x = add(number1, number2, &result);
    if(x == 2){
        printf("Incorrect input");
        free(number1);
        free(number2);
        return 1;
    }
    if(x == 3){
        printf("Failed to allocate memory");
        free(number1);
        free(number2);
        return 8;
    }
    printf("%s", result);

    free(result);
    x = subtract(number1, number2, &result);
    if(x == 2){
        printf("Incorrect input");
        free(number1);
        free(number2);
        return 1;
    }
    if(x == 3){
        printf("Failed to allocate memory");
        free(number1);
        free(number2);
        return 8;
    }
    printf("\n%s", result);
    free(result);
    free(number1);
    free(number2);
    return 0;
}


int subtract(const char* number1, const char* number2, char** result){
    if(number1 == NULL || number2 == NULL || result == NULL){
        return 1;
    }
    if(validate(number1) == 2 || validate(number2) == 2)
        return 2;
    if(*(number2 + 0) != '-' && *(number1 + 0) == '-'){
        int r = add(number1 + 1, number2, result);
        if(r == 0){
            int lenght = strlen(*result);
            if((*(number1 + 1) - 48 + *(number2 + 0) - 48 ) >= 10){
                void *newpointer;
                if((newpointer = (char*) realloc(*result,(lenght + 2) * sizeof(char)))  == NULL){
                    free(*result);
                    return 2;
                }
                else{
                    *result = newpointer;
                }
            }
            for(int j = lenght; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = '-';
            *(*result + lenght + 1) = '\0';
        }
        return r;
    }
    else if(*(number2 + 0) == '-' && *(number1 + 0) != '-'){
        int r = add(number1, number2 + 1, result);
        return r;
    }
    else if(*(number2 + 0) == '-' && *(number1 + 0) == '-'){
        int r = subtract(number1 + 1, number2 + 1, result);
        if(r == 0){
            if(compare(number1, number2) == 1){
                int lenght = strlen(*result);
                for(int i = 0; i < lenght - 1; ++i){
                    *(*result + i) = *(*result + i + 1);
                }
                *(*result + lenght - 1) = '\0';
            }
            else if(compare(number1, number2) == -1){
                int lenght = strlen(*result);
                for(int j = lenght; j > 0; --j){
                    *(*result + j) = *(*result + j - 1);
                }
                *(*result + 0) = '-';
                *(*result + lenght + 1) = '\0';
            }
        }
        return r;
    }
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    int diff;
    if(lenght1 >= lenght2){
        *result = calloc((lenght1 + 2), sizeof(char));
        diff = lenght1 - lenght2;
    }
    else{
        *result = calloc((lenght2 + 2), sizeof(char));
        diff = lenght2 - lenght1;
    }
    if (*result == NULL)
        return 3;
    int carry = 0;
    int j = 0;
    //odjemowanie dwóch dodatnich
    if(*(number2 + 0) != '-' && *(number1 + 0) != '-'){
        if(compare(number1, number2) == 1 || compare(number1, number2) == 0){
            j = lenght1 - 1;
            for (int i = lenght2 - 1; i >= 0; i--) {
                int sub = ((*(number1 + i + diff) - '0') - (*(number2 + i) - '0')
                           - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                    carry = 0;

                *(*result + j) = sub + '0';
                --j;
            }
            for (int i = lenght1 - lenght2 - 1; i >= 0; i--) {
                if (*(number1 + i) == '0' && carry) {
                    *(*result + j) = '9';
                    --j;
                    continue;
                }
                int sub = ((*(number1 + i) - '0') - carry);
                if (i >= 0 || sub > 0)
                    *(*result + j) = sub + '0';
                --j;
                carry = 0;
            }
            if(compare(number1, number2) == 1){
                while(*(*result + 0) == '0'){
                    int lenght = strlen(*result);
                    for(int i = 0; i < lenght - 1; ++i){
                        *(*result + i) = *(*result + i + 1);
                    }
                    *(*result + lenght - 1) = '\0';
                }
            }
            else{
                while(*(*result + 0) == '0' && *(*result + 1) == '0'){
                    int lenght = strlen(*result);
                    for(int i = 0; i < lenght - 1; ++i){
                        *(*result + i) = *(*result + i + 1);
                    }
                    *(*result + lenght - 1) = '\0';
                }
            }
        }
        else{
            j = lenght2 - 1;
            for (int i = lenght1 - 1; i >= 0; i--) {
                int sub = ((*(number2 + i + diff) - '0') - (*(number1 + i) - '0')
                           - carry);
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                    carry = 0;

                *(*result + j) = sub + '0';
                --j;
            }
            for (int i = lenght2 - lenght1 - 1; i >= 0; i--) {
                if (*(number2 + i) == '0' && carry) {
                    *(*result + j) = '9';
                    --j;
                    continue;
                }
                int sub = ((*(number2 + i) - '0') - carry);
                if (i >= 0 || sub > 0)
                    *(*result + j) = sub + '0';
                --j;
                carry = 0;
            }
            int lenght = strlen(*result);
            for(int i = lenght + 1; i > 0; --i){
                *(*result + i) = *(*result + i - 1);
            }
            while(*(*result + 0) == '0' && *(*result + 1) == '0'){
                int lenght = strlen(*result);
                for(int i = 0; i < lenght - 1; ++i){
                    *(*result + i) = *(*result + i + 1);
                }
                *(*result + lenght - 1) = '\0';
            }
            *(*result + 0) = '-';
        }
    }
    return 0;
}

int add(const char* number1, const char* number2, char** result){
    if(number1 == NULL || number2 == NULL || result == NULL){
        return 1;
    }
    if(validate(number1) == 2 || validate(number2) == 2)
        return 2;
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    int krotszy;
    if(*(number1 + 0) == '-' &&  *(number2 + 0) != '-'){

        int r = subtract(number2, number1 + 1, result);
        return r;
    }
    else if(*(number1 + 0) != '-' &&  *(number2 + 0) == '-'){

        int r = subtract(number1, number2 + 1, result);
        return r;
    }
    if(lenght1 >= lenght2){
        *result = calloc((lenght1 + 2), sizeof(char));
        krotszy = lenght2;
    }
    else{
        *result = calloc((lenght2 + 2), sizeof(char));
        krotszy = lenght1;
    }
    if (*result == NULL)
        return 3;
    //zmienne do obliczania sumy
    int w, p = 0;
    int i = 0;
    char tmp1, tmp2;
    int l;
    if(*(number1 + 0) != '-' &&  *(number2 + 0) != '-'){
        for(int j = 1; j <= krotszy; j++)
        {
            w  = (int)*(number1 + --lenght1) + (int)*(number2 + --lenght2) + p - 96;
            p  = w / 10;
            l = strlen(*result);
            if(l > 0) {
                tmp1 = *(*result + 0);
                *(*result + 0) = (char) ((w % 10) + 48);
                for (int q = 0; q < l; ++q) {
                    if ((q + 1) < l)
                        tmp2 = *(*result + q + 1);
                    *(*result + q + 1) = tmp1;
                    tmp1 = tmp2;
                }
            }
            else{
                *(*result + 0) = (char)((w % 10) + 48);
            }
            ++i;
        }
        while(lenght1)
        {
            w  = (int)*(number1 + --lenght1) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            tmp1 = *(*result + 0);
            *(*result + 0) = (char) ((w % 10) + 48);
            for (int q = 0; q < l; ++q) {
                if ((q + 1) < l)
                    tmp2 = *(*result + q + 1);
                *(*result + q + 1) = tmp1;
                tmp1 = tmp2;
            }
            ++i;
        }
        while(lenght2)
        {
            w  = (int)*(number2 + --lenght2) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            tmp1 = *(*result + 0);
            *(*result + 0) = (char) ((w % 10) + 48);
            for (int q = 0; q < l; ++q) {
                if ((q + 1) < l)
                    tmp2 = *(*result + q + 1);
                *(*result + q + 1) = tmp1;
                tmp1 = tmp2;
            }
            ++i;
        }
        if(p){
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char)(p + 48);
            ++i;
        }
    }
    else{
        int a;
        int b;
        for(int j = 1; j <= krotszy; j++)
        {
            a = (int)*(number1 + --lenght1);
            b = (int)*(number2 + --lenght2);
            if(a != '-' && b != '-'){
                w  = a + b + p - 96;
                p  = w / 10;
                l = strlen(*result);
                if(l > 0) {
                    tmp1 = *(*result + 0);
                    *(*result + 0) = (char) ((w % 10) + 48);
                    for (int q = 0; q < l; ++q) {
                        if ((q + 1) < l)
                            tmp2 = *(*result + q + 1);
                        *(*result + q + 1) = tmp1;
                        tmp1 = tmp2;
                    }
                }
                else{
                    *(*result + 0) = (char)((w % 10) + 48);
                }
                ++i;
            }
        }
        if(lenght1 == 0 && lenght2 != 0)
            lenght2++;
        else if(lenght1 != 0 && lenght2 == 0)
            lenght1++;
        while(lenght1 > 1)
        {
            w  = (int)*(number1 + --lenght1) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char) ((w % 10) + 48);
            ++i;
        }
        while(lenght2 > 1)
        {
            w  = (int)*(number2 + --lenght2) + p - 48;
            p  = w / 10;
            l = strlen(*result);
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char) ((w % 10) + 48);
            ++i;
        }
        if(p){
            for(int j = i; j > 0; --j){
                *(*result + j) = *(*result + j - 1);
            }
            *(*result + 0) = (char)(p + 48);
            ++i;
        }
        for(int j = i; j > 0; --j){
            *(*result + j) = *(*result + j - 1);
        }
        *(*result + 0) = '-';
        ++i;
    }
    *(*result + i) = '\0';
    return 0;
}
int validate(const char *number){
    if(number == NULL){
        return -1;
    }
    char buf;
    int x = 0;
    int i = 0;
    if(*(number + 0) == '\0' || (*(number + 0) == '0' && *(number + 1) != '\0') || (*(number + 0) == '-' && *(number + 1) == '\0'))
        return 2;
    while (*(number + i) != '\0'){
        buf = *(number + i);
        if((buf < 48 || buf > 57) && buf != 45){
            return 2;
        }
        if(buf == 45 && x == 0){
            x = -1;
        }
        else if(buf == 45 && x == -1){
            return 2;
        }
        ++i;
    }
    return 0;
}
int compare(const char* number1, const char* number2){
    if(number1 == NULL || number2 == NULL)
        return 2;
    if(validate(number1) == 2 || validate(number2) == 2)
        return 3;
    if(*(number1 + 0) == '-' && *(number2 + 0) != '-')
        return -1;
    if(*(number1 + 0) != '-' && *(number2 + 0) == '-')
        return 1;
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    if(lenght1 > lenght2){
        if(*(number1 + 0) != '-' && *(number2 + 0) != '-')
            return 1;
        else
            return -1;
    }
    if(lenght2 > lenght1){
        if(*(number1 + 0) != '-' && *(number2 + 0) != '-')
            return -1;
        else
            return 1;
    }

    int a;
    int b;
    int i = 0, j = 0;
    if(*(number1 + 0) != '-' && *(number2 + 0) != '-'){
        while (lenght1 > i && lenght2 > j){
            a = (int)*(number1 + i);
            b = (int)*(number2 + j);
            a -= 48;
            b -= 48;
            if(a > b)
                return 1;
            if(b > a)
                return -1;
            ++i;
            ++j;
        }
    }
    else{
        ++i; ++j;
        while (lenght1 > i && lenght2 > j){
            a = (int)*(number1 + i);
            b = (int)*(number2 + j);
            a -= 48;
            b -= 48;
            if(a < b)
                return 1;
            if(b < a)
                return -1;
            ++i;
            ++j;
        }
    }
    return 0;
}