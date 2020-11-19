/*IMPLEMENTASI ADT TREE*/

#include "boolean.h"
#include "ADT_tree.h"
#include <stdio.h>
#include <stdlib.h>

#define Nil NULL

/*********PREDIKAT************/
boolean TreeKosong(Tree T)
{
	return(WD(T) == Nil);
}

boolean TreeSatuElemen(Tree T)
{
	if(!TreeKosong(T)){
		return((FUW(WD(T)) == Nil) && (WS(WD(T)) == Nil));
	}
}

boolean MaxUpgrade(address Wahana)
{
	return(FUW(Wahana) == Nil);
}

boolean SatuUpgrade(address Wahana)
{
	return(!MaxUpgrade(Wahana) && (WS(Wahana) == Nil));
}

/********KONSTRUKTOR**********/
void BuatTreeKosong(Tree* T)
{
	WD(*T) = Nil;
}

/**********MANAJEMEN MEMORI***********/
address AlokasiAddress(TupelUp wahana)
{
	int i;
	address P;
	P = (Node*) malloc(sizeof(Node));
	if(P != Nil){
		for(i = 0; i < 6; i++){
			InfoWahana(P)[i] = wahana[i];
		}
		FUW(P) = Nil;
		WS(P) = Nil;
	}
	return(P);
}

void DealokasiAddress(address P)
{
	free(P);
}

/************TRAVERSAL************/
address SearchWahanaDenganIndeks(int idx, address P)
{
	if(P == Nil){
		return Nil;
	} else if(IDWahana(P) == idx){
		return P;
	} else if(SearchWahanaDenganIndeks(idx, FUW(P)) != Nil){
		return(SearchWahanaDenganIndeks(idx, FUW(P)));
	} else {
		return(SearchWahanaDenganIndeks(idx, WS(P)));
	}
}

address Predecessor(address Wahana, Tree T)
{
	return(SearchWahanaDenganIndeks(InfoWahana(Wahana)[5], WD(T)));
}

void TambahUpgrade(address Wahana, address newUpgrade, Tree T)
{
	if(MaxUpgrade(Wahana)){
		FUW(Wahana) = newUpgrade;
	} else if(SatuUpgrade(Wahana)){
		WS(Wahana) = newUpgrade;
	} else {
		address P = WS(Wahana);
		while(WS(P) != Nil){
			P = WS(P);
		}
		WS(P) = newUpgrade;
	}
}
