/*ADT KATA*/
#ifndef KATA_H
#define KATA_H

#include "boolean.h"

typedef struct {
    char TabKata[50];
    int Length;
} Kata;

/*****************KONSTRUKTOR*********************/
Kata createKata(char string[]);

/*****************PENGECEKAN*********************/
boolean isKataSama(Kata kata1, Kata kata2);

/*****************OUTPUT*************************/
void printKata(Kata kata);

#endif
