#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *filePointer;
    char ch;
    char map[5][5];
    int i,j;

    //INISIALISASI
    filePointer = fopen("testmap.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        //PEMBACAAN MAP DALAM TXT DAN DISIMPAN DALAM MATRIKS
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                ch = fgetc(filePointer);
                map[i][j] = ch;
            }
            //UNTUK SKIP NEWLINE
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);

    //PRINT MAP
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    //PROTOTYPE ADT PEMAIN
    typedef struct {int KoorX; int KoorY; char Simbol;} KoorPlay;

    KoorPlay Pemain;

    Pemain.KoorX = 1;
    Pemain.KoorY = 1;
    Pemain.Simbol = 'P';

    //PELETAKKAN DEFAULT PEMAIN DALAM MAP DI KOORD (1,1)
    map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;

    printf("\n");

    //PRINT ULANG MAP DGN SIMBOL PEMAIN
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    //PROTOTYPE KONTROL PEMAIN
    char command;

    do {
         scanf(" %c", &command);
        //SETELAH MENDAPAT INPUT, DILAKUKAN CEK APAKAH MENABRAK BATAS ATAU TIDAK, BELUM ADA IMPLEMENTASI GERBANG

        //INPUT W
        if (command == 'w') {
            if (Pemain.KoorY - 1 != 0)  {
                map[Pemain.KoorY][Pemain.KoorX] = '-';
                Pemain.KoorY--;
                map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
            }
        //INPUT A
        } else if (command == 'a') {
            if (Pemain.KoorX - 1 != 0)  {
                map[Pemain.KoorY][Pemain.KoorX] = '-';
                Pemain.KoorX--;
                map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
            }
        //INPUT S
        } else if (command == 's') {
            if (Pemain.KoorY + 1 != 4)  {
                map[Pemain.KoorY][Pemain.KoorX] = '-';
                Pemain.KoorY++;
                map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
            }
        //INPUT D
        } else if (command == 'd') {
            if (Pemain.KoorX + 1 != 4)  {
                map[Pemain.KoorY][Pemain.KoorX] = '-';
                Pemain.KoorX++;
                map[Pemain.KoorY][Pemain.KoorX] = Pemain.Simbol;
            }
        }
        //PRINT ULANG MAP DGN SIMBOL PEMAIN
        printf("\n");

        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
    //UNTUK STOP
    } while (command != 'q');

    return 0;
}
