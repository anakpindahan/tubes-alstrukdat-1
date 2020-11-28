#include "ADT_Peta.h"
#include <stdio.h>
#include <stdlib.h>

void bacaPeta(char* file_name, Peta* kontainer_peta) {
    char ch; int i,j;
    FILE* filePointer = fopen(file_name, "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
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
