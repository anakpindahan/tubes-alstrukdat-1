#include "ADT_Peta.h"

int main () {
    Peta sample;

    bacaPeta("sample.txt",&sample);

    printf("Baris: %d Kolom: %d\nPeta:\n\n", sample.NBrsEff, sample.NKolEff);

    for (int i = 0; i < sample.NBrsEff; i++) {
        for (int j = 0; j < sample.NKolEff; j++) {
            printf("%c",sample.Isi[i][j]);
        }
        printf("\n");
    }

    Peta test;
    bacaPeta("test.txt",&test);

    printf("\nBaris: %d Kolom: %d\nPeta:\n\n", test.NBrsEff, test.NKolEff);

    for (int i = 0; i < test.NBrsEff; i++) {
        for (int j = 0; j < test.NKolEff; j++) {
            printf("%c",test.Isi[i][j]);
        }
        printf("\n");
    }

    return 0;
}
