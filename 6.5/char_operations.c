//
// Created by root on 5/13/21.
//

#include <string.h>
#include <stdlib.h>
#include "char_operations.h"

char lower_to_upper(char ch){
    if(ch > 96 && ch < 123){
        ch -= 32;
    }
    return ch;
}
char upper_to_lower(char ch){
    if(ch > 64 && ch < 91){
        ch += 32;
    }
    return ch;
}
char space_to_dash(char ch){
    if(ch == 32){
        ch = 95;
    }
    return ch;
}
char reverse_letter(char ch){
    if(ch > 96 && ch < 123){
        ch = 'z' - ch + 'a';
    }
    if(ch > 64 && ch < 91){
        ch = 'Z' - ch + 'A';
    }
    return ch;
}
char* letter_modifier(const char* input_text, char (*fun)(char)){
    if(input_text == NULL || fun == NULL)
        return NULL;
    size_t howLong = strlen(input_text);
    char* txt = (char *) malloc((howLong + 1) * sizeof(char));
    if(txt == NULL)
        return NULL;
    for(size_t i = 0; i < howLong; ++i){
        *(txt + i) = fun(*(input_text + i));
    }
    *(txt + howLong) = '\0';
    return txt;
}