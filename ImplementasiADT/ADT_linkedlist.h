/*ADT Linked List*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

#define Nil NULL

typedef struct tElmtLinkedList *addressLL;
typedef struct tElmtLinkedList{
	int indeks;
	addressLL next;
} ElmtLinkedList;
typedef struct{
	addressLL first;
} LinkedList;

// Linked List kosong adalah list yang firstnya bernilai Nil
// Setiap elemen list beraddress P dapat didapat dengan infoidx(P)
// Elemen setelah address P adalah Next(P)
// Elemen terakhir aadalah elemen P yang mememnuhi Next(P) = Nil

#define InfoIdx(P) (P)->indeks
#define Next(P) (P)->next
#define First(L) ((L).first) 

/********PREDIKAT**********/
boolean LLKosong(LinkedList LL);

/*******KONSTRUKTOR********/
void BuatLL(LinkedList *LL);

/*********MANAJEMEN MEMORI**********/
addressLL AlokasiLL(int idx);

void DealokasiLL(addressLL *P);

/*********OPERASI PENAMBAHAN***********/
void InsVLast(LinkedList *LL, int idx);

#endif
