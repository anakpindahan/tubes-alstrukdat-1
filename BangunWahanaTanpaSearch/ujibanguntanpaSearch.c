#include <stdio.h>
#include <stdlib.h>
//#include "boolean.h"

//PROTOTYPE ADT WAHANA UNTUK DITAMPILKAN PADA MAP
typedef struct {char* nama; int mapKuad; int KoorX; int KoorY; char Simbol;} KoorWahana;

typedef struct {KoorWahana T[10]; int Isi;} ListWahana;

//PROTOTYPE ADT PEMAIN DGN SEGMENTASI MAP
typedef struct {char (*map)[5]; int mapKuad; int KoorX; int KoorY; char Simbol; char PetakPijak;} KoorPlay;

/*
void returnSimbol(KoorPlay Pemain, ListWahana* list) {
    int i = 0;
    boolean temu = false;

    while (list->T[i].nama != NULL && !temu) {
        if (list->T[i].KoorX == Pemain.KoorX && list->T[i].KoorY == Pemain.KoorY && list->T[i].mapKuad == Pemain.mapKuad) {
            temu = true;
            Pemain.map[Pemain.KoorY][Pemain.KoorX] = list->T[i].Simbol;
        }
        i++;
    }

    if (!temu) {
        Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
    }
}
*/

int main() {
    FILE *filePointer;
    char ch;
    char mapkuad1[5][5];
    char mapkuad2[5][5];
    char mapkuad3[5][5];
    char mapkuad4[5][5];
    int i,j;

    //INISIALISASI MEMBACA TIAP SEGMEN MAP DALAM FILE TEXT DAN DISIMPAN KE DALAM MATRIKS YG BERSESUAIAN
    filePointer = fopen("kuadran1.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                ch = fgetc(filePointer);
                mapkuad1[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);

    filePointer = fopen("kuadran2.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                ch = fgetc(filePointer);
                mapkuad2[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);

    filePointer = fopen("kuadran3.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                ch = fgetc(filePointer);
                mapkuad3[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);

    filePointer = fopen("kuadran4.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                ch = fgetc(filePointer);
                mapkuad4[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);


    //MEMBUATAN VAR TIPE DATA LISTWAHANA
    ListWahana list;
    ListWahana* ptrlist = &list;

    list.Isi = 0;
    /*
        //MEMBUATAN VAR TIPE DATA KOORWAHANA
        KoorWahana sample;

        sample.nama = "Sample";
        sample.mapKuad = 2;
        sample.KoorX = 2;
        sample.KoorY = 2;
        sample.Simbol = 'S';

        KoorWahana ujian;

        ujian.nama = "Ujian";
        ujian.mapKuad = 1;
        ujian.KoorX = 1;
        ujian.KoorY = 1;
        ujian.Simbol = 'U';

    list.T[0] = sample;
    list.T[1] = ujian;
    */

    //MEMBUATAN VAR TIPE DATA KOORPLAY
    KoorPlay Pemain;

    Pemain.mapKuad = 2;
    Pemain.map = &mapkuad2;
    Pemain.KoorX = 1;
    Pemain.KoorY = 1;
    Pemain.Simbol = 'P';
    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];

    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;

    //PRINT AWAL MAP DGN PEMAIN DI KUADRAN 2
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c", Pemain.map[i][j]);
        }
        printf("\n");
    }

    char command;
    char prediksi;

    do {
         scanf(" %c", &command);
        //INPUT W
        if (command == 'w') {
            //CEK ISI PETAK YG AKAN DITUJU
            prediksi = Pemain.map[Pemain.KoorY - 1][Pemain.KoorX];
            if (prediksi != '*') {
                //JIKA BUKAN TEMBOK
                if (prediksi != '^') {
                    //JIKA BUKAN GERBANG
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorY--;
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == '^') {
                    //JIKA GERBANG UTARA (HANYA ADA PADA KUADRAN 3 & 4)
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorY = 4 - 1; //--> PERLU REVISI MENJADI NILAI PETAK MAKS - 1
                    if (Pemain.mapKuad == 3) {
                        //JIKA DI KUADRAN 3
                        Pemain.map = &mapkuad2;//PINDAH MAP
                        Pemain.mapKuad = 2;//GANTI ID SEGMEN
                    } else if (Pemain.mapKuad == 4) {
                        //JIKA DI KUADRAN 4
                        Pemain.map = &mapkuad1;
                        Pemain.mapKuad = 1;
                    }
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 'a') {
            prediksi = Pemain.map[Pemain.KoorY][Pemain.KoorX - 1];
            if (prediksi != '*') {
                if (prediksi != '<') {
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorX--;
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == '<') {
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorX = 4 - 1;
                    if (Pemain.mapKuad == 1) {
                        Pemain.map = &mapkuad2;
                        Pemain.mapKuad = 2;
                    } else if (Pemain.mapKuad == 4) {
                        Pemain.map = &mapkuad3;
                        Pemain.mapKuad = 3;
                    }
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 's') {
            prediksi = Pemain.map[Pemain.KoorY + 1][Pemain.KoorX];
            if (prediksi != '*') {
                if (prediksi != 'V') {
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorY++;
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == 'V') {
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorY = 0 + 1;
                    if (Pemain.mapKuad == 1) {
                        Pemain.map = &mapkuad4;
                        Pemain.mapKuad = 4;
                    } else if (Pemain.mapKuad == 2) {
                        Pemain.map = &mapkuad3;
                        Pemain.mapKuad = 3;
                    }
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 'd') {
            prediksi = Pemain.map[Pemain.KoorY][Pemain.KoorX + 1];
            if (prediksi != '*') {
                if (prediksi != '>') {
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorX++;
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == '>') {
                    //Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    //returnSimbol(Pemain, ptrlist);
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.PetakPijak;
                    Pemain.KoorX = 0 + 1;
                    if (Pemain.mapKuad == 3) {
                        Pemain.map = &mapkuad4;
                        Pemain.mapKuad = 4;
                    } else if (Pemain.mapKuad == 2) {
                        Pemain.map = &mapkuad1;
                        Pemain.mapKuad = 1;
                    }
                    Pemain.PetakPijak = Pemain.map[Pemain.KoorY][Pemain.KoorX];
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 'b') {
            KoorWahana sample;

            scanf("%s", &sample.nama);
            sample.mapKuad = Pemain.mapKuad;
            sample.KoorX = Pemain.KoorX;
            sample.KoorY = Pemain.KoorY;
            scanf(" %c", &sample.Simbol);

            Pemain.PetakPijak = sample.Simbol;

            list.T[list.Isi] = sample;
            list.Isi++;
            //printf("%s %c", sample.nama, sample.Simbol);
        }

        //PRINT ULANG MAP DGN PEMAIN
        system("cls");

        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                printf("%c", Pemain.map[i][j]);
            }
            printf("\n");
        }
    } while (command != 'q');

}


