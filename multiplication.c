#include <stdio.h>
#include <stdlib.h>

char *multiplicationBinaire(const char binaire1[16], const char binaire2[16], int *erreur) {
    int taille = 16;
    int retenue = 0;
    int resultat[32] = {0}; // Utiliser un tableau plus grand pour gérer les retenues potentielles

    // Multiplication
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (binaire1[i] == '1' && binaire2[j] == '1') {
                resultat[i + j] += 1;

                if (resultat[i + j] >= 2) {
                    retenue = 1;
                    resultat[i + j] %= 2;
                }
            }
        }
    }

    // Addition
    for (int i = 0; i < 16; i++) {
        resultat[i] += retenue;

        if (resultat[i] >= 2) {
            resultat[i] %= 2;
            retenue = 1;

            if (i == 15) {
                *erreur = 1;
            }
        } else {
            retenue = 0;
        }
    }

    // Construire la chaîne de caractères résultante
    char *result = (char *)malloc(17); // Alloue 17 caractères pour 16 bits + 1 pour le caractère nul '\0'
    for (int i = 0; i < 16; i++) {
        result[i] = resultat[i] + '0'; // Convertit 0 ou 1 en caractère '0' ou '1'
    }
    result[16] = '\0'; // Caractère nul de fin de chaîne

    return result;
}

int main() {
    char binary1[16] = "1010";
    char binary2[16] = "1";
    int erreur = 0;

    char *result = multiplicationBinaire(binary1, binary2, &erreur);

    printf("Résultat : %s\n", result);

    free(result);

    return 0;
}
