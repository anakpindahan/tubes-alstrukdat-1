
#include "../Boolean/boolean.h"
#include "ADT_queue.h"
#include <stdio.h>
#include <stdlib.h>

boolean QueueKosong(PrioQueue Q)
{
	return((Head(Q) == NilQ) && (Tail(Q) == NilQ));
}

boolean QueuePenuh(PrioQueue Q)
{
	return(BanyakAnggotaQueue(Q) == MaxEl(Q));
}

int BanyakAnggotaQueue(PrioQueue Q)
{
	if(QueueKosong(Q)){
		return(0);
	} else {
		return(Tail(Q) - Head(Q) + 1);
	}
}

void BuatQueue(PrioQueue *Q, int Max)
{
	(*Q).P = (Pengunjung *) malloc (sizeof(Pengunjung));
	if((*Q).P != NULL){
		MaxEl(*Q) = Max;
		Head(*Q) = NilQ;
		Tail(*Q) = NilQ;
	} else {
		MaxEl(*Q) = 0;
	}
}

void DealokasiQueue(PrioQueue *Q)
{
	MaxEl(*Q) = 0;
	free((*Q).P);	
}

void EnqueuePengunjung(PrioQueue *Q, Pengunjung X)
{
	addressQ i;
	if(QueueKosong(*Q)){
		Head(*Q) = 0;
		Tail(*Q) = 0;
		Elmt(*Q, 0) = X;
	} else {
		i = Tail(*Q);
		Tail(*Q)++;
		while((i >= Head(*Q)) && (Prio(X) < Prio(Elmt(*Q, i)))){
			Elmt(*Q, i+1) = Elmt(*Q, i);
			i--;
		}
		// i = Head(*Q) atau Prio(X) = Prio(Elmt(*Q, i))
		i++;
		Elmt(*Q, i) = X;
	}	
}

void DequeuePengunjung(PrioQueue *Q, Pengunjung *X)
{
	addressQ i;
	*X = Elmt(*Q, Head(*Q));
	if(BanyakAnggotaQueue(*Q) == 1){
		Head(*Q) = NilQ;
		Tail(*Q) = NilQ;
	} else {
		for(i = Head(*Q) + 1; i <= Tail(*Q); i++){
			Elmt(*Q, i - 1) = Elmt(*Q, i);
		}
		Tail(*Q)--;
	}	
}

void PrintPrioQueue (PrioQueue Q)
{
	addressQ i;
	if(!QueueKosong(Q)){
		for(i = Head(Q); i <= Tail(Q); i++){
			printf("%d %d %d - [%d %d %d]\n", Nomor(Elmt(Q, i)), Prio(Elmt(Q, i)), Sabar(Elmt(Q, i)), NaikWahanaKei(Elmt(Q, i), 0), NaikWahanaKei(Elmt(Q, i), 1), NaikWahanaKei(Elmt(Q, i), 2));
		}
	}
	printf("#\n");	
}

void kesabaran (PrioQueue * Q){
/* I.S. Q terdefinisi
   F.S. Kesabaran seluruh pelanggan berkurang 1.
*/
     Pengunjung X;
     if (!QueueKosong(*Q)){
          int i = Head(*Q);
          while(i <= Tail(*Q)){
               Sabar(Elmt(*Q,i))--;
               i++;
          }
          while (Sabar(InfoHead(*Q)) == 0 && !QueueKosong(*Q)){
               DequeuePengunjung(Q,&X);
          }
     }
}
