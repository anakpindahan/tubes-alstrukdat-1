/*ADT Stack*/

#ifndef STACK_H
#define STACK_H

#include "../Boolean/boolean.h"

typedef int Tupel[10];
//Tupel berisi [comm, w, u, b1, b2, b3, up, X, Y]
// comm: perintah yang akan dikerjakan, 1: build, 2: upgrade, 3: buy
// w: id wahana yang dibangun, jika tidak ada, 0
// u: uang yang dihabiskan, jika tidak ada, 0
// b1: bahanbangunan1 yang dihabiskan, jika tidak ada, 0
// b2: bahanbangunan2 yang dihabiskan, jika tidak ada, 0
// b3: bahanbangunan3 yang dihabiskan, jika tidak ada, 0
// up: id wahana hasil upgrade, jika tidak ada, 0
// X: posisi X build, jika tidak ada, -999
// Y: posisi Y build, jika tidak ada, -999

typedef struct {
	Tupel T[25];
	int TOP;
} Stack;

/*****************SELEKTOR*************/
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/****************KONSTRUKTOR************/
void BuatStack(Stack *S);

/***************PREDIKAT*****************/
boolean StackKosong(Stack S);

boolean StackPenuh(Stack S);

/****************TAMBAH/HAPUS**************/
void Push(Stack *S, Tupel X);

void Pop(Stack *S, Tupel *X);

#endif

