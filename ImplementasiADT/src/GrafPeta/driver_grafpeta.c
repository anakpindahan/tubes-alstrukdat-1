#include "../Peta/ADT_Peta.h"
#include "ADT_GrafPeta.h"

int main () {
    Graph graf;

    Peta peta1;
    Peta peta2;

    graf.First = GrafAlokNode(&peta1);
    GrafInsertNode(graf,&peta2);

    GrafInsertEdge(graf,&peta1,&peta2,'w');

    //Terbentuk graf sederhana yaitu:
    //peta1 -> peta2

    //Uji pembentukan Graf secara manual
    printf("&peta1 = %p\n", &peta1);
    printf("geraf.First-> = %p\n", graf.First->ID);

    printf("%s\n\n", &peta1 == graf.First->ID ? "TRUE" : "FALSE");

    //Uji hasil pencarian dengan fungsi GrafSearchTarget
    printf("&peta2 = %p\n", &peta2);
    printf("graf.First->Next->ID = %p\n", graf.First->Next->ID);

    printf("GrafSearchTarget(graf,&petal,'w') = %p\n", GrafSearchTarget(graf,&peta1,'w'));

    printf("%s\n\n", &peta2 == GrafSearchTarget(graf,&peta1,'w') ? "TRUE" : "FALSE");

    //Uji Trail dari Node
    printf("graf.First->Trail->Succ = %p\n", graf.First->Trail->Succ);
    printf("graf.First->Next = %p\n", graf.First->Next);

    printf("%s\n", graf.First->Trail->Succ == graf.First->Next ? "TRUE" : "FALSE");

    return 0;
}
