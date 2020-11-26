#define Map_X_Max 9
#define Map_X_Min 1
#define Map_Y_Max 9
#define Map_Y_Min 1
#define Ukuran_Peta 11


typedef struct {
	char Isi[Ukuran_Peta][Ukuran_Peta];
} Peta;

void bacaPeta(char* file_name, Peta* kontainer_peta) {
    char ch; int i,j;
    FILE* filePointer = fopen(file_name, "r");

    if (filePointer == NULL) {
        printf("File tidak ditemukan\n");
    }
    else {
        i = 0;
        for (i; i < Ukuran_Peta; i++) {
            j = 0;
            for (j; j < Ukuran_Peta; j++) {
                ch = fgetc(filePointer);
                kontainer_peta->Isi[i][j] = ch;
            }
            ch = fgetc(filePointer);
        }
    }

    fclose(filePointer);
}
