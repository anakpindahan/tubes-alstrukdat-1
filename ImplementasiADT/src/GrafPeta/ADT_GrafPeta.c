#include <stdlib.h>
#include "ADT_GrafPeta.h"

adrGrafNode GrafAlokNode (Peta* peta) {
    adrGrafNode Pn = (adrGrafNode) malloc (sizeof(GrafNode));

    if (Pn != NULL) {
        Pn->ID = peta;
        Pn->Trail = NULL;
        Pn->Next = NULL;
    }
    return Pn;
}

void GrafDealokNode (adrGrafNode Pn) {
    free(Pn);
}

adrGrafSuccNode GrafAlokSuccNode (adrGrafNode Pn, char orientasi) {
    adrGrafSuccNode Pt = (adrGrafSuccNode) malloc (sizeof(GrafSuccNode));

    if (Pt != NULL) {
        Pt->Succ = Pn;
        Pt->Next = NULL;
        Pt->arah = orientasi;
    }
    return Pt;
}

void GrafDealokSuccNode (adrGrafSuccNode Pt) {
    free(Pt);
}

void GrafInsertNode (Graph G, Peta* peta) {
    adrGrafNode Pn = GrafAlokNode(peta);

    if (Pn != NULL) {
        adrGrafNode Ptemp = G.First;

        while (Ptemp->Next != NULL) {
            Ptemp = Ptemp->Next;
        }
        Ptemp->Next = Pn;
    }
}

void GrafInsertEdge (Graph G, Peta* prec, Peta* succ, char orientasi) {
    adrGrafNode Pnprec = G.First;
    adrGrafNode Pnsucc = G.First;

    while (Pnprec->ID != prec) {
        Pnprec = Pnprec->Next;
    }

    while (Pnsucc->ID != succ) {
        Pnsucc = Pnsucc->Next;
    }

    adrGrafSuccNode Pt = Pnprec->Trail;

    if (Pt == NULL) {
        adrGrafSuccNode Pttemp = GrafAlokSuccNode(Pnsucc,orientasi);

        if (Pttemp != NULL) {
            Pnprec->Trail = Pttemp;
        }
    } else {
        while (Pt->Next != NULL) {
            Pt = Pt->Next;
        }
        adrGrafSuccNode Pttemp = GrafAlokSuccNode(Pnsucc,orientasi);

        if (Pttemp != NULL) {
            Pt->Next = Pttemp;
        }
    }
}

Peta* GrafSearchTarget(Graph G, Peta* peta_asal, char orientasi) {
    adrGrafNode Pn = G.First;

    while (Pn->ID != peta_asal) {
        Pn = Pn->Next;
    }

    adrGrafSuccNode Pt = Pn->Trail;

    while (Pt->arah != orientasi) {
        Pt = Pt->Next;
    }

    adrGrafNode Target = Pt->Succ;

    return Target->ID;
}
