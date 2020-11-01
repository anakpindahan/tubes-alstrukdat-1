#include <stdio.h>
#include <stdlib.h>

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

    //PROTOTYPE ADT PEMAIN DGN SEGMENTASI MAP
    typedef struct {char (*map)[5]; int mapKuad; int KoorX; int KoorY; char Simbol;} KoorPlay;

    KoorPlay Pemain;

    Pemain.mapKuad = 2;
    Pemain.map = &mapkuad2;
    Pemain.KoorX = 1;
    Pemain.KoorY = 1;
    Pemain.Simbol = 'P';

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
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorY--;
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == '^') {
                    //JIKA GERBANG UTARA (HANYA ADA PADA KUADRAN 3 & 4)
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
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
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 'a') {
            prediksi = Pemain.map[Pemain.KoorY][Pemain.KoorX - 1];
            if (prediksi != '*') {
                if (prediksi != '<') {
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorX--;
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == '<') {
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorX = 4 - 1;
                    if (Pemain.mapKuad == 1) {
                        Pemain.map = &mapkuad2;
                        Pemain.mapKuad = 2;
                    } else if (Pemain.mapKuad == 4) {
                        Pemain.map = &mapkuad3;
                        Pemain.mapKuad = 3;
                    }
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 's') {
            prediksi = Pemain.map[Pemain.KoorY + 1][Pemain.KoorX];
            if (prediksi != '*') {
                if (prediksi != 'V') {
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorY++;
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == 'V') {
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorY = 0 + 1;
                    if (Pemain.mapKuad == 1) {
                        Pemain.map = &mapkuad4;
                        Pemain.mapKuad = 4;
                    } else if (Pemain.mapKuad == 2) {
                        Pemain.map = &mapkuad3;
                        Pemain.mapKuad = 3;
                    }
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        } else if (command == 'd') {
            prediksi = Pemain.map[Pemain.KoorY][Pemain.KoorX + 1];
            if (prediksi != '*') {
                if (prediksi != '>') {
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorX++;
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                } else if (prediksi == '>') {
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = '-';
                    Pemain.KoorX = 0 + 1;
                    if (Pemain.mapKuad == 3) {
                        Pemain.map = &mapkuad4;
                        Pemain.mapKuad = 4;
                    } else if (Pemain.mapKuad == 2) {
                        Pemain.map = &mapkuad1;
                        Pemain.mapKuad = 1;
                    }
                    Pemain.map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
                }
            }
        }

        //PRINT ULANG MAP DGN PEMAIN
        printf("\n");

        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                printf("%c", Pemain.map[i][j]);
            }
            printf("\n");
        }
    } while (command != 'q');

}
