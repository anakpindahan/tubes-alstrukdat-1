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
/*I.S. */
/*F.S. */


/**************KELOMPOK BACA/TULIS*********/
void printDalamFormatWaktu(Waktu waktu);
/*I.S.*/
/*F.S.*/

/**************KELOMPOK OPERASI ARITMETIKA *****************/
Waktu tambahWaktu(Waktu waktu1, Waktu waktu2);

void tambahWaktuManualP(Waktu waktu, int jam, int menit);

Waktu tambahWaktuManualF(Waktu waktu, int jam, int menit);

void tambahWaktuMainADTWaktu(Waktu waktu);

void tambahWaktuMainManual(int jam, int menit);

Waktu selisihTerhadapWaktuMain(Waktu waktu);

boolean diMainPhase(Waktu waktu);

#endif
