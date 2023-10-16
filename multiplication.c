#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction pour multiplier deux nombres binaires
char* multiplierBinaire(const char* binaire1, const char* binaire2) {
    int longueur1 = strlen(binaire1);
    int longueur2 = strlen(binaire2);
    int longueurResultat = longueur1 + longueur2;
    char* resultat = (char*)malloc(longueurResultat + 1);
    
    for (int i = 0; i < longueurResultat; i++) {
        resultat[i] = '0';
    }
    resultat[longueurResultat] = '\0';
    
    for (int i = longueur1 - 1; i >= 0; i--) {
        if (binaire1[i] == '1') {
            int retenue = 0;
            for (int j = longueur2 - 1; j >= 0; j--) {
                int produit = (binaire2[j] - '0') * (binaire1[i] - '0') + (resultat[i + j + 1] - '0') + retenue;
                retenue = produit / 2;
                resultat[i + j + 1] = (produit % 2) + '0';
            }
            resultat[i] = retenue + '0';
        }
    }
    
    return resultat;
}

int main() {
    const char* binaire1 = "1010";
    const char* binaire2 = "101";

    char* resultat = multiplierBinaire(binaire1, binaire2);

    // Supprimer les zéros non significatifs
    int debut = 0;
    while (resultat[debut] == '0' && resultat[debut + 1] != '\0') {
        debut++;
    }

    printf("Le résultat de la multiplication est : %s\n", &resultat[debut]);

    free(resultat);

    return 0;
}
