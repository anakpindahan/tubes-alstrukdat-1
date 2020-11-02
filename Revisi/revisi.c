#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

typedef struct {
	char Isi[5][5];
} Peta;

typedef struct {
    int X;
    int Y;
} Poin;

typedef struct {
    Peta* KuadranPeta;
    Poin PosisiPemain;
    char SimbolPemain;
    char SimbolPetak;
} Pemain;

Pemain DataPemain;

typedef struct {
    int Uang;
    int BahanBangunan1;
    int BahanBangunan2;
    int BahanBangunan3;
} Inventory;

Inventory Inventaris;

typedef struct {
    Peta* AsalKuadranPeta;
    char InputArah;
    Peta* TargetKuadranPeta;
} Garis;

typedef struct {
    Garis Edge[8];
} GrafPeta;

GrafPeta GrafUntukPeta;

typedef struct {
    char W;
    char A;
    char S;
    char D;
} PetakSekitar;

PetakSekitar SekitaranPemain;

void update() {
    SekitaranPemain.W = DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y - 1][DataPemain.PosisiPemain.X];
    SekitaranPemain.A = DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X - 1];
    SekitaranPemain.S = DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y + 1][DataPemain.PosisiPemain.X];
    SekitaranPemain.D = DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X + 1];
}

void printPeta() {
    int i,j;

    i = 0;
    for (i; i < 5; i++) {
        j = 0;
        for (j; j < 5; j++) {
            printf("%c", DataPemain.KuadranPeta->Isi[i][j]);
        }
        printf("\n");
    }
}

void pindahPeta(char command, Peta* currentPetaKuadran) {
    boolean ditemukan = false;
    int i = 0;

    while (!ditemukan) {
        if (GrafUntukPeta.Edge[i].AsalKuadranPeta == currentPetaKuadran && GrafUntukPeta.Edge[i].InputArah == command) {
            ditemukan = true;
            DataPemain.KuadranPeta = GrafUntukPeta.Edge[i].TargetKuadranPeta;
        }
        i++;
    }
}

void printInventaris() {
    printf("\n");
    printf("Lungmen Dollar: %d\n", Inventaris.Uang);
    printf("D32 Steel: %d\n", Inventaris.BahanBangunan1);
    printf("Bipolar Nanoflake: %d\n", Inventaris.BahanBangunan2);
    printf("Polymerization Preparation: %d\n", Inventaris.BahanBangunan3);
}

int main() {

    Peta petaKuadran1, petaKuadran2, petaKuadran3, petaKuadran4;
    FILE *filePointer;
    int i,j;
    char ch, perintah;

    filePointer = fopen("kuadran1.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        i = 0;
        for (i; i < 5; i++) {
            j = 0;
            for (j; j < 5; j++) {
                ch = fgetc(filePointer);
                petaKuadran1.Isi[i][j] = ch;
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
        i = 0;
        for (i; i < 5; i++) {
            j = 0;
            for (j; j < 5; j++) {
                ch = fgetc(filePointer);
                petaKuadran2.Isi[i][j] = ch;
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
        i = 0;
        for (i; i < 5; i++) {
            j = 0;
            for (j; j < 5; j++) {
                ch = fgetc(filePointer);
                petaKuadran3.Isi[i][j] = ch;
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
        i = 0;
        for (i; i < 5; i++) {
            j = 0;
            for (j; j < 5; j++) {
                ch = fgetc(filePointer);
                petaKuadran4.Isi[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);

    ///// ///// ///// ///// /////

    DataPemain.KuadranPeta = &petaKuadran2;
    DataPemain.PosisiPemain.X = 1;
    DataPemain.PosisiPemain.Y = 1;
    DataPemain.SimbolPemain = 'P';
    DataPemain.SimbolPetak = '-';

    ///// ///// ///// ///// /////

    Garis GarisHubung1;
        GarisHubung1.AsalKuadranPeta = &petaKuadran1;
        GarisHubung1.InputArah = 'a';
        GarisHubung1.TargetKuadranPeta = &petaKuadran2;

    GrafUntukPeta.Edge[0] = GarisHubung1;

        Garis GarisHubung2;
        GarisHubung2.AsalKuadranPeta = &petaKuadran1;
        GarisHubung2.InputArah = 's';
        GarisHubung2.TargetKuadranPeta= &petaKuadran4;

    GrafUntukPeta.Edge[1] = GarisHubung2;

        Garis GarisHubung3;
        GarisHubung3.AsalKuadranPeta = &petaKuadran2;
        GarisHubung3.InputArah = 'd';
        GarisHubung3.TargetKuadranPeta = &petaKuadran1;

    GrafUntukPeta.Edge[2] = GarisHubung3;

        Garis GarisHubung4;
        GarisHubung4.AsalKuadranPeta = &petaKuadran2;
        GarisHubung4.InputArah = 's';
        GarisHubung4.TargetKuadranPeta = &petaKuadran3;

    GrafUntukPeta.Edge[3] = GarisHubung4;

        Garis GarisHubung5;
        GarisHubung5.AsalKuadranPeta = &petaKuadran3;
        GarisHubung5.InputArah = 'w';
        GarisHubung5.TargetKuadranPeta = &petaKuadran2;

    GrafUntukPeta.Edge[4] = GarisHubung5;

        Garis GarisHubung6;
        GarisHubung6.AsalKuadranPeta = &petaKuadran3;
        GarisHubung6.InputArah = 'd';
        GarisHubung6.TargetKuadranPeta = &petaKuadran4;

    GrafUntukPeta.Edge[5] = GarisHubung6;

        Garis GarisHubung7;
        GarisHubung7.AsalKuadranPeta= &petaKuadran4;
        GarisHubung7.InputArah = 'w';
        GarisHubung7.TargetKuadranPeta = &petaKuadran1;

    GrafUntukPeta.Edge[6] = GarisHubung7;

        Garis GarisHubung8;
        GarisHubung8.AsalKuadranPeta = &petaKuadran4;
        GarisHubung8.InputArah = 'a';
        GarisHubung8.TargetKuadranPeta = &petaKuadran3;

    GrafUntukPeta.Edge[7] = GarisHubung8;

    ///// ///// ///// ///// /////

    Inventaris.BahanBangunan1 = 1000;
    Inventaris.BahanBangunan2 = 1000;
    Inventaris.BahanBangunan3 = 1000;
    Inventaris.Uang = 1000;

    ///// ///// ///// ///// /////

    DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;

    printPeta();
    printInventaris();
    update();

    do {
        scanf(" %c", &perintah);

        if (perintah == 'w') {
            if (SekitaranPemain.W == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y--;
                DataPemain.SimbolPetak = SekitaranPemain.W;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            } else if (SekitaranPemain.W == '^') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y = 3;
                pindahPeta(perintah, DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            }
            system("cls");
            printPeta();
            printInventaris();
        } else if (perintah == 'a') {
            if (SekitaranPemain.A == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X--;
                DataPemain.SimbolPetak = SekitaranPemain.A;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            } else if (SekitaranPemain.A == '<') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X = 3;
                pindahPeta(perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            }
            system("cls");
            printPeta();
            printInventaris();
        } else if (perintah == 's') {
            if (SekitaranPemain.S == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y++;
                DataPemain.SimbolPetak = SekitaranPemain.S;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            } else if (SekitaranPemain.S == 'V') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y = 1;
                pindahPeta(perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            }
            system("cls");
            printPeta();
            printInventaris();
        } else if (perintah == 'd') {
            if (SekitaranPemain.D == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X++;
                DataPemain.SimbolPetak = SekitaranPemain.D;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            } else if (SekitaranPemain.D == '>') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X = 1;
                pindahPeta(perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
            }
            system("cls");
            printPeta();
            printInventaris();
        } else if (perintah == 'b') {
            if (SekitaranPemain.A == '<' || SekitaranPemain.D == '>' || SekitaranPemain.W == '^' || SekitaranPemain.S == 'V') {
                printf("Tidak bisa membangun di sini\n");
            } else {
                char IDWahana;
                scanf(" %c", &IDWahana);
                if (IDWahana == 'b') {
                    continue;
                } else {
                    DataPemain.SimbolPetak = IDWahana;
                }
            }
        } else if (perintah == 'u') {
            printf("Menu Pembelian:\n");
            printf("\t1. D32 Steel: 5 LMD\n");
            printf("\t2. Bipolar Nanoflake: 7 LMD\n");
            printf("\t3. Polymerization Preparation: 8 LMD\n");
            printf("\n");

            char Tipe;
            int Jumlah;

            scanf(" %c\n", &Tipe);
            if (Tipe == '1' || Tipe == '2' || Tipe == '3') {
                scanf("%d\n", &Jumlah);
            }
        }


    } while (perintah != 'q');

    return 0;
}
