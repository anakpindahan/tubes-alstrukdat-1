#include "ADT_waktu.h"

int main () {
    setWaktu(&WaktuMain,10,0);

    printf("Waktu main: ");
    printDalamFormatWaktu(WaktuMain);
    printf("\n");

    Waktu test;
    setWaktu(&test,3,0);

    printf("Waktu test: ");
    printDalamFormatWaktu(test);
    printf("\n");

    printf("Waktu hasil tambah antara main dan test: ");
    printDalamFormatWaktu(tambahWaktu(WaktuMain,test));
    printf("\n");

    printf("Waktu hasil tambah test dengan 3:15 : ");
    printDalamFormatWaktu(tambahWaktuManualF(test,3,15));
    printf("\n");

    tambahWaktuMainManual(23,0);
    printf("Waktu main hasil tambah dengan 23:00 : ");
    printDalamFormatWaktu(WaktuMain);
    printf("\n");

    printf("Waktu selisih antara test dan main: ");
    printDalamFormatWaktu(selisihTerhadapWaktuMain(test));
    printf("\n");

    printf("Apakah waktu main ada di main phase: ");
    printf("%s", diMainPhase(WaktuMain) == true ? "TRUE" : "FALSE");
    printf("\n");

    printf("Apakah waktu test ada di main phase: ");
    printf("%s", diMainPhase(test) == true ? "TRUE" : "FALSE");
    printf("\n");

    return 0;
}
