#include "ADT_kata.h"

int main () {
    //Uji ADT dan fungsi
    Kata kata_sesuatu = createKata("sesuatu"); // --> Membuat kata dari string yang sudah ada
    Kata kata1 = readInput(); // --> Membuat kata dari input

    printf("%s\n", isKataSama(kata_sesuatu,kata1) == true ? "TRUE" : "FALSE"); // --> Uji fungsi isKataSama

    return 0;
}
