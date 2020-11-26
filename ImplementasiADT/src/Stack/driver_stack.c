/*Akeyla Pradia Naufal 13519178*/

/*Driver untuk Stack*/

#include "../Boolean/boolean.h"
#include "ADT_stack.h"
#include <stdio.h>

int main(){
	/*KAMUS*/
	Stack S;
	Tupel Z;
	int i, X;
	/*ALGORITMA*/
	BuatStack(&S);
	if(StackKosong(S)){
		printf("INI BENAR, Stack S memang kosong\n");
	} else {
		printf("INI SALAH, Stack S harusnya kosong\n");
	}
	printf("Masukkan 9 bilangan yang ingin dimasukkan:");
	for(i = 0; i < 9; i++){
		scanf("%d", &X);
		Z[i] = X;
	}
	Push(&S, Z);
	if(!StackKosong(S)){
		printf("INI BENAR, Stack S memang tidak kosong\n");
	} else {
		printf("INI SALAH, Stack S seharusnya tidak kosong\n");
	}
	
	for(i = 0; i < 9; i++){
		Z[i] = i;
	}
	Push(&S, Z);
	
	for(i = 0; i < 9; i++){
		Z[i] = 2*i;
	}
	Push(&S, Z);
	
	
	if(InfoTop(S)[1] == 2){
		printf("INI BENAR, TOP dari S memuat angka 2 di indeks ke-1 nya\n");
	} else {
		printf("INI SALAH, TOP dari S seharusnya memuat angka 2 di indeks ke-1 nya\n");
	}
	
	Pop(&S, &Z);
	
	if(Z[8] == 16){
		printf("INI BENAR, Tupel yang berhasil dipop dari S memuat angka 16 di indeks ke-8 nya\n");
	} else {
		printf("INI SALAH, Tupel yang berhaisl dipop dari S harusnya memuat angka 16 di indeks ke-8 nya\n");
	}
	
	if(InfoTop(S)[8] == 8){
		printf("INI BENAR, TOP dari S setelah operasi pop memuat angka 8 di indeks ke-8 nya\n");
	} else {
		printf("INI SALAH, TOP dari S setelah operasi pop harusnya memuat angka 8 di indeks ke-8 nya\n");
	}
	
	Pop(&S, &Z);
	Pop(&S, &Z);
	
	if(StackKosong(S)){
		printf("INI BENAR, Stack S memang kosong\n");
	} else {
		printf("INI SALAH, Stack S harusnya kosong\n");
	}
	return 0;
}
