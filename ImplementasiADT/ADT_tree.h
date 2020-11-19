/*ADT TREE*/

#ifndef TREE_H
#define TREE_H

#include "boolean.h"

#define Nil NULL

typedef int TupelUp[6];
// Memiliki 6 elemen: ID Wahana saat ini, Resource yang dibutuhkan untuk membangun/upgrade ini (Uang, 
// BahanBangunan1, BahanBangunan2, BahanBangunan3), dan ID Wahana yang diupgrade (0 jika ini wahana dasar)


typedef struct tNode *address;

typedef struct tNode{
	TupelUp CWahana;
	address FirstUpWahana;
	address WahanaSetara;
} Node;

typedef struct{
	address WahanaDasar;
} Tree;

// Tree bersifat generic tree yang diimplementasikan dengan binary tree
// CWahana bersifat tupel isi enam elemen seperti yang sudah dijelaskan
// FirstUpWahana adalah salah satu wahana hasil upgrade dari wahana ini
// WahanaSetara adalah salah satu wahana hasil upgrade wahana W1 dengan salah satu hasil upgrade W1 yang
// lain adalah CWahana

/***********SELEKTOR***********/
#define InfoWahana(P) (P)->CWahana
#define FUW(P) (P)->FirstUpWahana
#define WS(P) (P)->WahanaSetara
#define WD(T) (T).WahanaDasar
#define IDWahana(P) InfoWahana(P)[0]

/*********PREDIKAT************/
boolean TreeKosong(Tree T);

boolean TreeSatuElemen(Tree T);

boolean MaxUpgrade(address Wahana);

boolean SatuUpgrade(address Wahana);

/********KONSTRUKTOR**********/
void BuatTree(TupelUp wahana, Tree Anak, Tree Saudara, Tree* T);

/**********MANAJEMEN MEMORI***********/
address AlokasiAddress(TupelUp wahana);

void DealokasiAddress(address P);

/************TRAVERSAL************/
address SearchWahanaDenganIndeks(int idx, address P);

address Predecessor(address Wahana, Tree T);

void TambahUpgrade(address Wahana, address newUpgrade, Tree T);

#endif

