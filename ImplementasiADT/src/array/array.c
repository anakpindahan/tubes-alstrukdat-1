#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../Kata/ADT_kata.c"
#include "array.h"


List_Info_Bahan Daftar_Harga_Bahan;

void makeEmpty(List_Info_Bahan B) {
    B.Neff = 0;
}

void BacaBahan_dari_File(char string[]) {
    int i; char buff[255]; char* token;
    FILE* filePointer = fopen(string, "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
    	i = 0;
    	while(fgets(buff, 255, filePointer) != NULL){
			token = strtok(buff, ";");
    		Daftar_Harga_Bahan.BI[i].nama_bahan = createKata(token);

            token = strtok(NULL, ";");
    		Daftar_Harga_Bahan.BI[i].Harga = atoi(token);
    		i++;
        }
    Daftar_Harga_Bahan.Neff = i;
    }
    fclose(filePointer);
}
void PrintMenuBuy (List_Info_Bahan B) {
    int i = 0;
    printf("Menu Pembelian:\n");
    for (i; i < B.Neff; i++) {
        printf("\t%d. ", i + 1);
        printKata(B.BI[i].nama_bahan);
        printf(": %d LMD\n", B.BI[i].Harga);
    }
    printf("\nTuliskan angka dari benda yang ingin dibeli\n");
}
