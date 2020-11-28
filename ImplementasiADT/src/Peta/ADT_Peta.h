#ifndef GRAF_PETA_H
#define GRAF_PETA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char Isi[50][50];
	int NKolEff;
	int NBrsEff;
} Peta;

typedef struct {
    int Map_X_Max;
    int Map_X_Min;
    int Map_Y_Max;
    int Map_Y_Min;
} IDPetaUmum;

extern IDPetaUmum Identitas_Peta;

/*
void bacaPeta(char* file_name, Peta* kontainer_peta) {
    char ch; int i,j;
    FILE* filePointer = fopen(file_name, "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        i = 0;
        for (i; i < Ukuran_Peta; i++) {
            j = 0;
            for (j; j < Ukuran_Peta; j++) {
                ch = fgetc(filePointer);
                kontainer_peta->Isi[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);
}
*/

void bacaPeta(char* file_name, Peta* kontainer_peta);

#endif
