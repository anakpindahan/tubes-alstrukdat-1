/* Driver Linked List */
#include "../Boolean/boolean.h"
#include "ADT_linkedlist.h"
#include <stdio.h>

int main() {
    int e1, e2;
    LinkedList LL;
    addressLL LP;

    e1 = 1;
    e2 = 2;

    BuatLL(&LL);
    if (LLKosong(LL)) {
        printf("List struktur berkait terbuat, kosong.\n");
    }

    InsVLast(&LL, &e1);
    PrintLL(LL);

    LP = AlokasiLL(&e2);
    PrintLL(LL);
    
    return 0;
}