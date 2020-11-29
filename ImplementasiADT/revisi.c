#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h> // Untuk keperluan randomizer, bukan untuk waktu
#include "./src/Boolean/boolean.h"
#include "./src/Waktu/ADT_waktu.h"
#include "./src/Kata/ADT_kata.h"
#include "./src/Stack/ADT_stack.h"
#include "./src/Tree/ADT_tree.h"
#include "./src/Peta/ADT_Peta.h"
#include "./src/GrafPeta/ADT_GrafPeta.h"
#include "./src/LinkedList/ADT_linkedlist.h"
#include "./src/Poin/ADT_poin.h"
#include "./src/array/array.h"
#include "./src/Queue/ADT_queue.h"

char dummyChar; // --> Kontainer untuk scanf '\n'
char nama_pemain[50]; // --> Kontainer untuk nama pemain

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
    Poin PosisiPemain;
    Peta* KuadranPeta;
    char SimbolPemain;
    char SimbolPetak;
    int Kuadran;
} Pemain;

Pemain DataPemain;

typedef struct {
    int Uang;
    int BahanBangunan1;
    int BahanBangunan2;
    int BahanBangunan3;
} Inventory;

Inventory Inventaris;

Graph GrafPeta;
IDPetaUmum Identitas_Peta;

typedef struct {
	int Indeks;
	int Tipe;
	Kata Nama;
	int HargaTiket;
	Inventory HargaBangun;
	int Durasi;
	int Kapasitas;
	Kata Deskripsi;
	int Upgrade;
} Wahana;

typedef struct{
	int Indeks;
	Poin Posisi;
	int Kuadran;
	int Kerusakan;
	Kata Nama;
	LinkedList Upgrade;
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
    for (i; i < DataPemain.KuadranPeta->NBrsEff; i++) {
        j = 0;
        for (j; j < DataPemain.KuadranPeta->NKolEff; j++) {
            printf("%c", DataPemain.KuadranPeta->Isi[i][j]);
        }
        printf("\n");
    }
    printf("\nLegend:\n");
    printf("A : Antrian\n");
    printf("P : Pemain\n");
    printf("W : Wahana\n");
    printf("O : Office\n");
    printf("^, <, V, > : Gerbang\n\n");
    printf("Nama: %s\n", nama_pemain);
}

void pindahPeta(Kata kata, Peta* currentPetaKuadran) {
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

    printf("                                       ##   ##                                              \n");
    printf("                                       ##   ##  ##      ##                                  \n");
    printf(" ########               ########  ##   ##   ##   ##    ##                                   \n");
    printf("   #####                 #####         ##   ##    ##  ##                                    \n");
    printf("     ###                 ###      ##   ##   ##     ####                                     \n");
    printf("      ###       #       ###       ##   ##   ##      ##                                      \n");
    printf("      ###      ###      ###       ##   ###  ###    ##         ##                    ###                 \n");
    printf("       ###    #####    ###                        ##          ##                    ###                 \n");
    printf("       ###   ### ###   ###     #####    ## ####  ##  ######   ##  ##   ##       ##    #   #####         \n");
    printf("        ### ###   ### ###          ##   ###   ##    ##   ##   #####     ##     ##    #   ##             \n");
    printf("        #####      #####       ######   ##    ##   ##    ##   #####      ##   ##          ####          \n");
    printf("         ###        ###       ##   ##   ##    ##    ##   ##   ##  ##       ####              ##         \n");
    printf("          #          #         ######   ##    ##     ######   ##   ##       ##           #####          \n");
    printf("                                                         ##                ##                           \n");
    printf("                                                    ##  ##                ##                            \n");
    printf("                                                     ####                ##                             \n");
    printf("                                                                                                                \n");
    printf("   # # #                   # # #    # # # # # #     # # # # # #      # # #         # # # # #        # # # #     \n");
    printf("   #    #                 #    #   #           #    #          #     #   #         #        #       #     #     \n");
    printf("    #    #       #       #    #   #    # # #    #   #   # # #   #    #   #         #   # #   #      #     #     \n");
    printf("     #    #     # #     #    #    #    #   #    #   #   #    #   #   #   #         #   #  #   #     #     #     \n");
    printf("      #    #   #   #   #    #     #    #   #    #   #   # # #   #    #   #         #   #   #   #    #     #     \n");
    printf("       #    # #     # #    #      #    #   #    #   #          #     #   #         #   #   #   #     #   #      \n");
    printf("        #    #   #   #    #       #    #   #    #   #   #     #      #   #         #   #  #   #       # #       \n");
    printf("         #      # #      #        #    # # #    #   #   # #    #     #   # # # #   #   # #   #                  \n");
    printf("          #    #   #    #          #           #    #   #  #    #    #         #   #        #         # #       \n");
    printf("           #  #     #  #            # # # # # #     # # #   # #  #   # # # # # #   # # # # #          # #       \n");
    printf("\n");
    printf("MAIN MENU:     \n");
    printf("  1. NEW GAME   \n");
    printf("  2. QUIT GAME  \n\n");

    int opsiMenu;

    do {
    printf("Input angka: ");
    scanf("%d", &opsiMenu);
    scanf("%c", &dummyChar);
    // Input menu tidak valid
    if (opsiMenu < 1 || opsiMenu > 2) {
        printf("Opsi tidak valid. Silakan ulangi!\n\n");
    }
    } while (opsiMenu < 1 || opsiMenu > 2);

    if (opsiMenu == 2) {
        return 0;
    } else if (opsiMenu == 1) {
    printf("Nama pemain: ");
    scanf("%s", nama_pemain);
    scanf("%c", &dummyChar);
    system("cls");
    printf("Membuka dunia baru...");
    sleep(1);
    system("cls");

    Peta petaKuadran1, petaKuadran2, petaKuadran3, petaKuadran4;
    FILE *filePointer;
    int i,j;
    char ch;

    ///// ///// ///// ///// /////

    bacaPeta("kuadran1.txt",&petaKuadran1);
    bacaPeta("kuadran2.txt",&petaKuadran2);
    bacaPeta("kuadran3.txt",&petaKuadran3);
    bacaPeta("kuadran4.txt",&petaKuadran4);

    Identitas_Peta.Map_X_Min = 1;
    Identitas_Peta.Map_Y_Min = 1;
    Identitas_Peta.Map_X_Max = petaKuadran1.NKolEff - 2;
    Identitas_Peta.Map_Y_Max = petaKuadran1.NBrsEff - 2;

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
    		wahana.HargaBangun.Uang = atoi(token);

			token = strtok(NULL, ";");
			wahana.HargaBangun.BahanBangunan1 = atoi(token);

			token = strtok(NULL, ";");
			wahana.HargaBangun.BahanBangunan2 = atoi(token);

			token = strtok(NULL, ";");
			wahana.HargaBangun.BahanBangunan3 = atoi(token);

    		token = strtok(NULL, ";");
    		wahana.Durasi = atoi(token);

    		token = strtok(NULL, ";");
    		wahana.Kapasitas = atoi(token);

    		token = strtok(NULL, ";");
			wahana.Deskripsi = createKata(token);

    		token = strtok(NULL, ";");
			wahana.Upgrade = atoi(token);

			ListWahana[i] = wahana;
			i++;
			BanyakWahana++;
		}

    }

    fclose(filePointer);

    int BanyakWahanaDibangun = 0;

    Tree TreeUpgrade;
    TupelUp DummyUpgrade;
    TupelUp NewUp;
    DummyUpgrade[0] = 0;
    DummyUpgrade[1] = 0;
    DummyUpgrade[2] = 0;
    DummyUpgrade[3] = 0;
    DummyUpgrade[4] = 0;
    DummyUpgrade[5] = 0;

    TreeUpgrade = BuatTreeF(DummyUpgrade, Nil, Nil);

    for(i = 0; i < BanyakWahana; i++){
   		NewUp[0] = ListWahana[i].Indeks;
    	NewUp[1] = ListWahana[i].HargaBangun.Uang;
    	NewUp[2] = ListWahana[i].HargaBangun.BahanBangunan1;
    	NewUp[3] = ListWahana[i].HargaBangun.BahanBangunan2;
    	NewUp[4] = ListWahana[i].HargaBangun.BahanBangunan3;
    	NewUp[5] = ListWahana[i].Upgrade;
		TambahUpgrade(ListWahana[i].Upgrade, NewUp, &TreeUpgrade);
	}

    ///// ///// ///// ///// /////

    DataPemain.KuadranPeta = &petaKuadran2;
    DataPemain.PosisiPemain.X = 1;
    DataPemain.PosisiPemain.Y = 1;
    DataPemain.SimbolPemain = 'P';
    DataPemain.SimbolPetak = '-';
    DataPemain.Kuadran = 2;

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
    Kata kata_Reports = createKata("Reports");
    Kata kata_Exit = createKata("Exit");

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

    BacaBahan_dari_File("materials.txt");

    ///// ///// ///// ///// /////

    do {
        printf("\n");

        Perintah = readInput();

        if (isKataSama(kata_w,Perintah)) {
        	if(SekitaranPemain.W == 'O'){
        		DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.Y--;
                DataPemain.SimbolPetak = SekitaranPemain.W;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);	
                system("cls");
                
                Kata inoffice;
				do{
                	printf("------------SELAMAT DATANG DI WILLY WANGKY\'S OFFICE------------\n");
                	printf("Silahkan masukkan perintah yang ingin dilakukan:\n");
					printf("1. office: Melihat detail semua wahana yang ada\n");
					printf("2. Reports: Melihat laporan wahana\n");
					printf("3. Exit: Keluar menu office\n");
					printf("Silahkan masukkan perintah:\n");
					Kata inoffice;
					inoffice = readInput();
					if(isKataSama(kata_office, inoffice)){
						// TAMPILKAN DETAIL
						int i = 0, j = 0;
						int X;
						char Dummy;
						if(BanyakWahanaDibangun == 0){
							printf("Belum ada wahana yang dibangun, coba bangun beberapa wahana\n");
							scanf("%c", &Dummy);
							system("cls");
						} else {
							for(i = 0; i < BanyakWahanaDibangun;i++){
								printf("%d. ", i);
								printKata(ListWahanaDibangun[i].Nama);
								printf("\n");
							}
							printf("Silahkan masukkan nomor wahana yang ingin dilihat:\n");
							scanf("%d", &X);
							char Dummy;
							scanf("%c", &Dummy);
							
							boolean found = false;
							while(!found){
								if(ListWahana[j].Indeks == ListWahanaDibangun[X].Indeks){
									found = true;
								} else {
									j++;
								}
							}
							
							printf("-------------DETAIL WAHANA-------------\n");
							printf("Nama: ");
							printKata(ListWahanaDibangun[X].Nama);
							printf("\nTipe Wahana: %d\n", ListWahana[j].Tipe);
							printf("Indeks Wahana: %d\n", ListWahana[j].Indeks);
							printf("Harga Tiket Wahana: %d Lungmen Dollar\n", ListWahana[j].HargaTiket);
							printf("Lokasi wahana: (%d, %d) di kuadran %d\n", ListWahanaDibangun[X].Posisi.X, ListWahanaDibangun[X].Posisi.Y, ListWahanaDibangun[X].Kuadran);
							printf("Deskripsi wahana: ");
							printKata(ListWahana[j].Deskripsi);
							printf("\nKapasitas wahana: %d orang\n", ListWahana[j].Kapasitas);
							printf("History Upgrade Wahana:\n");
							PrintLL(ListWahanaDibangun[X].Upgrade);
							addressLL aLL = First(ListWahanaDibangun[X].Upgrade);
							found = false;
							i = 0;
							printf("(");
							while(!found){
								if(ListWahana[i].Indeks == InfoIdx(aLL)){
									found = true;
								} else {
									i++;
								}
							}
							printKata(ListWahana[i].Nama);
							while(Next(aLL) != Nil){
								aLL = Next(aLL);
								found = false;
								i = 0;
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(aLL)){
										found = true;
										printf(" -> ");
										printKata(ListWahana[i].Nama);
									} else {
										i++;
									}
								}
							}
							printf(")\n");
							printf("Durasi wahana: %d menit\n", ListWahana[j].Durasi);	
							scanf("%c", &Dummy);
							system("cls");						
						}
					} else if(isKataSama(kata_Reports, inoffice)){
						// TAMPILKAN LAPORAN
					} else if(isKataSama(kata_Exit, inoffice)) {
						printf("Terima kasih sudah berkunjung ke office hari ini\n");
						sleep(1);
						system("cls");
						break;
					} else {
						printf("Perintah tidak dikenal\n");
						sleep(1);
						system("cls");
					}
				} while(!isKataSama(kata_Exit, inoffice));
			} else {
				if (SekitaranPemain.W == '-') {
	                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
	                DataPemain.PosisiPemain.Y--;
	                DataPemain.SimbolPetak = SekitaranPemain.W;
	                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
	                update();
	                tambahWaktuMainManual(0,1);
	            } else if (SekitaranPemain.W == '^') {
	                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
	                DataPemain.PosisiPemain.Y = Identitas_Peta.Map_Y_Max;
	                pindahPeta(Perintah, DataPemain.KuadranPeta);
	                DataPemain.SimbolPetak = '-';
	                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
	                if(DataPemain.Kuadran == 3){
	                	DataPemain.Kuadran = 2;
					} else if(DataPemain.Kuadran == 4){
						DataPemain.Kuadran = 1;
					}
					update();
	                tambahWaktuMainManual(0,1);
	            } 
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
                DataPemain.PosisiPemain.X = Identitas_Peta.Map_X_Max;
                pindahPeta(Perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                if(DataPemain.Kuadran == 1){
                	DataPemain.Kuadran = 2;
				} else if(DataPemain.Kuadran == 4){
					DataPemain.Kuadran = 3;
				}
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
                DataPemain.PosisiPemain.Y = Identitas_Peta.Map_X_Min;
                pindahPeta(Perintah,DataPemain.KuadranPeta);
                DataPemain.SimbolPetak = '-';
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                if(DataPemain.Kuadran == 1){
                	DataPemain.Kuadran = 4;
				} else if(DataPemain.Kuadran == 2){
					DataPemain.Kuadran = 3;
				}
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
        	if(SekitaranPemain.D == 'O'){
        		DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                DataPemain.PosisiPemain.X++;
                DataPemain.SimbolPetak = SekitaranPemain.D;
                DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                update();
                tambahWaktuMainManual(0,1);
                system("cls");
                
                Kata inoffice;
				do{
                	printf("------------SELAMAT DATANG DI WILLY WANGKY\'S OFFICE------------\n");
                	printf("Silahkan masukkan perintah yang ingin dilakukan:\n");
					printf("1. office: Melihat detail semua wahana yang ada\n");
					printf("2. Reports: Melihat laporan wahana\n");
					printf("3. Exit: Keluar menu office\n");
					printf("Silahkan masukkan perintah:\n");
					Kata inoffice;
					inoffice = readInput();
					if(isKataSama(kata_office, inoffice)){
						// TAMPILKAN DETAIL
						int i = 0, j = 0;
						int X;
						char Dummy;
						if(BanyakWahanaDibangun == 0){
							printf("Belum ada wahana yang dibangun, coba bangun beberapa wahana\n");
							scanf("%c", &Dummy);
							system("cls");
						} else {
							for(i = 0; i < BanyakWahanaDibangun;i++){
								printf("%d. ", i);
								printKata(ListWahanaDibangun[i].Nama);
								printf("\n");
							}
							printf("Silahkan masukkan nomor wahana yang ingin dilihat:\n");
							scanf("%d", &X);
							char Dummy;
							scanf("%c", &Dummy);
							
							boolean found = false;
							while(!found){
								if(ListWahana[j].Indeks == ListWahanaDibangun[X].Indeks){
									found = true;
								} else {
									j++;
								}
							}
							
							printf("-------------DETAIL WAHANA-------------\n");
							printf("Nama: ");
							printKata(ListWahanaDibangun[X].Nama);
							printf("\nTipe Wahana: %d\n", ListWahana[j].Tipe);
							printf("Indeks Wahana: %d\n", ListWahana[j].Indeks);
							printf("Harga Tiket Wahana: %d Lungmen Dollar\n", ListWahana[j].HargaTiket);
							printf("Lokasi wahana: (%d, %d) di kuadran %d\n", ListWahanaDibangun[X].Posisi.X, ListWahanaDibangun[X].Posisi.Y, ListWahanaDibangun[X].Kuadran);
							printf("Deskripsi wahana: ");
							printKata(ListWahana[j].Deskripsi);
							printf("\nKapasitas wahana: %d orang\n", ListWahana[j].Kapasitas);
							printf("History Upgrade Wahana:\n");
							PrintLL(ListWahanaDibangun[X].Upgrade);
							addressLL aLL = First(ListWahanaDibangun[X].Upgrade);
							found = false;
							i = 0;
							printf("(");
							while(!found){
								if(ListWahana[i].Indeks == InfoIdx(aLL)){
									found = true;
								} else {
									i++;
								}
							}
							printKata(ListWahana[i].Nama);
							while(Next(aLL) != Nil){
								aLL = Next(aLL);
								found = false;
								i = 0;
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(aLL)){
										found = true;
										printf(" -> ");
										printKata(ListWahana[i].Nama);
									} else {
										i++;
									}
								}
							}
							printf(")\n");
							printf("Durasi wahana: %d menit\n", ListWahana[j].Durasi);	
							scanf("%c", &Dummy);
							system("cls");						
						}
					} else if(isKataSama(kata_Reports, inoffice)){
						// TAMPILKAN LAPORAN
					} else if(isKataSama(kata_Exit, inoffice)) {
						printf("Terima kasih sudah berkunjung ke office hari ini\n");
						sleep(1);
						system("cls");
						break;
					} else {
						printf("Perintah tidak dikenal\n");
						sleep(1);
						system("cls");
					}
				} while(!isKataSama(kata_Exit, inoffice));                
			} else {
				if (SekitaranPemain.D == '-') {
                	DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                	DataPemain.PosisiPemain.X++;
                	DataPemain.SimbolPetak = SekitaranPemain.D;
                	DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                	update();
                	tambahWaktuMainManual(0,1);
            	} else if (SekitaranPemain.D == '>') {
                	DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPetak;
                	DataPemain.PosisiPemain.X = Identitas_Peta.Map_X_Min;
                	pindahPeta(Perintah,DataPemain.KuadranPeta);
                	DataPemain.SimbolPetak = '-';
                	DataPemain.KuadranPeta->Isi[DataPemain.PosisiPemain.Y][DataPemain.PosisiPemain.X] = DataPemain.SimbolPemain;
                	if(DataPemain.Kuadran == 2){
                		DataPemain.Kuadran = 1;
					} else if(DataPemain.Kuadran ==3){
						DataPemain.Kuadran = 4;
					}
					update();
                	tambahWaktuMainManual(0,1);
            	}	
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

			petaKuadran2.Isi[1][1] = '-';
			if(DataPemain.Kuadran == 2){
				if(DataPemain.PosisiPemain.X == 1 && DataPemain.PosisiPemain.Y == 2){
					SekitaranPemain.W = '-';
				} else if(DataPemain.PosisiPemain.Y == 1 && DataPemain.PosisiPemain.X == 2) {
					SekitaranPemain.A = '-';
				} else if(DataPemain.PosisiPemain.X == 1 && DataPemain.PosisiPemain.Y == 1){
					DataPemain.SimbolPetak = '-';
				}
			}

            system("cls");
            printStage();
            printPeta();
            printInventaris();
            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);
            printf("Buka pukul: "); printDalamFormatWaktu(waktuBuka);
            selisih = selisihTerhadapWaktuMain(waktuBuka);
            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
        } else if (isKataSama(kata_main,Perintah) && GameStage.Phase == 0) {
        	if(GameStage.Phase == 0){
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

				// Menaruh antrean di peta kuadran 2
				// Untuk sekarang asumsikan posisinya di pojok kiri atas
				petaKuadran2.Isi[1][1] = 'A';
				if(DataPemain.Kuadran == 2){
					if(DataPemain.PosisiPemain.X == 1 && DataPemain.PosisiPemain.Y == 2){
						SekitaranPemain.W = 'A';
					} else if(DataPemain.PosisiPemain.Y == 1 && DataPemain.PosisiPemain.X == 2) {
						SekitaranPemain.A = 'A';
					} else if(DataPemain.PosisiPemain.X == 1 && DataPemain.PosisiPemain.Y == 1){
						DataPemain.SimbolPetak = '-';
					}
				}

	            system("cls");
	            printStage();
	            printPeta();
	            printInventaris();
	            printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);
	            printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
	            selisih = selisihTerhadapWaktuMain(waktuTutup);
	            printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
			} else {
				printf("Perintah ini hanya bisa dilakukan saat fase preparasi\n");
			}
        } else if (isKataSama(kata_quit,Perintah)) {
            printf("\nNoice\n");
        } else if (isKataSama(kata_build,Perintah)) {
            if (diMainPhase(WaktuMain)) {
				printf("Hanya bisa membangun pada saat preparation phase\n");
            } else if(SekitaranPemain.A == '<' || SekitaranPemain.D == '>' || SekitaranPemain.W == '^' || SekitaranPemain.S == 'V'){
                printf("Tidak bisa membangun di sini\n");
			} else if(diMainPhase(tambahWaktu(WaktuMain, tambahWaktuManualF(durasiExecute, 1, 0)))){
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
						printf("Wahana ini memiliki durasi permainan %d menit, harga tiket wahana adalah %d Lungmen Dollar, dan kapasitas wahana adalah %d orang\n", \
						ListWahana[i].Durasi, ListWahana[i].HargaTiket, ListWahana[i].Kapasitas);

					}
				}
				printf("Masukkan nomor wahana yang ingin dibangun.\n");

                scanf("%d", &IDWahana);
                //Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
                scanf("%c", &dummyChar);

                i = 0;
                boolean found = false;
                while(i < BanyakWahana && !found){
                	if((ListWahana[i].Indeks == IDWahana) && (ListWahana[i].Tipe == 1)){
                		found = true;
                		if((Inventaris.Uang < ListWahana[i].HargaBangun.Uang + HutangUang) || (Inventaris.BahanBangunan1 < ListWahana[i].HargaBangun.BahanBangunan1 + HutangBB1) || (Inventaris.BahanBangunan2 < ListWahana[i].HargaBangun.BahanBangunan2 + HutangBB2) || (Inventaris.BahanBangunan3 < ListWahana[i].HargaBangun.BahanBangunan3 + HutangBB3)){
                			printf("Resource Anda tidak mencukupi");
						} else {
		                	int tupelBuild[10];
		                	tupelBuild[0] = 1;
		                	tupelBuild[1] = ListWahana[i].Indeks;
		                	tupelBuild[2] = -1*ListWahana[i].HargaBangun.Uang;
							tupelBuild[3] = -1*ListWahana[i].HargaBangun.BahanBangunan1;
							tupelBuild[4] = -1*ListWahana[i].HargaBangun.BahanBangunan2;
							tupelBuild[5] = -1*ListWahana[i].HargaBangun.BahanBangunan3;
							tupelBuild[6] = 0;
							tupelBuild[7] = DataPemain.PosisiPemain.Y;
							tupelBuild[8] = DataPemain.PosisiPemain.X;
							tupelBuild[9] = DataPemain.Kuadran;
							HutangUang -= tupelBuild[2];
							HutangBB1 -= tupelBuild[3];
							HutangBB2 -= tupelBuild[4];
							HutangBB3 -= tupelBuild[5];
		                	Push(&DaftarPerintah, tupelBuild);
							printf("Perintah untuk membangun sudah dimasukkan ke stack perintah. Pemain diharapkan segera bergerak dari area pembangunan. Terima kasih.\n");
		                	tambahWaktuManualP(durasiExecute, 1, 0);
						}
					}
					i++;
				}
				if(!found){
					printf("Wahana yang Anda pilih bukan merupakan wahana dasar\n");
				}
            }
        } else if(isKataSama(kata_upgrade, Perintah)){
        	boolean wahanaSekitar[4];
        	wahanaSekitar[0] = (SekitaranPemain.A == 'W');
        	wahanaSekitar[1] = (SekitaranPemain.W == 'W');
        	wahanaSekitar[2] = (SekitaranPemain.S == 'W');
        	wahanaSekitar[3] = (SekitaranPemain.D == 'W');
			if(diMainPhase(WaktuMain)){
				printf("Hanya bisa upgrade saat fase preparasi\n");
			} else if(!(wahanaSekitar[0] || wahanaSekitar[1] || wahanaSekitar[2] || wahanaSekitar[3])){
				printf("Tidak ada wahana yang dapat diupgrade di sekitar sini\n");
			} else if(diMainPhase(tambahWaktu(WaktuMain, tambahWaktuManualF(durasiExecute, 1, 30)))){
				printf("Waktu eksekusi tidak akan mencukupi\n");
			} else {
				char input;
				int i;
				int idA, idS, idW, idD;
				Poin PosisiWahana;
				printf("Pilihlah wahana yang ingin diupgrade\n");
				for(i = 0; i < 4; i++){
					if(wahanaSekitar[i]){
						switch(i){
							case 0:
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X - 1 && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
										idA = ListWahanaDibangun[j].Indeks;
										printf("(A) %d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\n");
									}
								}
								break;
							case 1:
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y - 1 && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
										idW = ListWahanaDibangun[j].Indeks;
										printf("(W) %d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\n");
									}
								}
								break;
							case 2:
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y + 1 && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
										idS = ListWahanaDibangun[j].Indeks;
										printf("(S) %d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\n");
									}
								}
								break;
							case 3:
								for(j = 0; j < BanyakWahanaDibangun; j++){
									if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X + 1 && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
										idD = ListWahanaDibangun[j].Indeks;
										printf("(D) %d. ", ListWahanaDibangun[j].Indeks);
										printKata(ListWahanaDibangun[j].Nama);
										printf("\n");
									}
								}
								break;
						}
					}


				}
				int idx;
				boolean found = false;
				LinkedList LL;
				addressNode adN;
				addressNode adN1;
				addressLL adLL;
				scanf("%c", &input);
                //Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
                scanf("%c", &dummyChar);
				switch(input){
					case 'A':
						if(!wahanaSekitar[0]){
							printf("Wahana di lokasi ini tidak ada\n");
						} else {
							PosisiWahana.X = DataPemain.PosisiPemain.Y ;
							PosisiWahana.Y = DataPemain.PosisiPemain.X - 1;
							adN = SearchWahanaDenganIndeks(TreeUpgrade, idA);
							LL = KemungkinanUpgrade(adN);
							adLL = First(LL);
							while(adLL != Nil){
								i = 0;
								found = false;
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(adLL)){
										found = true;
										printf("%d. ", ListWahana[i].Indeks);
										printKata(ListWahana[i].Nama);
										printf("\nMembangunnya akan membutuhkan %d Lungmen Dollar, %d D32 Steel, %d Bipolar Nanoflake, dan %d Polymerization Preparation\n", \
										ListWahana[i].HargaBangun.Uang, ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2, ListWahana[i].HargaBangun.BahanBangunan3);
										printf("Membangunnya akan mengubah durasi wahana menjadi %d menit, harga tiket menjadi %d Lungmen Dollar, dan kapasitas menjadi %d orang\n", \
										ListWahana[i].Durasi, ListWahana[i].HargaTiket, ListWahana[i].Kapasitas);
									} else {
										i++;
									}
								}
								adLL = Next(adLL);
							}
							scanf("%d", &idx);
							//Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	                        scanf("%c", &dummyChar);
							found = false;
							DealokasiLL(&adLL);
							adLL = First(LL);
							while(!found && adLL != Nil){
								if(InfoIdx(adLL) == idx){
									found = true;
								} else {
									adLL = Next(adLL);
								}
							}
							if(!found){
								printf("Anda memasukkan indeks yang salah\n");
							} else {
								adN1 = SearchWahanaDenganIndeks(TreeUpgrade, idx);
								int tupelUpgrade[9];
								tupelUpgrade[0] = 2;
								tupelUpgrade[1] = idA;
								tupelUpgrade[2] = -1*InfoWahana(adN1)[1];
								tupelUpgrade[3] = -1*InfoWahana(adN1)[2];
								tupelUpgrade[4] = -1*InfoWahana(adN1)[3];
								tupelUpgrade[5] = -1*InfoWahana(adN1)[4];
								tupelUpgrade[6] = idx;
								tupelUpgrade[7] = PosisiWahana.X;
								tupelUpgrade[8] = PosisiWahana.Y;
								tupelUpgrade[9] = DataPemain.Kuadran;
								Push(&DaftarPerintah, tupelUpgrade);
								HutangUang -= tupelUpgrade[2];
								HutangBB1 -= tupelUpgrade[3];
								HutangBB2 -= tupelUpgrade[4];
								HutangBB3 -= tupelUpgrade[5];
			                	tambahWaktuManualP(durasiExecute, 1, 30);
							}
						}
						break;
					case 'W':
						if(!wahanaSekitar[1]){
							printf("Tidak ada wahana di lokasi ini\n");
						} else {
							PosisiWahana.X = DataPemain.PosisiPemain.Y - 1;
							PosisiWahana.Y = DataPemain.PosisiPemain.X;
							adN = SearchWahanaDenganIndeks(TreeUpgrade, idW);
							LL = KemungkinanUpgrade(adN);
							adLL = First(LL);
							while(adLL != Nil){
								i = 0;
								found = false;
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(adLL)){
										found = true;
										printf("%d. ", ListWahana[i].Indeks);
										printKata(ListWahana[i].Nama);
										printf("\nMembangunnya akan membutuhkan %d Lungmen Dollar, %d D32 Steel, %d Bipolar Nanoflake, dan %d Polymerization Preparation\n", \
										ListWahana[i].HargaBangun.Uang, ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2, ListWahana[i].HargaBangun.BahanBangunan3);
										printf("Membangunnya akan mengubah durasi wahana menjadi %d menit, harga tiket menjadi %d Lungmen Dollar, dan kapasitas menjadi %d orang\n", \
										ListWahana[i].Durasi, ListWahana[i].HargaTiket, ListWahana[i].Kapasitas);
									} else {
										i++;
									}
								}
								adLL = Next(adLL);
							}
							scanf("%d", &idx);
							//Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	                        scanf("%c", &dummyChar);
							found = false;
							DealokasiLL(&adLL);
							adLL = First(LL);
							while(!found && adLL != Nil){
								if(InfoIdx(adLL) == idx){
									found = true;
								} else {
									adLL = Next(adLL);
								}
							}
							if(!found){
								printf("Anda memasukkan indeks yang salah\n");
							} else {
								adN1 = SearchWahanaDenganIndeks(TreeUpgrade, idx);
								int tupelUpgrade[9];
								tupelUpgrade[0] = 2;
								tupelUpgrade[1] = idA;
								tupelUpgrade[2] = -1*InfoWahana(adN1)[1];
								tupelUpgrade[3] = -1*InfoWahana(adN1)[2];
								tupelUpgrade[4] = -1*InfoWahana(adN1)[3];
								tupelUpgrade[5] = -1*InfoWahana(adN1)[4];
								tupelUpgrade[6] = idx;
								tupelUpgrade[7] = PosisiWahana.X;
								tupelUpgrade[8] = PosisiWahana.Y;
								tupelUpgrade[9] = DataPemain.Kuadran;
								Push(&DaftarPerintah, tupelUpgrade);
								HutangUang -= tupelUpgrade[2];
								HutangBB1 -= tupelUpgrade[3];
								HutangBB2 -= tupelUpgrade[4];
								HutangBB3 -= tupelUpgrade[5];
			                	tambahWaktuManualP(durasiExecute, 1, 30);
							}
						}
						break;
					case 'S':
						if(!wahanaSekitar[2]){
							printf("Tidak ada wahana di lokasi ini\n");
						} else {
							PosisiWahana.X = DataPemain.PosisiPemain.Y + 1;
							PosisiWahana.Y = DataPemain.PosisiPemain.X;
							adN = SearchWahanaDenganIndeks(TreeUpgrade, idS);
							LL = KemungkinanUpgrade(adN);
							adLL = First(LL);
							while(adLL != Nil){
								i = 0;
								found = false;
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(adLL)){
										found = true;
										printf("%d. ", ListWahana[i].Indeks);
										printKata(ListWahana[i].Nama);
										printf("\nMembangunnya akan membutuhkan %d Lungmen Dollar, %d D32 Steel, %d Bipolar Nanoflake, dan %d Polymerization Preparation\n", \
										ListWahana[i].HargaBangun.Uang, ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2, ListWahana[i].HargaBangun.BahanBangunan3);
										printf("Membangunnya akan mengubah durasi wahana menjadi %d menit, harga tiket menjadi %d Lungmen Dollar, dan kapasitas menjadi %d orang\n", \
										ListWahana[i].Durasi, ListWahana[i].HargaTiket, ListWahana[i].Kapasitas);
									} else {
										i++;
									}
								}
								adLL = Next(adLL);
							}
							scanf("%d", &idx);
							//Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	                        scanf("%c", &dummyChar);
							found = false;
							DealokasiLL(&adLL);
							adLL = First(LL);
							while(!found && adLL != Nil){
								if(InfoIdx(adLL) == idx){
									found = true;
								} else {
									adLL = Next(adLL);
								}
							}
							if(!found){
								printf("Anda memasukkan indeks yang salah\n");
							} else {
								adN1 = SearchWahanaDenganIndeks(TreeUpgrade, idx);
								int tupelUpgrade[9];
								tupelUpgrade[0] = 2;
								tupelUpgrade[1] = idA;
								tupelUpgrade[2] = -1*InfoWahana(adN1)[1];
								tupelUpgrade[3] = -1*InfoWahana(adN1)[2];
								tupelUpgrade[4] = -1*InfoWahana(adN1)[3];
								tupelUpgrade[5] = -1*InfoWahana(adN1)[4];
								tupelUpgrade[6] = idx;
								tupelUpgrade[7] = PosisiWahana.X;
								tupelUpgrade[8] = PosisiWahana.Y;
								tupelUpgrade[9] = DataPemain.Kuadran;
								Push(&DaftarPerintah, tupelUpgrade);
								HutangUang -= tupelUpgrade[2];
								HutangBB1 -= tupelUpgrade[3];
								HutangBB2 -= tupelUpgrade[4];
								HutangBB3 -= tupelUpgrade[5];
			                	tambahWaktuManualP(durasiExecute, 1, 30);
							}
						}
						break;
					case 'D':
						if(!wahanaSekitar[3]){
							printf("Tidak ada wahana di lokasi ini\n");
						} else {
							PosisiWahana.X = DataPemain.PosisiPemain.Y;
							PosisiWahana.Y = DataPemain.PosisiPemain.X + 1;
							adN = SearchWahanaDenganIndeks(TreeUpgrade, idD);
							LL = KemungkinanUpgrade(adN);
							adLL = First(LL);
							while(adLL != Nil){
								i = 0;
								found = false;
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(adLL)){
										found = true;
										printf("%d. ", ListWahana[i].Indeks);
										printKata(ListWahana[i].Nama);
										printf("\nMembangunnya akan membutuhkan %d Lungmen Dollar, %d D32 Steel, %d Bipolar Nanoflake, dan %d Polymerization Preparation\n", \
										ListWahana[i].HargaBangun.Uang, ListWahana[i].HargaBangun.BahanBangunan1, ListWahana[i].HargaBangun.BahanBangunan2, ListWahana[i].HargaBangun.BahanBangunan3);
										printf("Membangunnya akan mengubah durasi wahana menjadi %d menit, harga tiket menjadi %d Lungmen Dollar, dan kapasitas menjadi %d orang\n", \
										ListWahana[i].Durasi, ListWahana[i].HargaTiket, ListWahana[i].Kapasitas);
									} else {
										i++;
									}
								}
								adLL = Next(adLL);
							}
							scanf("%d", &idx);
							//Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	                        scanf("%c", &dummyChar);
							found = false;
							DealokasiLL(&adLL);
							adLL = First(LL);
							while(!found && adLL != Nil){
								if(InfoIdx(adLL) == idx){
									found = true;
								} else {
									adLL = Next(adLL);
								}
							}
							if(!found){
								printf("Anda memasukkan indeks yang salah\n");
							} else {
								adN1 = SearchWahanaDenganIndeks(TreeUpgrade, idx);
								int tupelUpgrade[9];
								tupelUpgrade[0] = 2;
								tupelUpgrade[1] = idA;
								tupelUpgrade[2] = -1*InfoWahana(adN1)[1];
								tupelUpgrade[3] = -1*InfoWahana(adN1)[2];
								tupelUpgrade[4] = -1*InfoWahana(adN1)[3];
								tupelUpgrade[5] = -1*InfoWahana(adN1)[4];
								tupelUpgrade[6] = idx;
								tupelUpgrade[7] = PosisiWahana.X;
								tupelUpgrade[8] = PosisiWahana.Y;
								tupelUpgrade[9] = DataPemain.Kuadran;
								Push(&DaftarPerintah, tupelUpgrade);
								HutangUang -= tupelUpgrade[2];
								HutangBB1 -= tupelUpgrade[3];
								HutangBB2 -= tupelUpgrade[4];
								HutangBB3 -= tupelUpgrade[5];
			                	tambahWaktuManualP(durasiExecute, 1, 30);
							}
						}
						break;
					default:
						printf("Mohon masukkan dengan benar, Tuan\n");
						break;
				}
			}
		} else if(isKataSama(kata_buy, Perintah)){
			if(diMainPhase(WaktuMain)){
				printf("Hanya bisa membeli barang saat fase preparasi\n");
			} else if(diMainPhase(tambahWaktu(WaktuMain, tambahWaktuManualF(durasiExecute, 0, 20)))){
				printf("Waktu eksekusi tidak mencukupi\n");
			} else {
                PrintMenuBuy(Daftar_Harga_Bahan);

	            char Tipe;
	            int Jumlah;

	            scanf("%d", &Tipe);
	            //Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	            scanf("%c", &dummyChar);
	            while(!((Tipe == 1) || (Tipe == 2) || (Tipe == 3))){
	            	printf("Masukin yang bener\n");
	            	scanf("%d", &Tipe);
	            	//Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	                scanf("%c", &dummyChar);
				}
				printf("Mau beli berapa?");
				scanf("%d", &Jumlah);
				//Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	            scanf("%c", &dummyChar);
				printf("Baik, akan segera diproses\n");
				printf("Jangan lupa untuk melakukan eksekusi\n");
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
				tupelBuy[9] = 0;
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
		        HutangUang -= tupelBuy[2];
		        HutangBB1 -= tupelBuy[3];
		        HutangBB2 -= tupelBuy[4];
		        HutangBB3 -= tupelBuy[5];
	            tambahWaktuManualP(durasiExecute, 0, 20);
			}
		} else if(isKataSama(kata_repair, Perintah)){

		} else if(isKataSama(kata_execute, Perintah)){
			Tupel X;
			if(diMainPhase(WaktuMain)){
				printf("Hanya bisa mengeksekusi perintah saat fase preparasi\n");
			} else if(StackKosong(DaftarPerintah)){
				printf("Tidak ada perintah untuk dieksekusi\n");
			} else {
				int i;
				// Copy Stack Perintah Agar Bisa Dijalankan dari paling Awal
				while(!StackKosong(DaftarPerintah)){
					Pop(&DaftarPerintah, &X);
					Push(&DaftarPerintahExec, X);
				}

				// Eksekusi satu persatu
				while(!StackKosong(DaftarPerintahExec)){
					Pop(&DaftarPerintahExec, &X);
					switch(X[0]){
						case 1: // Build

							Inventaris.Uang += X[2];
							Inventaris.BahanBangunan1 += X[3];
							Inventaris.BahanBangunan2 += X[4];
							Inventaris.BahanBangunan3 += X[5];

							// Tambah Wahana di List WahanaDibangun
							WahanaDibangun NewWahana;

							NewWahana.Indeks = X[1];
							boolean found =false;
							i = 0;
							while(!found){
								if(ListWahana[i].Indeks != X[1]){
									i++;
								} else {
									NewWahana.Nama = ListWahana[i].Nama;
									found = true;
								}
							}
							NewWahana.Posisi.X = X[7];
							NewWahana.Posisi.Y = X[8];
							NewWahana.Kuadran = X[9];
							NewWahana.Kerusakan = 0;
							LinkedList LL;
							BuatLL(&LL);
							InsVLast(&LL, X[1]);
							NewWahana.Upgrade = LL;

							switch(X[9]){
								case 1:
									petaKuadran1.Isi[X[7]][X[8]] = 'W';
									break;
								case 2:
									petaKuadran2.Isi[X[7]][X[8]] = 'W';
									break;
								case 3:
									petaKuadran3.Isi[X[7]][X[8]] = 'W';
									break;
								case 4:
									petaKuadran4.Isi[X[7]][X[8]] = 'W';
									break;
							}
							if(DataPemain.Kuadran == X[9] && DataPemain.PosisiPemain.Y == X[7] && DataPemain.PosisiPemain.X == X[8]){
								DataPemain.SimbolPetak = 'W';
							} else if(DataPemain.Kuadran == X[9] && DataPemain.PosisiPemain.Y == X[7] + 1 && DataPemain.PosisiPemain.X == X[8]){
								SekitaranPemain.W = 'W';
							} else if(DataPemain.Kuadran == X[9] && DataPemain.PosisiPemain.Y == X[7] - 1 && DataPemain.PosisiPemain.X == X[8]){
								SekitaranPemain.S = 'W';
							} else if(DataPemain.Kuadran == X[9] && DataPemain.PosisiPemain.Y == X[7] && DataPemain.PosisiPemain.X == X[8] - 1){
								SekitaranPemain.D = 'W';
							} else if(DataPemain.Kuadran == X[9] && DataPemain.PosisiPemain.Y == X[7] && DataPemain.PosisiPemain.X == X[8] + 1){
								SekitaranPemain.A = 'W';
							}

							ListWahanaDibangun[BanyakWahanaDibangun] = NewWahana;
							BanyakWahanaDibangun++;

							// Eksekusi Waktu
							tambahWaktuMainManual(1, 0);
							break;
						case 2:
							Inventaris.Uang += X[2];
							Inventaris.BahanBangunan1 += X[3];
							Inventaris.BahanBangunan2 += X[4];
							Inventaris.BahanBangunan3 += X[5];

							WahanaDibangun NewWahanaUp;

							NewWahanaUp.Indeks = X[6];
							found = false;
							i = 0;
							while(!found){
								if(ListWahana[i].Indeks != X[6]){
									i++;
								} else {
									NewWahanaUp.Nama = ListWahana[i].Nama;
									found = true;
								}
							}
							i = 0;
							found = false;
							while(!found){
								if(ListWahanaDibangun[i].Posisi.X == X[7] && ListWahanaDibangun[i].Posisi.Y == X[8]){
									found = true;
								} else {
									i++;
								}
							}
							NewWahanaUp.Posisi.X = X[7];
							NewWahanaUp.Posisi.Y = X[8];
							NewWahanaUp.Kuadran = X[9];
							NewWahanaUp.Kerusakan = 0;

							LinkedList LL1;
							LL1 = ListWahanaDibangun[i].Upgrade;
							InsVLast(&LL1, X[6]);
							NewWahanaUp.Upgrade = LL1;
							ListWahanaDibangun[i] = NewWahanaUp;
							tambahWaktuMainManual(1, 30);
							break;
						case 3: // Buy
							Inventaris.BahanBangunan1 += X[3];
							Inventaris.BahanBangunan2 += X[4];
							Inventaris.BahanBangunan3 += X[5];
							Inventaris.Uang += X[2];

							// Eksekusi Waktu
							tambahWaktuMainManual(0, 20);
							break;
					}
				}
				
				// Reset penghitungan waktu dan resource yang dibutuhkan
				HutangUang = 0;
				HutangBB1 = 0;
				HutangBB2 = 0;
				HutangBB3 = 0;
				setWaktu(&durasiExecute, 0, 0);

				// Skip langsung ke MainPhase
		        setWaktu(&WaktuMain,9,0);
		        GameStage.Phase = 1;

				// idem main
				if(BanyakWahanaDibangun > 0){
					petaKuadran2.Isi[1][1] = 'A';
					if(DataPemain.Kuadran == 2){
						if(DataPemain.PosisiPemain.X == 1 && DataPemain.PosisiPemain.Y == 2){
							SekitaranPemain.W = 'A';
						} else if(DataPemain.PosisiPemain.Y == 1 && DataPemain.PosisiPemain.X == 2) {
							SekitaranPemain.A = 'A';
						} else if(DataPemain.PosisiPemain.X == 1 && DataPemain.PosisiPemain.Y == 1){
							DataPemain.SimbolPetak = '-';
						}
					}

					srand(time(0));
					int r = rand();
					r += r % (BanyakWahanaDibangun + 1);

				}
		        system("cls");
		        printStage();
		        printPeta();
		        printInventaris();
		        printf("Sekarang pukul: "); printDalamFormatWaktu(WaktuMain);
		        printf("Tutup pukul: "); printDalamFormatWaktu(waktuTutup);
		        selisih = selisihTerhadapWaktuMain(waktuTutup);
		        printf("Waktu tersisa: %d jam %d menit\n", selisih.Jam, selisih.Menit);
			}
		} else if(isKataSama(kata_undo, Perintah)){
			Tupel X;
			if(diMainPhase(WaktuMain)){
				printf("Hanya bisa membatalkan perintah pada fase preparasi\n");
			} else if(StackKosong(DaftarPerintah)){
				printf("Anda tidak memiliki perintah yang dapat diundo\n");
			} else {
				Pop(&DaftarPerintah, &X);
				printf("Perintah terakhir Anda sudah dibatalkan\n");
			}
		} else if(isKataSama(kata_office, Perintah)){
			printf("Perintah ini hanya dapat dijalankan melalui office saja\n");
		} else if(isKataSama(kata_serve, Perintah)){

		} else if(isKataSama(kata_repair, Perintah)){

		} else if(isKataSama(kata_detail, Perintah)){
			if(diMainPhase(WaktuMain)){
				boolean wahanaSekitar[4];
        		wahanaSekitar[0] = (SekitaranPemain.A == 'W');
        		wahanaSekitar[1] = (SekitaranPemain.W == 'W');
        		wahanaSekitar[2] = (SekitaranPemain.S == 'W');
        		wahanaSekitar[3] = (SekitaranPemain.D == 'W');
				if(!(wahanaSekitar[0] || wahanaSekitar[1] || wahanaSekitar[2] || wahanaSekitar[3])){
					printf("Tidak ada wahana yang dapat dilihat detailnya di sekitar sini\n");
				} else {
					int idA, idW, idS, idD;
					printf("Pilihlah wahana yang ingin dilihat detailnya\n");
					for(i = 0; i < 4; i++){
						if(wahanaSekitar[i]){
							switch(i){
								case 0:
									for(j = 0; j < BanyakWahanaDibangun; j++){
										if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X - 1 && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
											idA = ListWahanaDibangun[j].Indeks;
											printf("(A) %d. ", ListWahanaDibangun[j].Indeks);
											printKata(ListWahanaDibangun[j].Nama);
											printf("\n");
										}
									}
									break;
								case 1:
									for(j = 0; j < BanyakWahanaDibangun; j++){
										if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y - 1 && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran) {
											idW = ListWahanaDibangun[j].Indeks;
											printf("(W) %d. ", ListWahanaDibangun[j].Indeks);
											printKata(ListWahanaDibangun[j].Nama);
											printf("\n");
										}
									}
									break;
								case 2:
									for(j = 0; j < BanyakWahanaDibangun; j++){
										if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y + 1 && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
											idS = ListWahanaDibangun[j].Indeks;
											printf("(S) %d. ", ListWahanaDibangun[j].Indeks);
											printKata(ListWahanaDibangun[j].Nama);
											printf("\n");
										}
									}
									break;
								case 3:
									for(j = 0; j < BanyakWahanaDibangun; j++){
										if(ListWahanaDibangun[j].Posisi.X == DataPemain.PosisiPemain.Y && ListWahanaDibangun[j].Posisi.Y == DataPemain.PosisiPemain.X + 1 && ListWahanaDibangun[j].Kuadran == DataPemain.Kuadran){
											idD = ListWahanaDibangun[j].Indeks;
											printf("(D) %d. ", ListWahanaDibangun[j].Indeks);
											printKata(ListWahanaDibangun[j].Nama);
											printf("\n");
										}
									}
									break;
							}
						}
					}
					i = 0;
					j = 0;
					Poin PosisiWahana;
					boolean found = false;
					char input;
					scanf("%c", &input);
	                //Untuk Mengambil Input '\n' sehingga tidak terjadi input tidak dikenali
	                scanf("%c", &dummyChar);
	                switch(input){
	                	case 'A':
	                		if(!wahanaSekitar[0]){
	                			printf("Tidak ada wahana di lokasi ini\n");
							} else {
								PosisiWahana.X = DataPemain.PosisiPemain.Y ;
								PosisiWahana.Y = DataPemain.PosisiPemain.X - 1;
								while(!found){
									if(ListWahanaDibangun[i].Posisi.X == PosisiWahana.X && ListWahanaDibangun[i].Posisi.Y == PosisiWahana.Y && ListWahanaDibangun[i].Indeks == idA && ListWahanaDibangun[i].Kuadran == DataPemain.Kuadran){
										found = true;
									} else {
										i++;
									}
								}
								found = false;
								while(!found){
									if(ListWahana[j].Indeks == idA){
										found = true;
									} else {
										j++;
									}
								}
								printf("-------------DETAIL WAHANA-------------\n");
								printf("Nama: ");
								printKata(ListWahanaDibangun[i].Nama);
								printf("\nTipe Wahana: %d\n", ListWahana[j].Tipe);
								printf("Indeks Wahana: %d\n", ListWahana[j].Indeks);
								printf("Harga Tiket Wahana: %d Lungmen Dollar\n", ListWahana[j].HargaTiket);
								printf("Lokasi wahana: (%d, %d) di kuadran %d\n", ListWahanaDibangun[i].Posisi.X, ListWahanaDibangun[i].Posisi.Y, ListWahanaDibangun[i].Kuadran);
								printf("Deskripsi wahana: ");
								printKata(ListWahana[j].Deskripsi);
								printf("\nKapasitas wahana: %d orang\n", ListWahana[j].Kapasitas);
								printf("History Upgrade Wahana:\n");
								PrintLL(ListWahanaDibangun[i].Upgrade);
								addressLL aLL = First(ListWahanaDibangun[i].Upgrade);
								found = false;
								i = 0;
								printf("(");
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(aLL)){
										found = true;
									} else {
										i++;
									}
								}
								printKata(ListWahana[i].Nama);
								while(Next(aLL) != Nil){
									aLL = Next(aLL);
									found = false;
									i = 0;
									while(!found){
										if(ListWahana[i].Indeks == InfoIdx(aLL)){
											found = true;
											printf(" -> ");
											printKata(ListWahana[i].Nama);
										} else {
											i++;
										}
									}
								}
								printf(")\n");
								printf("Durasi wahana: %d menit\n", ListWahana[j].Durasi);
							}
	                		break;
	                	case 'W':
	                		if(!wahanaSekitar[1]){
	                			printf("Tidak ada wahana di lokasi ini\n");
							} else {
								PosisiWahana.X = DataPemain.PosisiPemain.Y - 1;
								PosisiWahana.Y = DataPemain.PosisiPemain.X;
								while(!found){
									if(ListWahanaDibangun[i].Posisi.X == PosisiWahana.X && ListWahanaDibangun[i].Posisi.Y == PosisiWahana.Y && ListWahanaDibangun[i].Indeks == idW && ListWahanaDibangun[i].Kuadran == DataPemain.Kuadran){
										found = true;
									} else {
										i++;
									}
								}
								found = false;
								while(!found){
									if(ListWahana[j].Indeks == idW){
										found = true;
									} else {
										j++;
									}
								}
								printf("-------------DETAIL WAHANA-------------\n");
								printf("Nama: ");
								printKata(ListWahanaDibangun[i].Nama);
								printf("\nTipe Wahana: %d\n", ListWahana[j].Tipe);
								printf("Indeks Wahana: %d\n", ListWahana[j].Indeks);
								printf("Harga Tiket Wahana: %d Lungmen Dollar\n", ListWahana[j].HargaTiket);
								printf("Lokasi wahana: (%d, %d) di kuadran %d\n", ListWahanaDibangun[i].Posisi.X, ListWahanaDibangun[i].Posisi.Y, ListWahanaDibangun[i].Kuadran);
								printf("Deskripsi wahana: ");
								printKata(ListWahana[j].Deskripsi);
								printf("\nKapasitas wahana: %d orang\n", ListWahana[j].Kapasitas);
								printf("History Upgrade Wahana:\n");
								PrintLL(ListWahanaDibangun[i].Upgrade);
								addressLL aLL = First(ListWahanaDibangun[i].Upgrade);
								found = false;
								i = 0;
								printf("(");
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(aLL)){
										found = true;
									} else {
										i++;
									}
								}
								printKata(ListWahana[i].Nama);
								while(Next(aLL) != Nil){
									aLL = Next(aLL);
									found = false;
									i = 0;
									while(!found){
										if(ListWahana[i].Indeks == InfoIdx(aLL)){
											found = true;
											printf(" -> ");
											printKata(ListWahana[i].Nama);
										} else {
											i++;
										}
									}
								}
								printf(")\n");
								printf("Durasi wahana: %d menit\n", ListWahana[j].Durasi);
							}
							break;
						case 'S':
	                		if(!wahanaSekitar[2]){
	                			printf("Tidak ada wahana di lokasi ini\n");
							} else {
								PosisiWahana.X = DataPemain.PosisiPemain.Y + 1;
								PosisiWahana.Y = DataPemain.PosisiPemain.X;
								while(!found){
									if(ListWahanaDibangun[i].Posisi.X == PosisiWahana.X && ListWahanaDibangun[i].Posisi.Y == PosisiWahana.Y && ListWahanaDibangun[i].Indeks == idS && ListWahanaDibangun[i].Kuadran == DataPemain.Kuadran){
										found = true;
									} else {
										i++;
									}
								}
								found = false;
								while(!found){
									if(ListWahana[j].Indeks == idS){
										found = true;
									} else {
										j++;
									}
								}
								printf("-------------DETAIL WAHANA-------------\n");
								printf("Nama: ");
								printKata(ListWahanaDibangun[i].Nama);
								printf("\nTipe Wahana: %d\n", ListWahana[j].Tipe);
								printf("Indeks Wahana: %d\n", ListWahana[j].Indeks);
								printf("Harga Tiket Wahana: %d Lungmen Dollar\n", ListWahana[j].HargaTiket);
								printf("Lokasi wahana: (%d, %d) di kuadran %d\n", ListWahanaDibangun[i].Posisi.X, ListWahanaDibangun[i].Posisi.Y, ListWahanaDibangun[i].Kuadran);
								printf("Deskripsi wahana: ");
								printKata(ListWahana[j].Deskripsi);
								printf("\nKapasitas wahana: %d orang\n", ListWahana[j].Kapasitas);
								printf("History Upgrade Wahana:\n");
								PrintLL(ListWahanaDibangun[i].Upgrade);
								addressLL aLL = First(ListWahanaDibangun[i].Upgrade);
								found = false;
								i = 0;
								printf("(");
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(aLL)){
										found = true;
									} else {
										i++;
									}
								}
								printKata(ListWahana[i].Nama);
								while(Next(aLL) != Nil){
									aLL = Next(aLL);
									found = false;
									i = 0;
									while(!found){
										if(ListWahana[i].Indeks == InfoIdx(aLL)){
											found = true;
											printf(" -> ");
											printKata(ListWahana[i].Nama);
										} else {
											i++;
										}
									}
								}
								printf(")\n");
								printf("Durasi wahana: %d menit\n", ListWahana[j].Durasi);
							}
							break;
						case 'D':
	                		if(!wahanaSekitar[3]){
	                			printf("Tidak ada wahana di lokasi ini\n");
							} else {
								PosisiWahana.X = DataPemain.PosisiPemain.Y ;
								PosisiWahana.Y = DataPemain.PosisiPemain.X + 1;
								while(!found){
									if(ListWahanaDibangun[i].Posisi.X == PosisiWahana.X && ListWahanaDibangun[i].Posisi.Y == PosisiWahana.Y && ListWahanaDibangun[i].Indeks == idD && ListWahanaDibangun[i].Kuadran == DataPemain.Kuadran){
										found = true;
									} else {
										i++;
									}
								}
								found = false;
								while(!found){
									if(ListWahana[j].Indeks == idD){
										found = true;
									} else {
										j++;
									}
								}
								printf("-------------DETAIL WAHANA-------------\n");
								printf("Nama: ");
								printKata(ListWahanaDibangun[i].Nama);
								printf("\nTipe Wahana: %d\n", ListWahana[j].Tipe);
								printf("Indeks Wahana: %d\n", ListWahana[j].Indeks);
								printf("Harga Tiket Wahana: %d Lungmen Dollar\n", ListWahana[j].HargaTiket);
								printf("Lokasi wahana: (%d, %d) di kuadran %d\n", ListWahanaDibangun[i].Posisi.X, ListWahanaDibangun[i].Posisi.Y, ListWahanaDibangun[i].Kuadran);
								printf("Deskripsi wahana: ");
								printKata(ListWahana[j].Deskripsi);
								printf("\nKapasitas wahana: %d orang\n", ListWahana[j].Kapasitas);
								printf("History Upgrade Wahana:\n");
								PrintLL(ListWahanaDibangun[i].Upgrade);
								addressLL aLL = First(ListWahanaDibangun[i].Upgrade);
								found = false;
								i = 0;
								printf("(");
								while(!found){
									if(ListWahana[i].Indeks == InfoIdx(aLL)){
										found = true;
									} else {
										i++;
									}
								}
								printKata(ListWahana[i].Nama);
								while(Next(aLL) != Nil){
									aLL = Next(aLL);
									found = false;
									i = 0;
									while(!found){
										if(ListWahana[i].Indeks == InfoIdx(aLL)){
											found = true;
											printf(" -> ");
											printKata(ListWahana[i].Nama);
										} else {
											i++;
										}
									}
								}
								printf(")\n");
								printf("Durasi wahana: %d menit\n", ListWahana[j].Durasi);
							}
							break;
						default:
							printf("Masukan Anda salah\n");
							break;
					}
				}
			} else {
				printf("Detail hanya dapat digunakan saat Fase Utama\n");
			}
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
    }
    return 0;
}
