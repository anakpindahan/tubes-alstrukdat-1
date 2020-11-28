/*ADT KATA*/
#ifndef KATA_H
#define KATA_H

#include "../Boolean/boolean.h"

typedef struct {
    char TabKata[100]; // --> Ukuran default
    int Length;
} Kata;

/*****************KONSTRUKTOR*********************/
Kata createKata(char string[]); // --> Mesin konversi string ke tipe data Kata
/*
    Menerima sebuah string dan dikonversi menjadi tipe data kata
    Proses:
        1. Melakukan looping pembacaan char dari suatu string satu per satu
        2. Char input yang terbaca dimasukkan ke dalam TabKata
        3. Jika bertemu '\0'
            Pembacaan berhenti
            Mengisi Lenght berupa banyaknya char yang terbaca
*/

Kata readInput(); // --> Mesin karkater sederhana
/*
    Membaca char input pengguna satu per satu dan dikonversi menjadi tipe data kata
    Proses:
        1. Melakukan looping pembacaan char input satu per satu
        2. Char input yang terbaca dimasukkan ke dalam TabKata
        3. Jika bertemu '\n'
            Pembacaan berhenti
            Mengisi Length berupa banyaknya char yang terbaca
*/

/*****************PENGECEKAN*********************/
boolean isKataSama(Kata kata1, Kata kata2);
/*
    Membandingkan dua tipe data Kata, mengembalikan true jika keduanya identik, dan false jika tidak
    Proses:
        1. Membandingkan Length dari kedua kata
        2. Jika Length berbeda
            mengembalikan false
        3. Jika Length sama
            cek setiap char dalam TabKata
                Jika ada yang berbeda
                    mengembalikan false
*/

/*****************OUTPUT*************************/
void printKata(Kata kata);

#endif
