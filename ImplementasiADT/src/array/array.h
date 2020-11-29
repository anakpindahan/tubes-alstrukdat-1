/* ADT List untuk Bahan Bangunnan */
/* Dengan versi eksplisit rata kiri */

#ifndef ARRAY_H
#define ARRAY_H

#include "../Boolean/boolean.h"
#include "../Kata/ADT_kata.h"

typedef struct {
  Kata nama_bahan;              /* Tipe Bahan Bangunan */
  int Harga;                    /* Harga Bahan Banguna */
} info_bahan;

typedef struct {
  info_bahan BI[10];            /* Kontainer untuk Bahan Bangunan, dengan ukuran default 10 */
  int Neff;                     /* >=0, banyaknya elemen efektif */
} List_Info_Bahan;

extern List_Info_Bahan Daftar_Harga_Bahan; // --> Variabel global

void makeEmpty(List_Info_Bahan B);
/*

*/

/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaBahan_dari_File(char string[]);
/* I.S. Daftar_Harga_Barang kosong */
/* F.S. Daftar_Harga_Barang terdefinisi terdefinisi */
/* Proses: membaca isi file kemudian disimpan dalam Daftar_Harga_Barang, Neff menyesuaikan dengan jumlah bahan bangunan terbaca*/

void TulisIsiBahan (List_Info_Bahan B);
/* Proses : Menuliskan isi tabel dengan traversal menurut Neff*/
/* Contoh: Jika isi Tabel: [ [X, 20], [Y, 50] ]
   Maka tercetak di layar:
    bla bla ...
        1. X : 20
        2. Y : 50
        ...
*/

#endif
