#include <stdio.h>

void decimalToBinary(int nbr, int binaire[17]) {
    int i;
    for (i = 15; i >= 0; i--) {
        binaire[i] = nbr % 2;
        nbr /= 2;
    }
}

int main() {
    int nbr;
    printf("Entrez le nombre à convertir : ");
    scanf("%d", &nbr);

    int binaire[17];
    decimalToBinary(nbr, binaire);

    printf("Decimal to Binary: ");
    for (int i = 0; i < 16; i++) {
        printf("%d", binaire[i]);
    }
    printf("\n");

    return 0;
}