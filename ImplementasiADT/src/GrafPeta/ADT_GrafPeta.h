#ifndef _ADT_GRAFPETA_H
#define _ADT_GRAFPETA_H
#include "ADT_GrafPeta.h"
#include "../Peta/ADT_Peta.h"
// _ADT_GRAFPETA_H

#include <stdlib.h>
#include <stdio.h>
//#define NULL NULL
/*
typedef struct {
    Peta* TargetKuadranPeta;
    Peta* AsalKuadranPeta;
    char InputArah;
} Garis;

typedef struct {
    Garis Edge[8];
} GrafPeta;

GrafPeta GrafUntukPeta;
*/

typedef struct tGrafNode * adrGrafNode;
typedef struct tGrafSuccNode * adrGrafSuccNode;

typedef struct tGrafNode {
	Peta* ID;
	adrGrafSuccNode Trail;
	adrGrafNode Next;
} GrafNode;

typedef struct tGrafSuccNode {
	adrGrafNode Succ;
	char arah;
	adrGrafSuccNode Next;
} GrafSuccNode;

typedef struct {
	adrGrafNode First;
} Graph;

extern Graph GrafPeta;

adrGrafNode GrafAlokNode (Peta* peta);

void GrafDealokNode (adrGrafNode Pn);

adrGrafSuccNode GrafAlokSuccNode (adrGrafNode Pn, char orientasi);

void GrafDealokSuccNode (adrGrafSuccNode Pt);

void GrafInsertNode (Graph G, Peta* peta);

void GrafInsertEdge (Graph G, Peta* prec, Peta* succ, char orientasi);

Peta* GrafSearchTarget(Graph G, Peta* peta_asal, char orientasi);

#endif
