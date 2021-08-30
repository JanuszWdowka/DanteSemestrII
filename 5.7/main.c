#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int multiply(const char* number1, const char* number2, char** result);
int validate(const char *number);
int compare(const char* number1, const char* number2);
int validate_expression(const char *expr);
int calculate(const char* expr, char **result);

int main() {
    char* res;
    char* calc;
    calc = calloc(501, sizeof(char ));
    if(calc == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wyrazenie: ");
    scanf("%500s", calc);
    int r = calculate(calc, &res);
    if(r == 3){
        printf("Failed to allocate memory");
        free(calc);
        return 8;
    }
    else if(r == 2){
        printf("Incorrect input");
        free(calc);
        return 1;
    }
    printf("%s", res);
    free(calc);
    free(res);
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

int multiply(const char* number1, const char* number2, char** result){
    if(number1 == NULL || number2 == NULL || result == NULL){
        return 1;
    }
    if(validate(number1) == 2 || validate(number2) == 2)
        return 2;
    if(*(number1 + 0) == '-' &&  *(number2 + 0) == '-'){
        int r = multiply(number1 + 1, number2 + 1, result);
        return r;
    }
    else if(*(number1 + 0) != '-' &&  *(number2 + 0) == '-'){
        int r = multiply(number1, number2 + 1, result);
        if(r == 0 && *(*result + 0) != '0'){
            int lenght = strlen(*result);
            if((*(number1 + 1) - 48 * *(number2 + 0) - 48 ) >= 10){
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
    else if(*(number1 + 0) == '-' &&  *(number2 + 0) != '-'){
        int r = multiply(number1 + 1, number2, result);
        if(r == 0 && *(*result + 0) != '0'){
            int lenght = strlen(*result);
            if((*(number1 + 1) - 48 * *(number2 + 0) - 48 ) >= 10){
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
    int lenght1 = strlen(number1);
    int lenght2 = strlen(number2);
    int i_n1 = 0;
    int i_n2 = 0;
    int carry = 0;
    int c1 = 0; //od pierwszej liczby
    int c2 = 0; //od drugiej liczby znak
    int sum = 0;
    *result = calloc((lenght1 + lenght2 + 2), sizeof(char));
    if(*result == NULL)
        return 3;
    if(*(number1 + 0) == '0' || *(number2 + 0) == '0'){
        *(*result + 0) = '0';
        *(*result + 1) = '\0';
        return 0;
    }
    for(int i = lenght2 - 1; i >= 0; i--){
        carry = 0;
        c1 = *(number2 + i) - '0';
        i_n2 = 0;
        for (int j = lenght1 - 1; j >= 0; j--){
            c2 = *(number1 + j) - '0';
            int fromRes = 0;
            if(*(*result + i_n1 + i_n2) != 0){
                fromRes = (*(*result + i_n1 + i_n2) - '0');
            }
            sum = c1 * c2 + fromRes + carry;
            *(*result + i_n1 + i_n2) = sum % 10 + '0';
            carry = sum / 10;
            i_n2 += 1;
        }
        if (carry > 0)
            *(*result + i_n1 + i_n2) += carry + '0';
        i_n1 += 1;
    }
    int i = strlen(*result) - 1;
    while (i>=0 && (*result + i) == 0)
        i--;
    if (i == -1){
        *(*result + 0) = '0';
        *(*result + 1) = '\0';
        return 0;
    }
    int l = strlen(*result);
    char c = 0;
    for(int j = 0; j < l; ++j){
        l--;
        c = *(*result + j);
        *(*result + j) = *(*result + l);
        *(*result + l) = c;
    }
    l = strlen(*result);
    *(*result + l + 1) = '\0';
    return 0;
}

int validate_expression(const char *expr){
    if(expr == NULL)
        return 2;
    if((*(expr + 0) < '0' || *(expr + 0) > '9')){
        if(*(expr + 0) != '-')
            return 1;
    }
    int len = strlen(expr) + 1;
    for(int i = 0; i < len; ++i){
        if(*(expr + i) == '\0')
            break;
        if((*(expr + i) < '0' || *(expr + i) > '9')){
            if(*(expr + i) != '-' && *(expr + i) != '+' && *(expr + i) != '*')
                return 1;
            else{
                if(*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*')
                    if(*(expr + i + 1) == '+' || *(expr + i + 1) == '*' || *(expr + i + 1) == '\0')
                        return 1;
            }
        }
    }
    return 0;
}
int calculate(const char* expr, char **result){
    if(result == NULL || expr == NULL){
        return 1;
    }
    if(validate_expression(expr) != 0){
        return 2;
    }
    int len = strlen(expr);
    int positionEndLastOperation = 0;
    char* number1 = NULL;
    char* number2 = NULL;
    char* tmpRes1 = NULL;
    char* tmpRes2 = NULL;
    int firstOperation = 0;
    int firstNumber = 0;
    char operation;
    int isNegativ = 0;
    int i = 0;
    int j = 0;
    int numberOfOperations = 0;
    if(*(expr + 0) == '-'){
        isNegativ = 1;
        ++i;
        positionEndLastOperation = i;
    }
    for(; *(expr + i) != '\0' && firstNumber == 0; ++i){
        if(*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*'){
            operation = *(expr + i);
            if(firstNumber == 0){
                firstNumber = 1;
                number1 = calloc(i + 1, sizeof(char));
                if(number1 == NULL)
                    return 3;
                if(isNegativ){
                    *(number1 + 0) = '-';
                    isNegativ = 0;
                }
                for(j = positionEndLastOperation; j < i; ++j){
                    *(number1 + j) = *(expr + j);
                }
                *(number1 + j) = '\0';
                if(*(expr + i + 1) == '-'){
                    isNegativ = 1;
                    ++i;
                }
                positionEndLastOperation = i + 1;
            }
        }
    }
    for(; *(expr + i) != '\0' && *(expr + i) != '-' && *(expr + i) != '+' && *(expr + i) != '*'; ++i);
    if((*(expr + i) == '\0' || *(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*') && firstNumber == 1)
        firstOperation = 1;
    number2 = calloc(i - positionEndLastOperation + 2, sizeof(char));
    if(number2 == NULL){
        free(number1);
        return 3;
    }
    if(isNegativ){
        *(number2 + 0) = '-';
        isNegativ = 0;
    }
    for(j = positionEndLastOperation; j < i; ++j){
        if(*(number2 + 0) != '-')
            *(number2 + j - positionEndLastOperation) = *(expr + j);
        else
            *(number2 + j - positionEndLastOperation + 1) = *(expr + j);
    }
    if(*(number2 + 0) != '-')
        *(number2 + j - positionEndLastOperation) = '\0';
    else
        *(number2 + j - positionEndLastOperation + 1) = '\0';
    positionEndLastOperation = i + 1;
    if(operation == '+'){
        add(number1, number2, &tmpRes1);
        free(number1);
        free(number2);
        numberOfOperations++;
    }
    else if(operation == '-'){
        subtract(number1, number2, &tmpRes1);
        free(number1);
        free(number2);
        numberOfOperations++;
    }
    else if(operation == '*'){
        multiply(number1, number2, &tmpRes1);
        free(number1);
        free(number2);
        numberOfOperations++;
    }
    operation = *(expr + i);
    if(i + 1 < len && *(expr + i + 1) == '-'){
        isNegativ = 1;
        i += 2;
    }
    if(numberOfOperations != 0){
        while(*(expr + i) != '\0'){
            if(numberOfOperations % 2 == 0){
                ++i;
                while(*(expr + i) != '\0' && *(expr + i) != '-' && *(expr + i) != '+' && *(expr + i) != '*'){
                    ++i;
                }
                number2 = calloc(i - positionEndLastOperation + 2, sizeof(char));
                if(number2 == NULL){
                    free(tmpRes2);
                    return 3;
                }
                if(isNegativ){
                    *(number2 + 0) = '-';
                    isNegativ = 0;
                }
                if(*(expr + positionEndLastOperation) == '-' || *(expr + positionEndLastOperation) == '+' || *(expr + positionEndLastOperation) == '*')
                    positionEndLastOperation++;
                for(j = positionEndLastOperation; j < i; ++j){
                    if(*(number2 + 0) != '-')
                        *(number2 + j - positionEndLastOperation) = *(expr + j);
                    else
                        *(number2 + j - positionEndLastOperation + 1) = *(expr + j);
                }
                if(*(number2 + 0) == '*' || *(number2 + 0) == '+'){
                    int x = strlen(number2);
                    for(int a = 0; a < x; ++a){
                        *(number2 + a) = *(number2 + a + 1);
                    }
                    *(number2 + x) = '\0';
                }
                if(*(number2 + 0) != '-')
                    *(number2 + j - positionEndLastOperation) = '\0';
                else
                    *(number2 + j - positionEndLastOperation + 1) = '\0';
                if(i + 1 < len && *(expr + i + 1) == '-'){
                    isNegativ = 1;
                    i += 2;
                }
                positionEndLastOperation = i;
                if(operation == '+'){
                    add(tmpRes2, number2, &tmpRes1);
                    free(number2);
                    free(tmpRes2);
                }
                else if(operation == '-'){
                    subtract(tmpRes2, number2, &tmpRes1);
                    free(number2);
                    free(tmpRes2);
                }
                else if(operation == '*'){
                    multiply(tmpRes2, number2, &tmpRes1);
                    free(number2);
                    free(tmpRes2);
                }
                if(isNegativ == 1)
                    operation = *(expr + i - 2);
                else
                    operation = *(expr + i);
            }
            else{
                ++i;
                if(*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*')
                    ++i;
                while(*(expr + i) != '\0' && *(expr + i) != '-' && *(expr + i) != '+' && *(expr + i) != '*'){
                    ++i;
                }
                number2 = calloc(i - positionEndLastOperation + 2, sizeof(char));
                if(number2 == NULL){
                    free(tmpRes1);
                    return 3;
                }
                if(isNegativ){
                    *(number2 + 0) = '-';
                    isNegativ = 0;
                }
                if(*(expr + positionEndLastOperation) == '-' || *(expr + positionEndLastOperation) == '+' || *(expr + positionEndLastOperation) == '*')
                    positionEndLastOperation++;
                for(j = positionEndLastOperation; j < i; ++j){
                    if(*(number2 + 0) != '-')
                        *(number2 + j - positionEndLastOperation) = *(expr + j);
                    else
                        *(number2 + j - positionEndLastOperation + 1) = *(expr + j);
                }
                if(*(number2 + 0) == '*' || *(number2 + 0) == '+'){
                    int x = strlen(number2);
                    for(int a = 0; a < x; ++a){
                        *(number2 + a) = *(number2 + a + 1);
                    }
                    *(number2 + x) = '\0';
                }
                if(*(number2 + 0) != '-')
                    *(number2 + j - positionEndLastOperation) = '\0';
                else
                    *(number2 + j - positionEndLastOperation + 1) = '\0';
                if(i + 1 < len && *(expr + i + 1) == '-'){
                    isNegativ = 1;
                    i += 2;
                }
                positionEndLastOperation = i;
                if(operation == '+'){
                    add(tmpRes1, number2, &tmpRes2);
                    free(number2);
                    free(tmpRes1);
                }
                else if(operation == '-'){
                    subtract(tmpRes1, number2, &tmpRes2);
                    free(number2);
                    free(tmpRes1);
                }
                else if(operation == '*'){
                    multiply(tmpRes1, number2, &tmpRes2);
                    free(number2);
                    free(tmpRes1);
                }
                if(isNegativ == 1)
                    operation = *(expr + i - 2);
                else
                    operation = *(expr + i);
            }
            numberOfOperations++;
        }
    }
    if(firstOperation == 0){
        *result = calloc(len + 1, sizeof(char));
        if(*result == NULL){
            return 3;
        }
        for(int i = 0; i < len; ++i){
            *(*result + i) = *(expr + i);
        }
        free(number2);
        *(*result + len) = '\0';
    }
    else{
        if(numberOfOperations % 2 == 1){
        add(tmpRes1, "0", result);
        free(tmpRes1);
        }
        else{
            add(tmpRes2, "0", result);
            free(tmpRes2);
        }
    }
    return 0;
}