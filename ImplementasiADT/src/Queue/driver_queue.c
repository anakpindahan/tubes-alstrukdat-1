#include "ADT_queue.h"
#include "../Boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	Pengunjung A;
	Prio(A) = 7;
	Sabar(A) = 7;
	Nomor(A) = 1;
	NaikWahanaKei(A, 0) = 4;
	NaikWahanaKei(A, 1) = 1;
	NaikWahanaKei(A, 2) = 0;
	
	Pengunjung B;
	Prio(B) = 9;
	Sabar(B) = 8;
	Nomor(B) = 2;
	NaikWahanaKei(B, 0) = 1;
	NaikWahanaKei(B, 1) = 0;
	NaikWahanaKei(B, 2) = 0;
	
	Pengunjung C;
	Prio(C) = 5;
	Sabar(C) = 4;
	Nomor(C) = 3;
	NaikWahanaKei(C, 0) = 3;
	NaikWahanaKei(C, 1) = 4;
	NaikWahanaKei(C, 2) = 5;
	
	Pengunjung X;
	
	PrioQueue Q;
	BuatQueue(&Q, 6);
	if(QueueKosong(Q)){
		printf("BENAR, Q memang kosong\n");
	} else {
		printf("SALAH, Q harusnya kosong\n");
	}
	EnqueuePengunjung(&Q, A);
	if(BanyakAnggotaQueue(Q) == 1){
		printf("BENAR, Q memang memiliki satu anggota\n");
	} else {
		printf("SALAH, Q harusnya memiliki satu anggota\n");
	}
	EnqueuePengunjung(&Q, B);
	EnqueuePengunjung(&Q, C);
	PrintPrioQueue(Q);
	DequeuePengunjung(&Q, &X);
	PrintPrioQueue(Q);
	return 0;
}
