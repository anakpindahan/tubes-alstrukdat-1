/*Akeyla Pradia Naufal 13519178*/

#include "../Boolean/boolean.h"
#include "ADT_tree.h"
#include "../LinkedList/ADT_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Tree T = Nil;
	TupelUp TU;
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
	for(i = 0; i < 6; i++){
		TU[i] = i;
	}
	TambahUpgrade(7, TU, &T);
	for(i = 0; i < 6; i++){
		TU[i] = 3*i + 5;
	}	
	TambahUpgrade(7, TU, &T);
	PrintTree(T, 2);
	return 0;
}
