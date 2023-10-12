#include <stdio.h>

void multiplicationBinaire(const int binaire1[], const int binaire2[], int resultat[], int *erreur) {
    int taille = 16;
    int retenue = 0;

//multiplication :
    //Parcourir les deux tableaux de binaire
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            //Stocke les resultat dans un tableau partiel
            if (binaire1[i] == 1 && binaire2[j] == 1) {
                resultat[i + j] += 1;

                // Verifie si il y a une retenue 
                if (resultat[i + j] >= 2) {
                    retenue = 1;
                    resultat[i + j] %= 2; // Calcul si le resultat est 1 ou 0
                }
            }
        }
    }

//addition :
    for (int i = 0; i < 16; i++) {

        resultat[i] += retenue;

        if (resultat[i] >= 2) {
            resultat[i] %= 2;
            retenue = 1;

            if (i == 15) {
                *erreur = 1; // Marquer une erreur si le 16e bit est généré
            }

        } else {
            retenue = 0;
        }
    }
}

int main() {
    int binaire1[16] = {1,1,1,1,0};
    int binaire2[16] = {1,1,1};
    int resultat[16] = {};
    int erreur = 0;

    multiplicationBinaire(binaire1, binaire2, resultat, &erreur);

    for (int i = 0; i < 16; i++) {
        printf("%d", resultat[i]);
    }

    if (erreur) {
        printf("\nErreur : Le résultat dépasse 16 bits.\n");
    } else {
        printf("\nAucune erreur détectée.\n");
    }

    return 0;
}