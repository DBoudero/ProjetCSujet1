#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction pour supprimer les underscores d'une chaîne
void supprimerUnderscores(char* chaine) {
    int i, j;
    for (i = 0, j = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] != '_') {
            chaine[j++] = chaine[i];
        }
    }
    chaine[j] = '\0';
}

// Fonction pour multiplier deux nombres binaires
char* multiplierBinaire(const char* binaire1, const char* binaire2) {
    // Supprimer les underscores des entrées
    char binaire1SansUnderscores[100];
    char binaire2SansUnderscores[100];
    
    strncpy(binaire1SansUnderscores, binaire1, sizeof(binaire1SansUnderscores));
    supprimerUnderscores(binaire1SansUnderscores);

    strncpy(binaire2SansUnderscores, binaire2, sizeof(binaire2SansUnderscores));
    supprimerUnderscores(binaire2SansUnderscores);

    int longueur1 = strlen(binaire1SansUnderscores); // Utiliser la version sans underscores
    int longueur2 = strlen(binaire2SansUnderscores);
    int longueurResultat = longueur1 + longueur2;
    char* resultat = (char*)malloc(longueurResultat + 1);
    
    for (int i = 0; i < longueurResultat; i++) {
        resultat[i] = '0';
    }
    resultat[longueurResultat] = '\0';
    
    for (int i = longueur1 - 1; i >= 0; i--) {
        if (binaire1SansUnderscores[i] == '1') {
            int retenue = 0;
            for (int j = longueur2 - 1; j >= 0; j--) {
                int produit = (binaire2SansUnderscores[j] - '0') * (binaire1SansUnderscores[i] - '0') + (resultat[i + j + 1] - '0') + retenue;
                retenue = produit / 2;
                resultat[i + j + 1] = (produit % 2) + '0';
            }
            resultat[i] = retenue + '0';
        }
    }
    
    return resultat;
}


int main() {
    char binaire1[100];  // Vous pouvez ajuster la taille si nécessaire
    char binaire2[100];

    printf("Entrez le premier nombre binaire : ");
    scanf("%s", binaire1);

    printf("Entrez le deuxième nombre binaire : ");
    scanf("%s", binaire2);

    char* resultat = multiplierBinaire(binaire1, binaire2);

    // Supprimer les zéros non significatifs
    int debut = 0;
    while (resultat[debut] == '0' && resultat[debut + 1] != '\0') {
        debut++;
    }

    int resultatLength = strlen(&resultat[debut]);

    // Calculer le nombre de zéros à gauche nécessaires pour avoir une longueur de 16 bits
    int zerosToPad = 16 - resultatLength;

    // Créer une nouvelle chaîne avec des zéros ajoutés à gauche
    char resultat16Bits[resultatLength + zerosToPad + 1];  // 16 bits + caractère nul
    memset(resultat16Bits, '0', zerosToPad);
    strcpy(resultat16Bits + zerosToPad, &resultat[debut]);

    // Calculer le nombre d'underscores nécessaires
    int numUnderscores = (16 - 1) / 4;

    // Longueur totale du résultat avec les underscores
    int resultatLengthWithUnderscores = 16 + numUnderscores;

    char resultatAvecUnderscores[resultatLengthWithUnderscores + 1];  // +1 pour le caractère nul
    int i = 0;
    int j = 0;

    // Ajouter les underscores tous les 4 bits
    while (i < resultatLengthWithUnderscores) {
        if ((i % 5) == 4) {
            resultatAvecUnderscores[i] = '_';
        } else {
            resultatAvecUnderscores[i] = resultat16Bits[j];
            j++;
        }
        i++;
    }
    resultatAvecUnderscores[i] = '\0';

    printf("Le résultat de la multiplication sur 16 bits avec des zéros à gauche et des underscores tous les 4 bits est : %s\n", resultatAvecUnderscores);

    free(resultat);

    return 0;
}
