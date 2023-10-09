#include <stdio.h>

int main() {
    long long decimal;
    printf("Entrez une valeur décimale : ");
    scanf("%lld", &decimal);

    if (decimal < 0) {
        printf("Veuillez entrer un nombre positif ou nul.\n");
        return 1;
    }

    printf("En binaire : ");
    if (decimal == 0) {
        printf("0\n");
    } else {
        int binary[64];
        int i = 0;

        while (decimal > 0) {
            binary[i] = decimal % 2;
            decimal = decimal / 2;
            i++;
        }

        for (int j = i - 1; j >= 0; j--) {
            printf("%d", binary[j]);
        }
        printf("\n");
    }

    return 0;
}