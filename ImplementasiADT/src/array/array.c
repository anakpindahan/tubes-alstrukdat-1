#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyBahan (Bahan * B, int maxel) {
  /* KAMUS LOKAL */
  
  /* ALGORITMA */
  if (maxel > 0) {
    BI(*B) = (info_bahan *) malloc ((maxel + 1)* sizeof(info_bahan));
    MaxEl(*B) = maxel;
    Neff(*B) = 0;
  }
}

void DealokBahan(Bahan *B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  free(BI(*B));
  MaxEl(*B) = 0;
  Neff(*B) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtBhn (Bahan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return Neff(B);
}

/* *** Selektor INDEKS *** */
IdxType GetFirstBhn (Bahan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return IdxMin;
}

IdxType GetLastBhn (Bahan B) {
  /* KAMUS LOKAL */

  /* ALGORITMA */
  return Neff(B);
}

// * Mengirimkan harga bahan pada bahan (B,X), dimana X adalah nama bahan
int GetHarga(Bahan B, IdxType X){
int i = 0;
boolean found = false;
while ( i <= Neff(B) && !found){
    if (Nama(ElmtBhn(B,i)) == X){
        found = true;
    }
    i++;
}
if(found){
    return (Harga(ElmtBhn(B,i)));
}
else{
    return 0;
}
}

// test tabel kosong
boolean IsEmptyBhn (Bahan B) {
  return (Neff(B) == 0);
}

/* *** Test tabel penuh *** */
boolean IsFullBhn (Bahan B) {
  return (Neff(B) == MaxEl(B));
}

Bahan CopyBahan (Bahan B){
/* KAMUS LOKAL */
  Bahan P;
  int i;

  /* ALGORITMA */
  MakeEmptyBahan(&P, MaxEl(B));
  for (i = 1; i <= NbElmtBhn(B); i++) {
    Nama(ElmtBhn(P, i)) = Nama(ElmtBhn(B, i));
    Harga(ElmtBhn(P, i)) = Harga(ElmtBhn(B, i));
    Jumlah(ElmtBhn(P, i)) = Jumlah(ElmtBhn(B, i));
  }
  Neff(P) = Neff(B);
}
}

void TulisIsiBahan (Bahan B)
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50 */
{
	//Kamus
	IdxType i;

	//Algoritma
	if (IsEmptyBhn(T) == true)
	{
		printf ("Tabel kosong\n");
	}
	else
	{
		for (i = GetFirstBhn(T); i <= GetLastBhn(T); i++)
		{
			printf("[%d] %-15s %-15d %-15d\n", i, Nama(ElmtBhn(B,i)), Harga(ElmtBhn(B,i)), Jumlah(ElmtBhn(B,i));
		}
	}
}