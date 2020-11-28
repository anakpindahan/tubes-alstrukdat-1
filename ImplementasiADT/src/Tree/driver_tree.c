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
	adN = SearchWahanaDenganIndeks(T, 4);
	PrintTree(adN, 2);
	adN2 = Predecessor(adN, T);
	PrintTree(adN2, 2);
	return 0;
}
