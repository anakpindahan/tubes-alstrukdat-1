/*ADT Linked List*/

#include "boolean.h"
#include "ADT_linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

#define Nil NULL

// Linked List kosong adalah list yang firstnya bernilai Nil
// Setiap elemen list beraddress P dapat didapat dengan infoidx(P)
// Elemen setelah address P adalah Next(P)
// Elemen terakhir aadalah elemen P yang mememnuhi Next(P) = Nil

/********PREDIKAT**********/
boolean LLKosong(LinkedList LL)
{
	return(First(LL) == Nil);
}

/*******KONSTRUKTOR********/
void BuatLL(LinkedList *LL)
{
	First(*LL) = Nil; 
}

/*********MANAJEMEN MEMORI**********/
addressLL AlokasiLL(int idx)
{
	addressLL P;
	P = (ElmtLinkedList *) malloc (sizeof(ElmtLinkedList));
	if(P != Nil){
		InfoIdx(P) = idx;
		Next(P) = Nil;
	}
	return(P);
}

void DealokasiLL(addressLL *P)
{
	free(*P);
}

/*********OPERASI PENAMBAHAN***********/
void InsVLast(LinkedList *LL, int idx)
{
	addressLL last, P;
	P = AlokasiLL(idx);
	if(LLKosong(*LL)){
		if(P != Nil){
			First(*LL) = P;
		}
	} else {
		if(P != Nil){
			last = First(*LL);
			while(Next(last) != Nil){
				last = Next(last);
			}
			Next(last) = P;
		}
	}
}

