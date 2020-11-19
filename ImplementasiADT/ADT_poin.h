/*ADT POIN*/

#ifndef POIN_H
#define POIN_H

#include "boolean.h"

typedef struct {
    int X;
    int Y;
} Poin;

typedef struct {
	char Isi[5][5];
} Peta;

typedef struct {
    Poin PosisiPemain;
    Peta* KuadranPeta;
    char SimbolPemain;
    char SimbolPetak;
} Pemain;

#endif
