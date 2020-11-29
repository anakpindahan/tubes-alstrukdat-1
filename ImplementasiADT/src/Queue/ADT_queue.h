#ifndef QUEUE_H
#define QUEUE_H

#define NilQ -1

#include "../Boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* Definisi ADT Priority Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut tidak mengecil berdasarkan elemen prio */

typedef struct {
	int prio; // Prioritas dari 1 sampai 100, semakin rendah semakin dilayani
	int kesabaran; // Tingkat kesabaran pengunjung dari 1 sampai 10, semakin rendah semakin marah
	int nomor; // Nomor pengunjung
	int wahanaImpian[3]; // Semua indeks wahana yang ingin dinaiki oleh pengunjung, jika kurang dari tiga, elemennya ditulis dengan 0
} Pengunjung;

typedef int addressQ;
typedef struct {
	Pengunjung *P;	// Tabel elemen
	addressQ Head; 	// Alamat penghapusan
	addressQ Tail;	// Alamat penambahan
	int MaxEl;		// Banyak elemen maksimal 
} PrioQueue;

// PrioQueue

#define Prio(e) (e).prio
#define Sabar(e) (e).kesabaran
#define Nomor(e) (e).nomor
#define NaikWahana(e) (e).wahanaImpian
#define NaikWahanaKei(e, i) ((e).wahanaImpian)[(i)]
#define Head(Q) (Q).Head
#define Tail(Q) (Q).Tail
#define InfoHead(Q) (Q).P[(Q).Head]
#define InfoTail(Q) (Q).P[(Q).Tail]
#define MaxEl(Q)    (Q).MaxEl
#define Elmt(Q,i)   (Q).P[(i)]

boolean QueueKosong(PrioQueue Q);

boolean QueuePenuh(PrioQueue Q);

int BanyakAnggotaQueue(PrioQueue Q);

void BuatQueue(PrioQueue *Q, int Max);

void DealokasiQueue(PrioQueue *Q);

void EnqueuePengunjung(PrioQueue *Q, Pengunjung X);

void DequeuePengunjung(PrioQueue *Q, Pengunjung *X);

void PrintPrioQueue (PrioQueue Q);

#endif

