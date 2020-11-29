#include "array.c"

int main () {
    //Uji baca dan print menu buy
    BacaBahan_dari_File("materials.txt"); // --> Baca file

    PrintMenuBuy(Daftar_Harga_Bahan); // --> Print dalam format perintah buy

    return 0;
}
