#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "boolean.h"
#include "ADT_waktu.c"
#include "ADT_kata.c"
#include "ADT_stack.c"
#include "ADT_tree.c"
#include "ADT_Peta.c"
#include "ADT_GrafPeta.c"

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
	int Indeks;
	int Tipe;
	Kata Nama;
	int HargaTiket;
	Inventory HargaBangun;
	int Durasi;
	int Kapasitas;
	Kata Deskripsi;
	int Upgrade[6];
} Wahana;

typedef struct{
	int Indeks;
	Poin Posisi;
	int Kerusakan;
	Kata Nama;
	Inventory HargaBangun;
} WahanaDibangun;

WahanaDibangun ListWahanaDibangun[25];

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
    for (i; i < Ukuran_Peta; i++) {
        j = 0;
        for (j; j < Ukuran_Peta; j++) {
            printf("%c", DataPemain.KuadranPeta->Isi[i][j]);
        }
        printf("\n");
    }
}

void pindahPeta(Kata kata, Peta* currentPetaKuadran) {
    /*
    boolean ditemukan = false;
    int i = 0;

    while (!ditemukan) {
        if (GrafUntukPeta.Edge[i].AsalKuadranPeta == currentPetaKuadran && GrafUntukPeta.Edge[i].InputArah == kata.TabKata[0]) {
            ditemukan = true;
            DataPemain.KuadranPeta = GrafUntukPeta.Edge[i].TargetKuadranPeta;
        }
        i++;
    }*/
    DataPemain.KuadranPeta = GrafSearchTarget(GrafPeta,DataPemain.KuadranPeta,kata.TabKata[0]);
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

    ///// ///// ///// ///// /////

    bacaPeta("kuadran1.txt",&petaKuadran1);
    bacaPeta("kuadran2.txt",&petaKuadran2);
    bacaPeta("kuadran3.txt",&petaKuadran3);
    bacaPeta("kuadran4.txt",&petaKuadran4);

    ///// ///// ///// ///// /////

    adrGrafNode Pn = GrafAlokNode(&petaKuadran1);
    GrafPeta.First = Pn;

    GrafInsertNode(GrafPeta, &petaKuadran2);

    GrafInsertNode(GrafPeta, &petaKuadran3);
    GrafInsertNode(GrafPeta, &petaKuadran4);

    GrafInsertEdge(GrafPeta, &petaKuadran1, &petaKuadran2, 'a');

    GrafInsertEdge(GrafPeta, &petaKuadran1, &petaKuadran4, 's');

    GrafInsertEdge(GrafPeta, &petaKuadran2, &petaKuadran1, 'd');
    GrafInsertEdge(GrafPeta, &petaKuadran2, &petaKuadran3, 's');

    GrafInsertEdge(GrafPeta, &petaKuadran3, &petaKuadran2, 'w');
    GrafInsertEdge(GrafPeta, &petaKuadran3, &petaKuadran4, 'd');

    GrafInsertEdge(GrafPeta, &petaKuadran4, &petaKuadran3, 'a');
    GrafInsertEdge(GrafPeta, &petaKuadran4, &petaKuadran1, 'w');

    ///// ///// ///// ///// /////

	Wahana wahana;
	Wahana ListWahana[25];
	int BanyakWahana = 0;

    char buff[255];
    char* token, *tokenSec;

    filePointer = fopen("wahana.txt", "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
    	int i = 0;
    	while(fgets(buff, 255, filePointer) != NULL){
			token = strtok(buff, ";");
    		wahana.Indeks = atoi(token);

    		token = strtok(NULL, ";");
    		wahana.Tipe = atoi(token);

       		token = strtok(NULL, ";");
      		wahana.Nama = createKata(token);

    		token = strtok(NULL, ";");
    		wahana.HargaTiket = atoi(token);

    		token = strtok(NULL, ";");

			tokenSec = strtok(token, ",");
    		wahana.HargaBangun.Uang = atoi(tokenSec);

			tokenSec = strtok(NULL, ",");
			wahana.HargaBangun.BahanBangunan1 = atoi(tokenSec);

			tokenSec = strtok(NULL, ",");
			wahana.HargaBangun.BahanBangunan2 = atoi(tokenSec);

			tokenSec = strtok(NULL, ",");
			wahana.HargaBangun.BahanBangunan3 = atoi(tokenSec);

    		token = strtok(NULL, ";");
    		wahana.Durasi = atoi(token);

    		token = strtok(NULL, ";");
    		wahana.Kapasitas = atoi(token);

    		token = strtok(NULL, ";");
//			wahana.Deskripsi = createKata(token);

    		token = strtok(NULL, ";");
    		if(token != NULL){
    			int j = 0;
    			tokenSec = strtok(token, ",");
    			wahana.Upgrade[j] = atoi(tokenSec);
				while(tokenSec != NULL){
					tokenSec = strtok(NULL, ",");
					j++;
					wahana.Upgrade[j] = atoi(tokenSec);
				}
			}

			ListWahana[i] = wahana;
			i++;
			BanyakWahana++;
		}

    }

    fclose(filePointer);

    int BanyakWahanaDibangun = 0;

/*    for(i = 0; i < BanyakWahana; i++){
    	printf("%d %d ", ListWahana[i].Indeks, ListWahana[i].Tipe);
    	printKata(ListWahana[i].Nama);
    	printf("%d %d %d %d %d %d %d\n", ListWahana[i].HargaTiket, ListWahana[i].HargaBangun.Uang, ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2, ListWahana[i].HargaBangun.BahanBangunan3, ListWahana[i].Durasi, ListWahana[i].Kapasitas);
	}*/

    ///// ///// ///// ///// /////

    DataPemain.KuadranPeta = &petaKuadran2;
    DataPemain.PosisiPemain.X = 1;
    DataPemain.PosisiPemain.Y = 1;
    DataPemain.SimbolPemain = 'P';
    DataPemain.SimbolPetak = '-';

    ///// ///// ///// ///// /////
/*
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
*/
    ///// ///// ///// ///// /////

    Inventaris.BahanBangunan1 = 1000;
    Inventaris.BahanBangunan2 = 1000;
    Inventaris.BahanBangunan3 = 1000;
    Inventaris.Uang = 1000;

    int HutangUang = 0;
    int HutangBB1 = 0;
    int HutangBB2 = 0;
    int HutangBB3 = 0;

    ///// ///// ///// ///// /////

    DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;

    ///// ///// ///// ///// /////

    setWaktu(&WaktuMain,21,0);

	Waktu waktuBuka;
    setWaktu(&waktuBuka,9,0);

	Waktu waktuTutup;
    setWaktu(&waktuTutup,21,0);

    Waktu durasiExecute;
    setWaktu(&durasiExecute, 0, 0);

    ///// ///// ///// ///// /////

    Stack DaftarPerintah;
    Stack DaftarPerintahExec;
    BuatStack(&DaftarPerintah);
    BuatStack(&DaftarPerintahExec);

    //// //// ///// ///// //////

    Kata Perintah;

    Kata kata_w = createKata("w");
    Kata kata_a = createKata("a");
    Kata kata_s = createKata("s");
    Kata kata_d = createKata("d");
    Kata kata_quit = createKata("quit");
    Kata kata_prep = createKata("prep");
    Kata kata_main = createKata("main");
    Kata kata_build = createKata("build");
    Kata kata_upgrade = createKata("upgrade");
    Kata kata_buy = createKata("buy");
    Kata kata_repair = createKata("repair");
    Kata kata_execute = createKata("execute");
    Kata kata_undo = createKata("undo");
    Kata kata_office = createKata("office");
    Kata kata_serve = createKata("serve");
    Kata kata_detail = createKata("detail");

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

        Perintah = readInput();

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
                DataPemain.PosisiPemain.Y = Map_Y_Max;
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
                DataPemain.PosisiPemain.X = Map_X_Max;
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
                DataPemain.PosisiPemain.Y = Map_X_Min;
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
                DataPemain.PosisiPemain.X = Map_X_Min;
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
        	Tupel X;
			HutangUang = 0;
			HutangBB1 = 0;
			HutangBB2 = 0;
			HutangBB3 = 0;
			setWaktu(&durasiExecute, 0, 0);
			while(!StackKosong(DaftarPerintah)){
        		Pop(&DaftarPerintah, &X);
			}
			printf("Stack perintah Anda telah dikosongkan\n");
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
        } else if (isKataSama(kata_build,Perintah)) {
            if (diMainPhase(WaktuMain)) {
				printf("Hanya bisa membangun pada saat preparation phase\n");
            } else if(SekitaranPemain.A == '<' || SekitaranPemain.D == '>' || SekitaranPemain.W == '^' || SekitaranPemain.S == 'V'){
                printf("Tidak bisa membangun di sini\n");
			} else if(diMainPhase(tambahWaktu(WaktuMain, tambahWaktuManualF(durasiExecute, 0, 10)))){
				printf("Waktu eksekusi tidak akan mencukupi\n");
			} else {
            	int IDWahana;

            	printf("Silahkan pilih wahana apa yang ingin dibangun.\n");
            	int i;
            	for(i = 0; i < BanyakWahana; i++){
            		if(ListWahana[i].Tipe == 1){
            			printf("%d. ", ListWahana[i].Indeks);
						printKata(ListWahana[i].Nama);
						printf("\n");
            			printf("Harga yang perlu dibayar adalah %d Lungmen Dollar,", ListWahana[i].HargaBangun.Uang);
						printf("%d D32 Steel, %d Bipolar Nanoflake,", ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2);
						printf("dan %d Polymerization Preparation\n", ListWahana[i].HargaBangun.BahanBangunan3);
					}
				}
				printf("Masukkan nomor wahana yang ingin dibangun.\n");

                scanf("%d", &IDWahana);


                i = 0;
                boolean found = false;
                while(i < BanyakWahana && !found){
                	if((ListWahana[i].Indeks == IDWahana) && (ListWahana[i].Tipe == 1)){
                		found = true;
                		if((Inventaris.Uang < ListWahana[i].HargaBangun.Uang + HutangUang) || (Inventaris.BahanBangunan1 < ListWahana[i].HargaBangun.BahanBangunan1 + HutangBB1) || (Inventaris.BahanBangunan2 < ListWahana[i].HargaBangun.BahanBangunan2 + HutangBB2) || (Inventaris.BahanBangunan3 < ListWahana[i].HargaBangun.BahanBangunan3 + HutangBB3)){
                			printf("Resource Anda tidak mencukupi");
						} else {
		                	int tupelBuild[9];
		                	tupelBuild[0] = 1;
		                	tupelBuild[1] = ListWahana[i].Indeks;
		                	tupelBuild[2] = -1*ListWahana[i].HargaBangun.Uang;
							tupelBuild[3] = -1*ListWahana[i].HargaBangun.BahanBangunan1;
							tupelBuild[4] = -1*ListWahana[i].HargaBangun.BahanBangunan2;
							tupelBuild[5] = -1*ListWahana[i].HargaBangun.BahanBangunan3;
							tupelBuild[6] = 0;
							tupelBuild[7] = DataPemain.PosisiPemain.X;
							tupelBuild[8] = DataPemain.PosisiPemain.Y;
							HutangUang -= tupelBuild[2];
							HutangBB1 -= tupelBuild[3];
							HutangBB2 -= tupelBuild[4];
							HutangBB3 -= tupelBuild[5];
		                	Push(&DaftarPerintah, tupelBuild);
							printf("SJJAKSN\n");
		                	tambahWaktuManualP(durasiExecute, 1, 0);
						}
					}
					i++;
				}
            }
        } /*else if (perintah == 'u') {
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
        }*/ else if(isKataSama(kata_upgrade, Perintah)){
        	boolean wahanaSekitar[4];
        	wahanaSekitar[0] = (SekitaranPemain.A == 'W');
        	wahanaSekitar[1] = (SekitaranPemain.W == 'W');
        	wahanaSekitar[2] = (SekitaranPemain.S == 'W');
        	wahanaSekitar[3] = (SekitaranPemain.D == 'W');
			if((!wahanaSekitar[0]) && (wahanaSekitar[1]) && (wahanaSekitar[2]) && (wahanaSekitar[3])){
				printf("Gak ada apa-apa woy, mau upgrade apa?");
			} else {
				int IDupgrade;
				int i;
				Poin PosisiWahana;
				printf("Pilihlah wahana yang ingin diupgrade\n");
				for(i = 0; i < 4; i++){
					if(wahanaSekitar[i]){
						switch(i){
							case 0:
								PosisiWahana.X = DataPemain.PosisiPemain.X ;
								PosisiWahana.Y = DataPemain.PosisiPemain.Y - 1;
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == PosisiWahana.X && ListWahanaDibangun[j].Posisi.Y == PosisiWahana.Y){
										printf("%d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\nHarga yang perlu dibayar adalah %d Lungmen Dollar,", ListWahana[i].HargaBangun.Uang);
										printf("%d D32 Steel, %d Bipolar Nanoflake,", ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2);
										printf("dan %d Polymerization Preparation\n", ListWahana[i].HargaBangun.BahanBangunan3);
									}
								}
								break;
							case 1:
								PosisiWahana.X = DataPemain.PosisiPemain.X - 1;
								PosisiWahana.Y = DataPemain.PosisiPemain.Y;
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == PosisiWahana.X && ListWahanaDibangun[j].Posisi.Y == PosisiWahana.Y){
										printf("%d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\nHarga yang perlu dibayar adalah %d Lungmen Dollar,", ListWahana[i].HargaBangun.Uang);
										printf("%d D32 Steel, %d Bipolar Nanoflake,", ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2);
										printf("dan %d Polymerization Preparation\n", ListWahana[i].HargaBangun.BahanBangunan3);
									}
								}
								break;
							case 2:
								PosisiWahana.X = DataPemain.PosisiPemain.X + 1;
								PosisiWahana.Y = DataPemain.PosisiPemain.Y;
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == PosisiWahana.X && ListWahanaDibangun[j].Posisi.Y == PosisiWahana.Y){
										printf("%d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\nHarga yang perlu dibayar adalah %d Lungmen Dollar,", ListWahana[i].HargaBangun.Uang);
										printf("%d D32 Steel, %d Bipolar Nanoflake,", ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2);
										printf("dan %d Polymerization Preparation\n", ListWahana[i].HargaBangun.BahanBangunan3);
									}
								}
								break;
							case 3:
								PosisiWahana.X = DataPemain.PosisiPemain.X;
								PosisiWahana.Y = DataPemain.PosisiPemain.Y + 1;
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == PosisiWahana.X && ListWahanaDibangun[j].Posisi.Y == PosisiWahana.Y){
										printf("%d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\nHarga yang perlu dibayar adalah %d Lungmen Dollar,", ListWahana[i].HargaBangun.Uang);
										printf("%d D32 Steel, %d Bipolar Nanoflake,", ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2);
										printf("dan %d Polymerization Preparation\n", ListWahana[i].HargaBangun.BahanBangunan3);
									}
								}
								break;
						}
					}


				}
				// Ngeprint semua wahana di sekitar
				// Pilih wahana
				// Ngeprint semua upgrade yang ada
				scanf("%d", &IDupgrade);
/*				if(Salah milih upgrade){
					printf("Gak ada");
				} else if(Gak cukup resource){
					printf("Gak ada duit");
				} else {

                	int tupelUpgrade[7];
                	tupelUpgrade[0] = 2;
                	tupelUpgrade[1] = wahana.ID;
                	tupelUpgrade[2] = Baca
					tupelUpgrade[3] =   Dari
					tupelUpgrade[4] =   File
					tupelUpgrade[5] =   Eksternal
					tupelUpgrade[6] = IDupgrade;
					tupelUpgrade[7] = 90;
                	Push(&DaftarPerintah, tupelUpgrade);

                	tambahWaktu(waktuExecute, 1, 30);
				}*/
			}
		} else if(isKataSama(kata_buy, Perintah)){
            printf("Menu Pembelian:\n");
            printf("\t1. D32 Steel: 5 LMD\n");
            printf("\t2. Bipolar Nanoflake: 7 LMD\n");
            printf("\t3. Polymerization Preparation: 8 LMD\n");
            printf("\n");
            printf("Tuliskan angka dari benda yang ingin dibeli\n");

            char Tipe;
            int Jumlah;

            scanf("%d", &Tipe);
            while(!((Tipe == 1) || (Tipe == 2) || (Tipe == 3))){
            	printf("Masukin yang bener\n");
            	scanf("%d", &Tipe);
			}
			printf("Mau beli berapa?");
			scanf("%d", &Jumlah);
			printf("Baik, akan segera diproses\n");
			printf("Mohon tunggu beberapa saat\n");
            int tupelBuy[9];
            tupelBuy[0] = 3;
            tupelBuy[1] = 0;
	        tupelBuy[2] = 0;
			tupelBuy[3] = 0;
			tupelBuy[4] = 0;
			tupelBuy[5] = 0;
			tupelBuy[6] = 0;
			tupelBuy[7] = -999;
			tupelBuy[8] = -999;
			if(Tipe == 1){
				tupelBuy[3] += Jumlah;
				tupelBuy[2] += -5*Jumlah;
			} else if(Tipe == 2){
				tupelBuy[4] += Jumlah;
				tupelBuy[2] += -7*Jumlah;
			} else if(Tipe == 3){
				tupelBuy[5] += Jumlah;
				tupelBuy[2] += -9*Jumlah;
			}
	        Push(&DaftarPerintah, tupelBuy);
            tambahWaktuManualP(durasiExecute, 0, 20);
		} else if(isKataSama(kata_repair, Perintah)){
			// Tampilkan wahana di sebelah pemain
			// Pilih wahana
		} else if(isKataSama(kata_execute, Perintah)){
			Tupel X;
			while(!StackKosong(DaftarPerintah)){
				Pop(&DaftarPerintah, &X);
				Push(&DaftarPerintahExec, X);
			}
			while(!StackKosong(DaftarPerintahExec)){
				Pop(&DaftarPerintahExec, &X);
				switch(X[0]){
					case 1: // Build
						i = X[1];
						WahanaDibangun NewWahana;
						Inventaris.Uang += X[2];
						Inventaris.BahanBangunan1 += X[3];
						Inventaris.BahanBangunan2 += X[4];
						Inventaris.BahanBangunan3 += X[5];
					//	DataPemain.SimbolPetak = 'W';
						NewWahana.Indeks = X[1];
						NewWahana.Posisi.X = X[7];
						NewWahana.Posisi.Y = X[8];
						NewWahana.Kerusakan = 0;
						DataPemain.KuadranPeta->Isi[NewWahana.Posisi.X][NewWahana.Posisi.Y] = 'W';
						// GANTI SIMBOL DI PETA MENJADI W
						ListWahanaDibangun[BanyakWahanaDibangun] = NewWahana;
						BanyakWahanaDibangun++;
						tambahWaktuMainManual(1, 0);
						printf("Selamat, wahana telah dibangun\n");
						break;
					case 2:
							// Upgrade
						break;
					case 3: // Buy
						Inventaris.BahanBangunan1 += X[3];
						Inventaris.BahanBangunan2 += X[4];
						Inventaris.BahanBangunan3 += X[5];
						Inventaris.Uang += X[2];
						tambahWaktuMainManual(0, 20);
						break;
				}
				HutangUang = 0;
				HutangBB1 = 0;
				HutangBB2 = 0;
				HutangBB3 = 0;
				setWaktu(&durasiExecute, 0, 0);
			}
		} else if(isKataSama(kata_undo, Perintah)){
			Tupel X;
			if(StackKosong(DaftarPerintah)){
				printf("Anda tidak memiliki perintah yang dapat diundo");
			} else {
				Pop(&DaftarPerintah, &X);
			}
		} else if(isKataSama(kata_office, Perintah)){

		} else if(isKataSama(kata_serve, Perintah)){

		} else if(isKataSama(kata_repair, Perintah)){

		} else if(isKataSama(kata_detail, Perintah)){

		} else {
            system("cls");
            printf("Input tidak dikenali. Silakan ulangi.");
            sleep(1);

            system("cls");
            printStage();
            printPeta(11);
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

    } while(!isKataSama(kata_quit,Perintah));

    return 0;
}
