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

    return 0;
}
