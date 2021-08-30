//
// Created by root on 5/27/21.
//

#ifndef INC_5_6_BIG_NUMBERS_H
#define INC_5_6_BIG_NUMBERS_H
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

int compare(const char* number1, const char* number2);

int save_big_numbers_b(const struct big_numbers_t *bn, const char *filename);

int load_big_numbers_b(struct big_numbers_t **bn, const char *filename);

int sort_big_numbers_asc(struct big_numbers_t *bn);

char* total_sum_big_numbers(const struct big_numbers_t *bn, int *err_code);

int subtract(const char* number1, const char* number2, char** result);

int add(const char* number1, const char* number2, char** result);

int compare1(const void * number1, const void * number2);

#endif //INC_5_6_BIG_NUMBERS_H
