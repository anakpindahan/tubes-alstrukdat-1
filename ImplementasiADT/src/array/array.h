/* ADT Array */

#ifndef ARRAY_H
#define ARRAY_H

#include "../Boolean/boolean.h"
#include "../Point/point.h"

/*  Kamus Umum */
#define IdxMin 1
/* Indeks minimum array */

/* Definisi elemen dan koleksi objek */
typedef int IdxType;  /* type indeks */
typedef int ElType;   /* type elemen tabel */   // Jujur kurang ngerti

typedef struct {
  char Nama;              /* Tipe Bahan Bangunan */
  int Harga;                /* Harga Bahan Bangunan */
  int Jumlah;               /* Jumlah per bahan */
} info_bahan;

typedef struct {
  info_bahan *BI; /* memori tempat penyimpan elemen (container) */
  int Neff;   /* >=0, banyaknya elemen efektif */
  int MaxEl;  /* ukuran elemen */
} Bahan;

/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Jika B adalah Bangunan, cara deklarasi dan akses: */
/* Deklarasi : B : Bahan */
/* Maka cara akses:
   B.Neff  untuk mengetahui banyaknya elemen
   B.BI    untuk mengakses seluruh nilai elemen tabel
   B.BI[i] untuk mengakses elemen ke-i 

/* Definisi :
   Tabel kosong: B.Neff = 0
   Definisi elemen pertama : B.BI[i] dengan i=1
   Definisi elemen terakhir yang terdefinisi: B.BI[i] dengan i=B.Neff */

/* ********** SELEKTOR ********** */
/* B adalah Bahan, A adalah Aksi     */
/* e adalah info_bahan dan info_aksi */
#define Neff(B)       (B).Neff
#define BI(B)         (B).BI
#define ElmtBhn(B,i)  (B).BI[(i)]
#define MaxEl(B)      (B).MaxEl

/* e adalah info_bahan */
#define Nama(e)       (e).Nama
#define Harga(e)     (e).Harga
#define Jumlah(e)     (e).Jumlah

// $ ********** KONSTRUKTOR **********

// $ Konstruktor : create tabel kosong
// * I.S. B sembarang, maxel > 0
// * F.S. Terbentuk tabel B kosong dengan kapasitas maxel + 1
void MakeEmptyBahan (Bahan * B, int maxel);

// * I.S. B terdefinisi;
// * F.S. BI(B) dikembalikan ke system, MaxEl(B)=0; Neff(B)=0
void DealokBahan(Bahan *B);

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */

/* Mengirimkan banyaknya elemen efektif tabel */
int NbElmtBhn (Bahan B);

/* *** Selektor INDEKS *** */

/* Prekondisi : Tabel B tidak kosong */
/* Mengirimkan indeks elemen B pertama */
IdxType GetFirstBhn (Bahan B);

/* Prekondisi : Tabel B tidak kosong */
/* Mengirimkan indeks elemen B terakhir */
IdxType GetLastBhn (Bahan B);

// * Mengirimkan harga bahan pada bahan (B,X)
int GetHarga(Bahan B, IdxType X);

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */

/* Mengirimkan true jika tabel B kosong, mengirimkan false jika tidak */
boolean IsEmptyBhn(Bahan B);

/* *** Test tabel penuh *** */

/* Mengirimkan true jika tabel B penuh, mengirimkan false jika tidak */
boolean IsFullBhn(Bahan B);

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */

/* I.S. B sembarang */
/* F.S. Tabel B terdefinisi */
/* Prekondisi : Banyaknya elemen B itu valid */
/* Proses : membaca banyaknya elemen B dan mengisi semua nilainya dengan Mesin Kata */
void BacaBahan(Bahan * B);

/*********************** Tentara Attack ****************************/

/* Mengecek apakah bahan ke-X memiliki harga yang >= N */
/* Jika benar maka true dan sebaliknya */
boolean CekHarga(Bahan B, IdxType X, int N);

/* Me-copy data-data Bahan */
Bahan CopyBahan(Bahan B);

#endif
