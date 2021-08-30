#include <stdio.h>

int longest_series(unsigned int x);

int main() {
    unsigned int x;
    printf("Enter number: ");
    if(!scanf("%u", &x)){
        printf("Incorrect input");
        return 1;
    }
    printf("%u", longest_series(x));
    return 0;
}

int longest_series(unsigned int x){
    int i = 0;
    int tmp = 0;
    unsigned int status = 0;
    for(unsigned int j = 0; j < 32; ++j){
        status = (x >> j) & 1;
        if(status == 1)
            tmp++;
        else{
            if(tmp > i)
                i = tmp;
            tmp = 0;
        }
    }
    if(tmp > i)
        i = tmp;
    tmp = 0;
    return i;
}