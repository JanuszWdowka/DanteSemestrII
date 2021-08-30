//
// Created by root on 5/11/21.
//
#ifndef INC_6_8_COMPARATORS_H
#define INC_6_8_COMPARATORS_H
#include <stddef.h>

struct point_t
{
    double x;
    double y;
};
int comp_int(const void * a, const void * b);
int comp_double(const void * a, const void * b);
int comp_point(const void *a, const void * b);
int sort(void* ptr, int size, size_t sizeo, int comparator(const void *ptr1, const void *ptr2));
#endif //INC_6_8_COMPARATORS_H
