#include <stdio.h>

unsigned long long add(unsigned long long a, unsigned long long b);

int main() {
    unsigned long long a;
    unsigned long long b;
    printf("Enter numbers: ");
    if(!scanf("%llu", &a)){
        printf("Incorrect input");
        return 1;
    }
    if(!scanf("%llu", &b)){
        printf("Incorrect input");
        return 1;
    }
    printf("%llu", add(a, b));
    return 0;
}

unsigned long long add(unsigned long long a, unsigned long long b){
    unsigned long long x;
    while (b != 0)
    {
        x = a & b;
        a = a ^ b;
        b = x << 1;
    }
    return a;
}
