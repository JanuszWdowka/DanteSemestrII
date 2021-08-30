//
// Created by root on 5/27/21.
//

#ifndef INC_8_13_FUNCTIONS_H
#define INC_8_13_FUNCTIONS_H

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter){\
    size_t x = sizeof(value);                                                               \
    *pointer_to_bits_set_counter = 0;                                                        \
    *pointer_to_bits_cleared_counter = 0;                                               \
    if(x == 1){                                                                             \
        unsigned char set = 0;                                                                 \
        for(int i = 0; i < 8; ++i){                                                            \
            set = (value >> i) & 1;                                                                  \
            if(set == 1){                                                               \
                *pointer_to_bits_set_counter += 1;\
            }                                                                                       \
            else{                                                                                   \
                *pointer_to_bits_cleared_counter += 1;                                              \
            }                                                                                       \
        }                                                                               \
    }   \
    else if(x == 2){                                                                    \
        unsigned short set = 0;                                                                 \
        for(int i = 0; i < 16; ++i){                                                            \
            set = (value >> i) & 1;                                                                  \
            if(set == 1){                                                               \
                *pointer_to_bits_set_counter += 1;\
            }                                                                                       \
            else{                                                                                   \
                *pointer_to_bits_cleared_counter += 1;                                              \
            }                                                                           \
        }                                                                               \
    }                                                                                       \
    else if(x == 4){                                                                        \
        unsigned int set = 0;                                                                 \
        for(int i = 0; i < 32; ++i){                                                            \
            set = (value >> i) & 1;                                                                  \
            if(set == 1){                                                               \
                *pointer_to_bits_set_counter += 1;\
            }                                                                                       \
            else{                                                                                   \
                *pointer_to_bits_cleared_counter += 1;                                              \
            }                                                                                     \
        }                                                                               \
    }                                                                                       \
    else{                                                                                   \
        unsigned long set = 0;                                                                 \
        for(int i = 0; i < 64; ++i){                                                            \
            set = (value >> i) & 1;                                                                  \
            if(set == 1){                                                               \
                *pointer_to_bits_set_counter += 1;\
            }                                                                                       \
            else{                                                                                   \
                *pointer_to_bits_cleared_counter += 1;                                              \
            }                                                                                    \
        }                                                                               \
        *pointer_to_bits_set_counter = 64 - *pointer_to_bits_cleared_counter;\
    }                                                                                       \
}

#define DISPLAY_BITS(value){\
    size_t x = sizeof(value); \
    if(x == 1){                                                                             \
        unsigned char set = 0;                                                                 \
        for(int i = 7; i >= 0; --i){                                                            \
            set = (value >> i) & 1;                                           \
            printf("%u", set);                                                                                       \
        }                                                                                       \
    }\
    else if(x == 2){                                                                             \
        unsigned short set = 0;                                                                 \
        for(int i = 15; i >= 0; --i){                                                            \
            set = (value >> i) & 1;                                           \
            printf("%u", set);\
        }                                                                                       \
    }                                                                                       \
    else if(x == 4){                                                                        \
        unsigned int set = 0;                                                                 \
        for(int i = 31; i >= 0; --i){                                                            \
            set = (value >> i) & 1;                                           \
            printf("%hu", set);\
        }                                                                                        \
    }                                                                                       \
    else{                                                                                   \
        unsigned long set = 0;                                                                 \
        for(int i = 63; i >= 0; --i){                                                            \
            set = (value >> i) & 1;                                           \
            printf("%lu", set);\
        }                                                                                         \
    }                       \
}

#define REVERSE_BITS(pointer_to_variable){ \
size_t x = sizeof(*pointer_to_variable);   \
\
    if(x == 1){                                                                             \
        unsigned char set = 0;                                                                 \
        for(int i = 0; i < 8; ++i){       \
            set <<= 1;                     \
            if(*pointer_to_variable & 1 == 1)                                            \
                set ^= 1;                  \
            *pointer_to_variable >>= 1;\
        }                                  \
        *pointer_to_variable = set;                                                                                      \
    }                                       \
    else if(x == 2){                                                                             \
        unsigned short set = 0;                                                                 \
        for(int i = 0; i < 16; ++i){       \
            set <<= 1;                     \
            if(*pointer_to_variable & 1 == 1)                                            \
                set ^= 1;                  \
            *pointer_to_variable >>= 1;\
        }                                  \
        *pointer_to_variable = set;\
    }                                                                                       \
    else if(x == 4){                                                                        \
        unsigned int set = 0;                                                                 \
        for(int i = 0; i < 32; ++i){       \
            set <<= 1;                     \
            if(*pointer_to_variable & 1 == 1)                                            \
                set ^= 1;                  \
            *pointer_to_variable >>= 1;\
        }                                  \
        *pointer_to_variable = set;\
    }                                                                                       \
    else{                                                                                   \
        unsigned long set = 0;                                                                 \
        for(int i = 0; i < 64; ++i){       \
        set <<= 1;                     \
            if(*pointer_to_variable & 1 == 1)                                            \
                set ^= 1;                  \
            *pointer_to_variable >>= 1;\
        }                                  \
        *pointer_to_variable = set;\
    }                                                                                       \
}


#endif //INC_8_13_FUNCTIONS_H
