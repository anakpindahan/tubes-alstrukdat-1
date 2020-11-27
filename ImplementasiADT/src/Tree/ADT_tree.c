/*IMPLEMENTASI ADT TREE*/

#include "../Boolean/boolean.h"
#include "../LinkedList/ADT_linkedlist.h"
#include "ADT_tree.h"
#include <stdio.h>
#include <stdlib.h>

#define Nil NULL

/*********PREDIKAT************/
boolean TreeKosong(Tree T)
{
	return(T == Nil);
}

boolean TreeSatuElemen(Tree T)
{
	if(!TreeKosong(T)){
		return((Left(T) == Nil) && (Right(T) == Nil));
	}
}

boolean UnerLeft(Tree T)
{
	return(Right(T) == Nil);
}

boolean UnerRight(Tree T)
{
	return(Left(T) == Nil);
}

/********KONSTRUKTOR**********/
void BuatTreeP(TupelUp wahana, Tree Anak, Tree Saudara, Tree* T)
{
	/*KAMUS*/
	int i;
	/*ALGORITMA*/
	*T = (Node *) malloc(sizeof(Node));
	if(*T != Nil){
		for(i = 0; i < 6; i++){
			InfoWahana(*T)[i] = wahana[i];
		}
		Left(*T) = Anak;
		Right(*T) = Saudara; 
	}
}

Tree BuatTreeF(TupelUp wahana, Tree Anak, Tree Saudara)
{
	int i;
	Tree T;
	T = (Node *) malloc(sizeof(Node));
	if(T != Nil){
		for(i = 0; i < 6; i++){
			InfoWahana(T)[i] = wahana[i];
		}
		Left(T) = Anak;
		Right(T) = Saudara; 
	}
}
/**********MANAJEMEN MEMORI***********/
addressNode AlokasiAddressTree(TupelUp wahana)
{
	int i;
	addressNode P;
	P = (Node*) malloc(sizeof(Node));
	if(P != Nil){
		for(i = 0; i < 6; i++){
			InfoWahana(P)[i] = wahana[i];
		}
		Left(P) = Nil;
		Right(P) = Nil;
	}
	return(P);
}

void DealokasiAddressTree(addressNode P)
{
	free(P);
}

/************TRAVERSAL************/
boolean SearchEksistensiIndeks(Tree T, int idx)
// Mengecek apakah ada address node di T yang memuat indeks idx
{
	/*KAMUS*/
	/*ALGORITMA*/
	if(TreeKosong(T)){
		return(false);
	} else if(TreeSatuElemen(T)) {
		return(IDWahana(T) == idx);
	} else {
		return(SearchEksistensiIndeks(Left(T), idx) || SearchEksistensiIndeks(Right(T), idx));
	}	
}
addressNode SearchWahanaDenganIndeks(Tree T, int idx)
// Prasyarat: setiap address node di T memuat indeks yang berbeda dan pasti ada yang nilai indeksnya idx

{
	/*KAMUS*/
	/*ALGORITMA*/
	if(IDWahana(T) == idx){
		return(T);
	} else {
		if(SearchEksistensiIndeks(Left(T), idx)){
			return(SearchWahanaDenganIndeks(Left(T), idx));
		} else {
			return(SearchWahanaDenganIndeks(Right(T), idx));
		}
	}
}

addressNode Predecessor(addressNode Wahana, Tree T)
// Mencari wahana yang apabila diupgrade akan menghasilkan Wahana
{
	return(SearchWahanaDenganIndeks(T, InfoWahana(Wahana)[5]));
}

void TambahUpgrade(int idx, TupelUp NewUp, Tree *T)
// I.S. T terdefinisi dan memuat sebuah wahana yang memiliki indeks idx
// F.S. Terbentuk daun baru yang merupakan left dari wahana berindeks idx jika wahana ini belum memiliki upgrade
// dan menjadi right child dari wahana terakhir hasil upgrade wahana berindeks idx
{
	/*KAMUS*/
	addressNode Node;
	Tree tempWahana;
	/*ALGORITMA*/
	Node = AlokasiAddressTree(NewUp);
	if(Node != Nil){
		if(IDWahana(*T) == idx){
			if(TreeSatuElemen(*T)){
				Left(*T) = Node;
			} else if(UnerLeft(*T)){
				Right(Left(*T)) = Node;
			} else {
				tempWahana = Left(*T);
				while(Right(tempWahana) != Nil){
					tempWahana = Right(tempWahana);
				}
				Right(tempWahana) = Node;
			}
		} else {
			if(SearchEksistensiIndeks(Left(*T), idx)){
				TambahUpgrade(idx, NewUp, &Left(*T));
			} else {
				TambahUpgrade(idx, NewUp, &Right(*T));
			}
		}
	}
}
	
	
LinkedList KemungkinanUpgrade(Tree T)
// Membuat list semua kemungkinan upgrade yang mungkin dari sebuah wahana
{
	LinkedList LL;
	Tree Tup;
	BuatLL(&LL);
	if(TreeSatuElemen(T)){
		return(LL);
	} else {
		Tup = Left(T);
		InsVLast(&LL, IDWahana(Tup));
		while(Right(Tup) != Nil){
			Tup = Right(Tup);
			InsVLast(&LL, IDWahana(Tup));
		}
		return(LL);
	}
}	

void PrintTree(Tree P, int h) 
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
	/*KAMUS*/
	int i, hc = h;
	/*ALGORITMA*/
	if(TreeKosong(P)){
		
	} else {
		printf("%d\n", IDWahana(P));
		if(!TreeKosong(Left(P))){
			for(i = 0; i < h; i++){
				printf(" ");
			}
			PrintTree(Left(P), hc+h);
		}
		if(!TreeKosong(Right(P))){
			for(i = 0; i < h; i++){
				printf(" ");
			}
			PrintTree(Right(P), hc+h);			
		}
	}
}
