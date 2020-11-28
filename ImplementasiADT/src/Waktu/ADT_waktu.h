/*ADT WAKTU*/

#ifndef WAKTU_H
#define WAKTU_H

#include "../Boolean/boolean.h"

typedef struct {
    int Jam;
    int Menit;
} Waktu;

extern Waktu WaktuMain;

/**************SELEKTOR***********/
#define Jam(W) (W).Jam
#define Menit(W) (W).Menit

/**************KONSTRUKTOR************/
void setWaktu(Waktu* waktu, int jam, int menit);
/*
    Setting suatu variabel Waktu sehingga memiliki Jam = jam dan Menit = menit
*/

/**************KELOMPOK BACA/TULIS*********/
void printDalamFormatWaktu(Waktu waktu);
/*
    Print variabel Waktu dalam format XX:XX
*/

/**************KELOMPOK OPERASI ARITMETIKA *****************/
Waktu tambahWaktu(Waktu waktu1, Waktu waktu2);
/*
    Mengembalikan hasil jumlah antara waktu1 dan waktu2
*/

void tambahWaktuManualP(Waktu waktu, int jam, int menit);
/*
    Menambahkan Jam dan Menit dari suatu variabel Waktu dengan input jam dan menit
*/

Waktu tambahWaktuManualF(Waktu waktu, int jam, int menit);
/*
    Mengembalikan hasil penjumlah suatu variabel bertipe Waktu dengan input jam dan menit
*/

void tambahWaktuMainADTWaktu(Waktu waktu);
/*
    Menambahkan Jam dan Menit dari WaktuMain (variabel global) dengan suatu variabel bertipe Waktu
*/

void tambahWaktuMainManual(int jam, int menit);
/*
    Menambahkan Jam dan Menit dari WaktuMain (variabel global) dengan input jam dan menit
*/

Waktu selisihTerhadapWaktuMain(Waktu waktu);
/*
    Mengembalikan selisih antara suatu variabel bertipa Waktu terhadap WaktuMain (variabel global)
*/

boolean diMainPhase(Waktu waktu);
/*
    Mengembalikan true jika waktu ada dalam main phase, yaitu antara jam 09.00 sampai 21.00, false jika tidak
*/

#endif
