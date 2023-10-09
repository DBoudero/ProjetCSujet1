#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vérification que le char n'a que des chiffres
int verifChiffres(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
    }
    return 0;
}

// Convertisseur 
void convertToBinary(char str[]) {
    long long decimal = atoll(str);

    if (decimal == 0) {
        printf("En binaire : 0\n");
        return;
    }

    int binary[64];
    int i = 0;

    while (decimal > 0) {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }

    printf("En binaire : ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binary[j]);
    }
    printf("\n");
}

int main() {
    char decimal_str[20];
    printf("Entrez une valeur décimale : ");
    scanf("%s", decimal_str);

    if (verifChiffres(decimal_str) == 1) {
        printf("L'entrée n'est pas un nombre décimal valide.\n");
        return 1; // Quitter avec une erreur
    }

    convertToBinary(decimal_str);

    return 0;
}