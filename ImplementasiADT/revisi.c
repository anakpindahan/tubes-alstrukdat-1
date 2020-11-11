#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "boolean.h"

typedef struct {
    int Phase; //PHASE 0 = PREPARATION, PHASE 1 = MAIN
    int Day;
} Stage;

Stage GameStage;

void printStage() {
    if (GameStage.Phase == 0) {
        printf("Persiapan Hari ke-%d\n\n", GameStage.Day);
    } else if (GameStage.Phase == 1) {
        printf("Pembukaan Wahana Hari ke-%d\n\n", GameStage.Day);
    }
}

typedef struct {
    char TabKata[50];
    int Length;
} Kata;

boolean isKataSama(Kata kata1, Kata kata2) {
    boolean sama;

    if (kata1.Length != kata2.Length) {
        sama = false;
    } else {
        sama = true;
        int i = 0;
        while (sama && i < kata1.Length) {
            if (kata1.TabKata[i] != kata2.TabKata[i]) {
                sama = false;
            }
            i++;
        }
    }
    return sama;
}

Kata createKata(char string[]) {
    Kata kataBaru;

    kataBaru.Length = 0;

    int i = 0;

    kataBaru.TabKata[i] = string[i];
    i++;

    while (string[i] != '\0') {
        kataBaru.TabKata[i] = string[i];
        i++;
    }
    kataBaru.Length = i;
    return kataBaru;
}

void printKata(Kata kata) {
    int i = 0;
    for (i; i < kata.Length; i++) {
        printf("%c",kata.TabKata[i]);
    }
}

typedef struct {
    int Jam;
    int Menit;
} Waktu;

Waktu WaktuMain;

void setWaktu(Waktu* waktu, int jam, int menit) {
    waktu->Jam = jam;
    waktu->Menit = menit;
}

void printDalamFormatWaktu(Waktu waktu) {
    if (waktu.Jam > 9) {
        printf("%d", waktu.Jam);
    } else {
        printf("0%d", waktu.Jam);
    }
    if (waktu.Menit > 9) {
        printf(":%d\n", waktu.Menit);
    } else {
        printf(":0%d\n", waktu.Menit);
    }
}

void tambahWaktuMainADTWaktu(Waktu waktu) {
    WaktuMain.Menit = WaktuMain.Menit + waktu.Menit;
    if (WaktuMain.Menit > 59) {
        WaktuMain.Menit = WaktuMain.Menit % 60;
        WaktuMain.Jam++;
    }
    WaktuMain.Jam = (WaktuMain.Jam + waktu.Jam) % 24;
}

void tambahWaktuMainManual(int jam, int menit) {
    WaktuMain.Menit = WaktuMain.Menit + menit;
    if (WaktuMain.Menit > 59) {
        WaktuMain.Menit = WaktuMain.Menit % 60;
        WaktuMain.Jam++;
    }
    WaktuMain.Jam = (WaktuMain.Jam + jam) % 24;
}

Waktu selisihTerhadapWaktuMain(Waktu waktu) {
    Waktu hasilSelisih;

    hasilSelisih.Jam = 0;
    hasilSelisih.Menit = waktu.Menit - WaktuMain.Menit;
    if (hasilSelisih.Menit < 0) {
        hasilSelisih.Menit += 60;
        hasilSelisih.Jam--;
    }
    hasilSelisih.Jam = hasilSelisih.Jam + waktu.Jam - WaktuMain.Jam;
    if (hasilSelisih.Jam < 0) {
        hasilSelisih.Jam += 24;
    }
    return hasilSelisih;
}

typedef struct {
	char Isi[5][5];
} Peta;

typedef struct {
    int X;
    int Y;
} Poin;

typedef struct {
    Poin PosisiPemain;
    Peta* KuadranPeta;
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
    Peta* TargetKuadranPeta;
    char InputArah;
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

void pindahPeta(Kata kata, Peta* currentPetaKuadran) {
    boolean ditemukan = false;
    int i = 0;

    while (!ditemukan) {
        if (GrafUntukPeta.Edge[i].AsalKuadranPeta == currentPetaKuadran && GrafUntukPeta.Edge[i].InputArah == kata.TabKata[0]) {
            ditemukan = true;
            DataPemain.KuadranPeta = GrafUntukPeta.Edge[i].TargetKuadranPeta;
        }
        i++;
    }
}

void printInventaris() {
    printf("\n");
    printf("Lungmen Dollar: %d\n\n", Inventaris.Uang);
    printf("D32 Steel: %d || ", Inventaris.BahanBangunan1);
    printf("Bipolar Nanoflake: %d || ", Inventaris.BahanBangunan2);
    printf("Polymerization Preparation: %d\n\n", Inventaris.BahanBangunan3);
}

int main() {

    Peta petaKuadran1, petaKuadran2, petaKuadran3, petaKuadran4;
    FILE *filePointer;
    int i,j;
    char ch;

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

    ///// ///// ///// ///// /////

    setWaktu(&WaktuMain,21,0);

    Waktu waktuBuka;
    setWaktu(&waktuBuka,9,0);

    Waktu waktuTutup;
    setWaktu(&waktuTutup,21,0);

    ///// ///// ///// ///// /////

    Kata Perintah;

    Kata kata_w = createKata("w");
    Kata kata_a = createKata("a");
    Kata kata_s = createKata("s");
    Kata kata_d = createKata("d");
    Kata kata_quit = createKata("quit");
    Kata kata_prep = createKata("prep");
    Kata kata_main = createKata("main");

    char k_perintah[50];

    ///// ///// ///// ///// /////

    GameStage.Day = 1; GameStage.Phase = 0;

    ///// ///// ///// ///// /////

    printStage();
    printPeta();
    printInventaris();
    printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);
    printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
    Waktu selisih = selisihTerhadapWaktuMain(waktuBuka);
    printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
    update();

    ///// ///// ///// ///// /////

    do {
        printf("\n");
        scanf("%s", k_perintah);

        Perintah = createKata(k_perintah);

        if (isKataSama(kata_w,Perintah)) {
            if (SekitaranPemain.W == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y--;
                DataPemain.SimbolPetak = SekitaranPemain.W;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.W == '^') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y = 3;
                pindahPeta(Perintah, DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.W == 'O') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y--;
                DataPemain.SimbolPetak = SekitaranPemain.W;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            }

            if (GameStage.Phase == 0 && WaktuMain.Jam == waktuBuka.Jam && WaktuMain.Menit == waktuBuka.Menit) {
                GameStage.Phase = 1;
            } else if (GameStage.Phase == 1 && WaktuMain.Jam == waktuTutup.Jam && WaktuMain.Menit == waktuTutup.Menit) {
                GameStage.Phase = 0;
                GameStage.Day++;
            }

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);

            if (GameStage.Phase == 0) {
                printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
                selisih = selisihTerhadapWaktuMain(waktuBuka);
            } else if (GameStage.Phase == 1) {
                printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
                selisih = selisihTerhadapWaktuMain(waktuTutup);
            }

            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_a,Perintah)) {
            if (SekitaranPemain.A == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X--;
                DataPemain.SimbolPetak = SekitaranPemain.A;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.A == '<') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X = 3;
                pindahPeta(Perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.A == 'O') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X--;
                DataPemain.SimbolPetak = SekitaranPemain.A;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            }

            if (GameStage.Phase == 0 && WaktuMain.Jam == waktuBuka.Jam && WaktuMain.Menit == waktuBuka.Menit) {
                GameStage.Phase = 1;
            } else if (GameStage.Phase == 1 && WaktuMain.Jam == waktuTutup.Jam && WaktuMain.Menit == waktuTutup.Menit) {
                GameStage.Phase = 0;
                GameStage.Day++;
            }

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);

            if (GameStage.Phase == 0) {
                printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
                selisih = selisihTerhadapWaktuMain(waktuBuka);
            } else if (GameStage.Phase == 1) {
                printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
                selisih = selisihTerhadapWaktuMain(waktuTutup);
            }

            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_s,Perintah)) {
            if (SekitaranPemain.S == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y++;
                DataPemain.SimbolPetak = SekitaranPemain.S;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.S == 'V') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y = 1;
                pindahPeta(Perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.S == 'O') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y++;
                DataPemain.SimbolPetak = SekitaranPemain.S;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            }

            if (GameStage.Phase == 0 && WaktuMain.Jam == waktuBuka.Jam && WaktuMain.Menit == waktuBuka.Menit) {
                GameStage.Phase = 1;
            } else if (GameStage.Phase == 1 && WaktuMain.Jam == waktuTutup.Jam && WaktuMain.Menit == waktuTutup.Menit) {
                GameStage.Phase = 0;
                GameStage.Day++;
            }

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);

            if (GameStage.Phase == 0) {
                printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
                selisih = selisihTerhadapWaktuMain(waktuBuka);
            } else if (GameStage.Phase == 1) {
                printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
                selisih = selisihTerhadapWaktuMain(waktuTutup);
            }

            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_d,Perintah)) {
            if (SekitaranPemain.D == '-') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X++;
                DataPemain.SimbolPetak = SekitaranPemain.D;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.D == '>') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X = 1;
                pindahPeta(Perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            } else if (SekitaranPemain.D == 'O') {
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X++;
                DataPemain.SimbolPetak = SekitaranPemain.D;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
            }

            if (GameStage.Phase == 0 && WaktuMain.Jam == waktuBuka.Jam && WaktuMain.Menit == waktuBuka.Menit) {
                GameStage.Phase = 1;
            } else if (GameStage.Phase == 1 && WaktuMain.Jam == waktuTutup.Jam && WaktuMain.Menit == waktuTutup.Menit) {
                GameStage.Phase = 0;
                GameStage.Day++;
            }

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);

            if (GameStage.Phase == 0) {
                printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
                selisih = selisihTerhadapWaktuMain(waktuBuka);
            } else if (GameStage.Phase == 1) {
                printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
                selisih = selisihTerhadapWaktuMain(waktuTutup);
            }

            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_prep,Perintah) && GameStage.Phase == 1) {
            setWaktu(&WaktuMain,21,0);
            GameStage.Phase = 0;
            GameStage.Day++;

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);
            printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
            selisih = selisihTerhadapWaktuMain(waktuBuka);
            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_main,Perintah) && GameStage.Phase == 0) {
            setWaktu(&WaktuMain,9,0);
            GameStage.Phase = 1;

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);
            printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
            selisih = selisihTerhadapWaktuMain(waktuTutup);
            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_quit,Perintah)) {
            printf("\nNoice\n");
        }

        /*else if (isKataSama()) {
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
        }*/ else {
            system("cls");
            printf("Input tidak dikenali. Silakan ulangi.");
            sleep(1);

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);

            if (GameStage.Phase == 0) {
                printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
                selisih = selisihTerhadapWaktuMain(waktuBuka);
            } else if (GameStage.Phase == 1) {
                printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
                selisih = selisihTerhadapWaktuMain(waktuTutup);
            }

            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);

            //printf("Input tidak dikenali, silakan ulangi.\n\n");
        }

    } while (!isKataSama(kata_quit,Perintah));

    return 0;
}
