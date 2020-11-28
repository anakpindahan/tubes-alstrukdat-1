/*Implementasi ADT Stack*/

#include "../Boolean/boolean.h"
#include "ADT_stack.h"

/*****************SELEKTOR*************/
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/****************KONSTRUKTOR************/
void BuatStack(Stack *S)
{
	Top(*S) = -1;
}

/***************PREDIKAT*****************/
boolean StackKosong(Stack S)
{
	return (Top(S) == -1);
}

boolean StackPenuh(Stack S)
{
	return (Top(S) == 19);
}

/****************TAMBAH/HAPUS**************/
void Push(Stack *S, Tupel X)
{
	int i;
	Top(*S)++;
	for(i = 0; i < 10; i++){
		InfoTop(*S)[i] = X[i];
	}
	
}

void Pop(Stack *S, Tupel *X)
{
	int i;
	for(i = 0; i < 10; i++){
		(*X)[i] = InfoTop(*S)[i];
	}
	Top(*S)--;
}
