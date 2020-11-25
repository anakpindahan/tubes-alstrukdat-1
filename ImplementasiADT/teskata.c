#include <stdio.h>

int main() {
    char CC;
    char Kata[20];

    int i = 0;

    do {
        scanf("%c",&CC);
        if (CC != '\n') {
            Kata[i] = CC;
        }
        i++;
    } while (CC != '\n');

    for (int j = 0; j < i; j++) {
        printf("%c",Kata[j]);
    }

    return 0;
}
