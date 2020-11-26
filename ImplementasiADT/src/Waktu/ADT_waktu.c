/*Implementasi ADT Waktu*/

#include "../Boolean/boolean.h"
#include "ADT_waktu.h"
#include <stdio.h>

Waktu WaktuMain;

/**************SELEKTOR***********/
#define Jam(W) (W).Jam
#define Menit(W) (W).Menit

/**************KONSTRUKTOR************/
void setWaktu(Waktu* waktu, int jam, int menit)
/*I.S. */
/*F.S. */
{
	Jam(*waktu) = jam;
	Menit(*waktu) = menit;
}

/**************KELOMPOK BACA/TULIS*********/
void printDalamFormatWaktu(Waktu waktu)
/*I.S.*/
/*F.S.*/
{
    if (Jam(waktu) > 9) {
        printf("%d", Jam(waktu));
    } else {
        printf("0%d", Jam(waktu));
    }
    if (Menit(waktu) > 9) {
        printf(":%d\n", Menit(waktu));
    } else {
        printf(":0%d\n", Menit(waktu));
    }
}

/**************KELOMPOK OPERASI ARITMETIKA *****************/
Waktu tambahWaktu(Waktu waktu1, Waktu waktu2){
	Waktu waktu3;
	int menit, jam, lebih;
	menit = (Menit(waktu1) + Menit(waktu2)) % 60;
	lebih = (Menit(waktu1) + Menit(waktu2)) / 60;
	jam = Jam(waktu1) + Jam(waktu2) + lebih;
	setWaktu(&waktu3, jam, menit);
	return waktu3;
}

void tambahWaktuManualP(Waktu waktu, int jam, int menit){
	int lebih;
	Menit(waktu) += menit; 
	lebih = Menit(waktu) / 60;
	Menit(waktu) %= 60;
	Jam(waktu) += (lebih + jam);
}

Waktu tambahWaktuManualF(Waktu waktu, int jam, int menit){
	int lebih;
	Waktu waktuHasil;
	int menitHasil;
	int jamHasil;
	menitHasil = menit + Menit(waktu); 
	lebih = menitHasil / 60;
	menitHasil = menitHasil % 60;
	jamHasil = lebih + jam + Jam(waktu);
	setWaktu(&waktuHasil, jamHasil, menitHasil);
	return(waktuHasil);
}

void tambahWaktuMainADTWaktu(Waktu waktu) {
    Menit(WaktuMain) += Menit(waktu);
    if (Menit(WaktuMain) > 59) {
        Menit(WaktuMain) = Menit(WaktuMain) % 60;
        Jam(WaktuMain)++;
    }
    Jam(WaktuMain) = (Jam(WaktuMain) + Jam(waktu)) % 24;
}

void tambahWaktuMainManual(int jam, int menit) {
    Menit(WaktuMain) += menit;
    if (Menit(WaktuMain) > 59) {
        Menit(WaktuMain) = Menit(WaktuMain) % 60;
        Jam(WaktuMain)++;
    }
    Jam(WaktuMain) = (Jam(WaktuMain) + jam) % 24;
}

Waktu selisihTerhadapWaktuMain(Waktu waktu) {
    Waktu hasilSelisih;

    Jam(hasilSelisih) = 0;
    Menit(hasilSelisih) = Menit(waktu) - Menit(WaktuMain);
    if (Menit(hasilSelisih) < 0) {
        Menit(hasilSelisih) += 60;
        Jam(hasilSelisih)--;
    }
    Jam(hasilSelisih) +=  (Jam(waktu) - Jam(WaktuMain));
    if (Jam(hasilSelisih) < 0) {
        Jam(hasilSelisih) += 24;
    }
    return hasilSelisih;
}
boolean diMainPhase(Waktu waktu){
	return((Jam(waktu) >= 9) && (Jam(waktu) < 21));
}
