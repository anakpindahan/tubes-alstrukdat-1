#ifndef GRAF_PETA_H
#define GRAF_PETA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char Isi[50][50]; // --> Ukuran default
	int NKolEff;
	int NBrsEff;
} Peta;

typedef struct {
    int Map_X_Max;
    int Map_X_Min;
    int Map_Y_Max;
    int Map_Y_Min;
} IDPetaUmum; // --> Sebagai variable global untuk menyimpan data berupa batas koordinat yang dapat dipijak pemain

extern IDPetaUmum Identitas_Peta;

void bacaPeta(char* file_name, Peta* kontainer_peta);
/*
    Membaca sebuah file .txt
    Proses:
        1. Looping pembacaan char satu per satu pada file
        2. Jika bertemu '\n'
            membaca line baru
        3. Jika bertemu '\0'
            selesai membaca
        4. Mengisi NBrsEff = jumlah line terbaca dalam file
        5. Mengisi NKolEff = jumlah char terbaca dalam satu baris

*/

#endif
