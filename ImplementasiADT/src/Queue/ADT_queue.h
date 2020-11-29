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
/* Mengirim true jika Q kosong: lihat definisi di atas */

boolean QueuePenuh(PrioQueue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */

int BanyakAnggotaQueue(PrioQueue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

void BuatQueue(PrioQueue *Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxQEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

void DealokasiQueue(PrioQueue *Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxQEl(Q) diset 0 */

void EnqueuePengunjung(PrioQueue *Q, Pengunjung X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */

void DequeuePengunjung(PrioQueue *Q, Pengunjung *X);
/* I.S. Q tidak mungkin kosong */
/* F.S. X = QNilai elemen HEAD pd I.S., HEAD "maju"*/

void PrintPrioQueue (PrioQueue Q);
/* I.S. Q tidak kosong */
/* F.S. menuliskan seluruh elemen Queue ke layar */

void kesabaran(PrioQueue *Q);
/* I.S. Q terdefinisi
   F.S. Kesabaran seluruh pelanggan berkurang 1.
*/

#endif