#include "ADT_poin.h"
#include <stdio.h>

int main () {
    char arah;
    Poin P;

    P.X = 0;
    P.Y = 0;

    printf("Koord: [ %d , %d ]\n", P.X, P.Y);

    do {
        scanf("%c", &arah);
        if (arah == 'w') {
            P.Y++;
            printf("Koord: [ %d , %d ]\n", P.X, P.Y);
        } else if (arah == 'a') {
            P.X--;
            printf("Koord: [ %d , %d ]\n", P.X, P.Y);
        } else if (arah == 's') {
            P.Y--;
            printf("Koord: [ %d , %d ]\n", P.X, P.Y);
        } else if (arah == 'd') {
            P.X++;
            printf("Koord: [ %d , %d ]\n", P.X, P.Y);
        }
    } while (arah != 'q');

    return 0;
}
