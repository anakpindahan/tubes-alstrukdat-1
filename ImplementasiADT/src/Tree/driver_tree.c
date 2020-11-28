/*Akeyla Pradia Naufal 13519178*/

#include "../Boolean/boolean.h"
#include "ADT_tree.h"
#include "../LinkedList/ADT_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Tree T = Nil;
	TupelUp TU;
	addressNode adN, adN2;
	addressNode adN3;
	LinkedList LL;
	int i;
	if(TreeKosong(T)){
		printf("INI BENAR, T memang kosong\n");
	} else {
		printf("INI SALAH, T seharusnya kosong\n");
	}
	for(i = 0; i < 6; i++){
		TU[i] = 7;
	}
	T = BuatTreeF(TU, Nil, Nil);
	for(i = 0; i < 5; i++){
		TU[i] = i;
	}
	TU[5] = 7;
	TambahUpgrade(7, TU, &T);
	for(i = 0; i < 5; i++){
		TU[i] = 3*i + 4;
	}	
	TU[5] = 7;
	TambahUpgrade(7, TU, &T);
	for(i = 0; i < 5; i++){
		TU[i] = 3*i + 5;
	}
	TU[5] = 4;	
	TambahUpgrade(4, TU, &T);
	for(i = 0; i < 5; i++){
		TU[i] = 3*i + 6;
	}	
	TU[5] = 7; 
	TambahUpgrade(7, TU, &T);
	PrintTree(T, 2);
	if(SearchEksistensiIndeks(T, 4)){
		printf("Berhasil, indeks ini memang ada\n");
	} else {
		printf("Gagal, indeks ini harusnya ada\n");
	}
	if(!SearchEksistensiIndeks(T, 11)){
		printf("Berhasil, indeks ini memang tidak ada\n");
	} else {
		printf("Gagal, indeks ini seharusnya tidak ada\n");
	}
	printf("Jika yang di bawah ini berhasil, akan ada tiga elemen: 4, 5, 0\n");
	adN = SearchWahanaDenganIndeks(T, 4);
	PrintTree(adN, 2);
	printf("Jika yang di bawah ini berhasil, akan ada lima elemen: 7, 6, 4, 5, 0\n");
	adN2 = Predecessor(adN, T);
	PrintTree(adN2, 2);
	printf("Jika yang di bawah ini berhasil, akan ada tiga elemen: 0, 4, 6\n");
	LL = KemungkinanUpgrade(T);
	PrintLL(LL);
	printf("Jika yang di bawah ini berhasil, akan ada satu elemen: 5\n");
	LL = KemungkinanUpgrade(SearchWahanaDenganIndeks(T, 4));
	PrintLL(LL);

	Tree TUp = Nil;
	for(i = 0; i < 6; i++){
		TU[i] = 0;
	}	
	TUp = BuatTreeF(TU, Nil, Nil);
	TU[0] = 1;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 0;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 2;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 1;
	TambahUpgrade(TU[5], TU, &TUp);	
	TU[0] = 3;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 1;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 4;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 0;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 5;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 2;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 6;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 3;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 7;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 4;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 8;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 4;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 9;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 4;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 10;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 7;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 11;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 8;
	TambahUpgrade(TU[5], TU, &TUp);
	TU[0] = 12;
	for(i = 1; i < 5; i++){
		TU[i] = 0;
	}
	TU[5] = 9;
	TambahUpgrade(TU[5], TU, &TUp);
	PrintTree(TUp, 2);
	adN = SearchWahanaDenganIndeks(TUp, 3);
	printf("%d", IDWahana(adN));
	return 0;
}
