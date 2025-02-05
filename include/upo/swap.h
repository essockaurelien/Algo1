#ifndef SWAP_H
#define SWAP_H

#include <stddef.h>

// Dichiarazione del tipo item_t
typedef struct {
    int ival;
    double dval;
    char str[10];
} item_t;

// Dichiarazione delle funzioni
void swap1(void *a, void *b, size_t n);
void swap2(void *a, void *b, size_t n);
void test_swap1();
void test_swap2();

#endif // SWAP_H
