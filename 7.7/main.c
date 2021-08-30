#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct point_t {
    int x;
    int y;
};
char *convert(int num, int base, int* x);
int my_printf(char * str, ...);
int my_scanf(char * str, ...);

int main() {
    return 0;
}

int my_printf(char* format, ...)
{
    char *traverse;
    int i;
    char *s;
    struct point_t p;
    double f;
    int x = 0;
    va_list zmienne;

    va_start(zmienne, format);
    int error = 0;
    for(traverse = format; *traverse != '\0'; ++traverse)
    {
        while(*traverse != '%')
        {
            if(*traverse == '\0'){
                error = 1;
                break;
            }
            ++x;
            putchar(*traverse);
            ++traverse;
        }
        if(error == 1)
            break;
        ++traverse;

        switch(*traverse)
        {
            case 'd':
                i = va_arg(zmienne, int);

                if(i < 0)
                {
                    i = -i;
                    putchar('-');
                    ++x;
                }
                fputs(convert(i,10, &x), stdout);
                break;

            case 's':
                s = va_arg(zmienne, char*);
                x += (int)strlen(s);
                for(int j = 0; *(s + j) != '\0'; ++j)
                    putchar(*(s + j));
                //fputs(s, stdout);
                break;
            case 'p':
                p = va_arg(zmienne, struct point_t);
                fputs("(", stdout);
                x++;
                if(p.x < 0)
                {
                    p.x = -p.x;
                    putchar('-');
                    ++x;
                }
                fputs(convert(p.x,10, &x), stdout);
                fputs(" ", stdout);
                x++;
                if(p.y < 0)
                {
                    p.y = -p.y;
                    putchar('-');
                    ++x;
                }
                fputs(convert(p.y,10, &x), stdout);
                fputs(")", stdout);
                x++;
                break;
            case 'f':
                f = va_arg(zmienne, double);
                if(f < 0){
                    f = -f;
                    putchar('-');
                    ++x;
                }
                double cale, poPrzecinku;
                poPrzecinku = modf(f, &cale);
                fputs(convert((int)cale, 10, &x), stdout);
                fputs(".", stdout);
                x++;
                f -= cale;
                for(int i = 0; i < 5; ++i){
                    f *= 10;
                    poPrzecinku = modf(f, &cale);
                    poPrzecinku--;
                    fputs(convert((int)cale, 10, &x), stdout);
                    f -= cale;
                }

        }
    }
    va_end(zmienne);
    return x;
}

char *convert(int num, int base, int* x)
{
    static char Representation[]= "0123456789";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *(x) += 1;
        *--ptr = Representation[num%base];
        num /= base;
    }while(num != 0);

    return(ptr);
}



int my_scanf(char * str, ...){
    va_list args;
    int ret = 0;
    va_start(args, str);
    for(;*str != '\0';str++){
        if (*str == '%'){
            str++;
            if (*str == 'd'){
                char buf;
                int i = 0, ch;
                int* a = va_arg(args, int*);
                *a = 0;
                int x = 1;
                while ((ch = getchar()) != EOF && !isspace(ch)){
                    buf = (char)ch;
                    if((buf < 48 || buf > 57) && buf != 45)
                        break;
                    if(buf == 45){
                        x = -1;
                    }
                    else{
                        buf -= 48;
                        *a = *a * 10 + buf;
                        ++i;
                    }

                }

                if (i == 0)
                    break;
                else
                    *a *= x;
                ++ret;
            }
            else if(*str == 'f'){
                char buf;
                int i = 0, ch;
                double * a = va_arg(args, double *);
                *a = 0;
                int x = 1;
                int poKropce = 0;
                double q;
                while ((ch = getchar()) != EOF && !isspace(ch)){
                    buf = (char)ch;
                    if((buf < 48 || buf > 57) && buf != 45 && buf != 46)
                        break;
                    if(buf == 45){
                        x = -1;
                    }
                    else if(buf == 46){
                        poKropce = 1;
                    }
                    else{
                        buf -= 48;
                        if(poKropce == 0){
                            *a = *a * 10 + buf;
                            ++i;
                        }
                        else{
                            q = (double)buf / (double)pow(10, poKropce);
                            *a = *a + q;
                            poKropce++;
                        }
                    }

                }

                if (i == 0)
                    break;
                else
                    *a *= x;
                ++ret;
            }
            else if(*str == 'p'){
                char buf;
                int i = 0, ch;
                struct point_t* a = va_arg(args, struct point_t*);
                a->x = 0;
                a->y = 0;
                int x = 1;
                ch = getchar();
                if(ch == '('){
                    while ((ch = getchar()) != EOF && !isspace(ch)){
                        buf = (char)ch;
                        if((buf < 48 || buf > 57) && buf != 45)
                            break;
                        if(buf == 45){
                            x = -1;
                        }
                        else{
                            buf -= 48;
                            a->x = a->x * 10 + buf;
                            ++i;
                        }

                    }
                    if (i == 0)
                        break;
                    else
                        a->x *= x;
                }
                x = 1; i = 0;
                while ((ch = getchar()) != EOF && !isspace(ch) && ch != ')'){
                    buf = (char)ch;
                    if((buf < 48 || buf > 57) && buf != 45)
                        break;
                    if(buf == 45){
                        x = -1;
                    }
                    else{
                        buf -= 48;
                        a->y = a->y * 10 + buf;
                        ++i;
                    }

                }
                while ((ch = getchar()) != EOF && !isspace(ch));
                if (i == 0)
                    break;
                else
                    a->y *= x;
                ret += 2;
            }
            else {
                break;
            }

        }
    }
    va_end(args);
    return ret;
}