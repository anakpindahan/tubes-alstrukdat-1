/*Implementasi ADT Waktu*/

#include "boolean.h"
#include "ADT_kata.h"
#include <stdio.h>

/*****************KONSTRUKTOR*********************/
Kata createKata(char string[]){
    Kata kataBaru;

    kataBaru.Length = 0;

    int i = 0;

    kataBaru.TabKata[i] = string[i];
    i++;

    while (string[i] != '\0') {
        kataBaru.TabKata[i] = string[i];
        i++;
    }
    kataBaru.Length = i;
    return kataBaru;
}

Kata readInput() {
    char CC; int i = 0;
    Kata kata;

     do {
        scanf("%c",&CC);
        if (CC != '\n') {
            kata.TabKata[i] = CC;
            i++;
        }
    } while (CC != '\n');

    kata.Length = i;
    return kata;
}

/*****************PENGECEKAN*********************/
boolean isKataSama(Kata kata1, Kata kata2) {
    boolean sama;

    if (kata1.Length != kata2.Length) {
        sama = false;
    } else {
        sama = true;
        int i = 0;
        while (sama && i < kata1.Length) {
            if (kata1.TabKata[i] != kata2.TabKata[i]) {
                sama = false;
            }
            i++;
        }
    }
    return sama;
}

/*****************OUTPUT*************************/
void printKata(Kata kata) {
    int i = 0;
    for (i; i < kata.Length; i++) {
        printf("%c",kata.TabKata[i]);
    }
}


