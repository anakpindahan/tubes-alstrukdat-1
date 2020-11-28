/*#define Map_X_Max 9
#define Map_X_Min 1
#define Map_Y_Max 9
#define Map_Y_Min 1
#define Ukuran_Peta 11
*/
#include "ADT_Peta.h"
#include <stdio.h>
#include <stdlib.h>

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

void bacaPeta(char* file_name, Peta* kontainer_peta) {
    char ch; int i,j;
    FILE* filePointer = fopen(file_name, "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        /*
        i = 0;
        for (i; i < Ukuran_Peta; i++) {
            j = 0;
            for (j; j < Ukuran_Peta; j++) {
                ch = fgetc(filePointer);
                kontainer_peta->Isi[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }*/
        i = 0; j = 0;
        do {
            ch = fgetc(filePointer);
            if (ch != '\n' && ch != EOF) {
                kontainer_peta->Isi[i][j] = ch;
                j++;
            } else if (ch == '\n') {
                i++; j = 0;
            }
        } while (ch != EOF);
        kontainer_peta->NBrsEff = i + 1;
        kontainer_peta->NKolEff = j;
    }

    fclose(filePointer);
}
