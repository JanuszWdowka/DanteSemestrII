//
// Created by root on 5/26/21.
//

#ifndef INC_5_5_BIG_NUMBERS_H
#define INC_5_5_BIG_NUMBERS_H
struct big_numbers_t {
    int size;
    int capacity;
    char **big_number;
};

int create(struct big_numbers_t *bn, int capacity);
int create_big_numbers(struct big_numbers_t **bn, int capacity);

void destroy(struct big_numbers_t *bn);
void destroy_big_numbers(struct big_numbers_t **bn);

int add_big_number(struct big_numbers_t *bn, const char *big_number);

void display(const struct big_numbers_t *bn);

int validate(const char *number);


#endif //INC_5_5_BIG_NUMBERS_H
