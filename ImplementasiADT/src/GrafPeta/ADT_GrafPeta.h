#ifndef _ADT_GRAFPETA_H
#define _ADT_GRAFPETA_H

#include "../Peta/ADT_Peta.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct tGrafNode * adrGrafNode;
typedef struct tGrafSuccNode * adrGrafSuccNode;

typedef struct tGrafNode {
	Peta* ID;
	adrGrafSuccNode Trail;
	adrGrafNode Next;
} GrafNode;

typedef struct tGrafSuccNode {
	adrGrafNode Succ;
	char arah;
	adrGrafSuccNode Next;
} GrafSuccNode;

typedef struct {
	adrGrafNode First;
} Graph;

extern Graph GrafPeta;

adrGrafNode GrafAlokNode (Peta* peta);
/*
    Melakukan alokasi memori untuk tipe data adrGrafNode
    Jika tidak NULL
        ID akan diisi peta
        Trail akan diisi NULL
        Next akan diisi NULL
*/

void GrafDealokNode (adrGrafNode Pn);
/*
    Mengembalikan memori dari variabel bertipe adrGrafNode ke sistem
*/

adrGrafSuccNode GrafAlokSuccNode (adrGrafNode Pn, char orientasi);
/*
    Melakukan alokasi memori untuk tipe data adrGrafSuccNode
    Jika tidak NULL
        Succ akan diisi Pn
        arah akan diisi orientasi
        Next akan diisi NULL
*/

void GrafDealokSuccNode (adrGrafSuccNode Pt);
/*
    Mengembalikan memori dari variabel bertipe adrGrafSuccNode ke sistem
*/

void GrafInsertNode (Graph G, Peta* peta);
/*
    Menambahkan sebuah Node ke dalam G
    Proses:
        1. Alokasi memori (Fungsi GrafAlokNode)
        2. Jika tidak NULL
            Next dari Node terakhir dalam G adalah hasil alokasi dari langkah 1
*/

void GrafInsertEdge (Graph G, Peta* prec, Peta* succ, char orientasi);
/*
    Menambahkan edge antara dua Node dalam graph
    Prekondisi: sudah ada Node dengan ID prec dan ID succ
    Proses:
        1. Alokasi memori (Fungsi GrafAlokSuccNode)
        2. Jika tidak NULL
            Jika Trail Node dengan ID prec kosong
                Trail dari Node ID prec diisi ke hasil alokasi langkah 1
            Jika Trail Node dengan ID prec tidak kosong
                Next dari Trail terakhir pada Node ID prec adalah hasil alokasi langkah 1
*/

Peta* GrafSearchTarget(Graph G, Peta* peta_asal, char orientasi);
/*
    Kondisi: hasil pasti ditemukan
    Proses:
        1. Mencari Node pada graph dengan ID peta_asal
        2. Mencari Trail yang memiliki arah = orientasi
        3. Mengembalikan ID dari Succ (adrGrafNode) dari Trail pada Langkah 2
*/

#endif
