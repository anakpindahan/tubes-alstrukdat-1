/*ADT TREE*/

#ifndef TREE_H
#define TREE_H

#include "boolean.h"
#include "ADT_linkedlist.h"

#define Nil NULL

typedef int TupelUp[6];
// Memiliki 6 elemen: ID Wahana saat ini, Resource yang dibutuhkan untuk membangun/upgrade ini (Uang, 
// BahanBangunan1, BahanBangunan2, BahanBangunan3), dan ID Wahana yang diupgrade (0 jika ini wahana dasar)


typedef struct tNode *addressNode;

typedef struct tNode{
	TupelUp CWahana;
	addressNode Left;
	addressNode Right;
} Node;

typedef addressNode Tree;

// Tree bersifat generic tree yang diimplementasikan dengan binary tree
// CWahana bersifat tupel isi enam elemen seperti yang sudah dijelaskan
// Jika CWahana hanya dapat diupgrade menjadi wahana W1, maka W1 akan menjadi leftchild dari CWahana
// Jika CWahana punya dua wahana hasil upgrade, salah satunya akan menjadi leftchild dari CWahana
// Sementara, wahan yang lain akan menjadi right child dari leftchild CWahana tadi
// Dengan kata lain, leftchild menunjukkan salah satu hasil upgrade wahana dan rightchild menunjukkan
// wahana yang dapat diupgrade dari wahana yang sama

/***********SELEKTOR***********/
#define InfoWahana(P) (P)->CWahana
#define Left(P) (P)->Left
#define Right(P) (P)->Right
#define IDWahana(P) InfoWahana(P)[0]

/*********PREDIKAT************/
boolean TreeKosong(Tree T);

boolean TreeSatuElemen(Tree T);

boolean UnerLeft(Tree T);

boolean UnerRight(Tree T);

/********KONSTRUKTOR**********/
void BuatTreeP(TupelUp wahana, Tree Anak, Tree Saudara, Tree* T);

Tree BuatTreeF(TupelUp wahana, Tree Anak, Tree Saudara);

/**********MANAJEMEN MEMORI***********/
addressNode AlokasiAddress(TupelUp wahana);

void DealokasiAddress(addressNode P);

/************TRAVERSAL************/
boolean SearchEksistensiIndeks(Tree T, int idx);
// Mengecek apakah ada address node di T yang memuat indeks idx

addressNode SearchWahanaDenganIndeks(Tree T, int idx);
// Prasyarat: setiap address node di T memuat indeks yang berbeda dan pasti ada yang nilai indeksnya idx

addressNode Predecessor(addressNode Wahana, Tree T);
// Mencari wahana yang apabila diupgrade akan menghasilkan Wahana

void TambahUpgrade(int idx, TupelUp NewUp, Tree T);

LinkedList KemungkinanUpgrade(Tree T);
// Membuat list semua kemungkinan upgrade yang mungkin dari sebuah wahana



#endif

