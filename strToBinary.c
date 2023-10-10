#include <stdio.h>
#include <string.h>

//conversion decimal vers binaire
void decimalToBinary(int nbr, int binaire[17]) {
    int i;
    for (i = 0; i < 16; i++) {
        binaire[i] = nbr % 2;
        nbr /= 2;
    }
}

// conversion inverse 
int binaryToDecimal(const char binaryString[]) {
    int decimalValue = 0;
    int length = strlen(binaryString);

    for (int i = length - 1; i >= 0; i--) {

        if (binaryString[i] != '0' && binaryString[i] != '1') {
            printf("Entrée invalide. Veuillez entrer un nombre binaire valide.\n");
            return -1; // Sortie en cas d'erreur
        }
        decimalValue = decimalValue * 2 + (binaryString[i] - '0');
    }
    return decimalValue;
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

    char binaryInput[17]; // Le +1 pour le caractère nul '\0'
    
    printf("Entrez un nombre binaire : ");
    scanf("%16s", binaryInput); // Lire jusqu'à 16 caractères (nombre binaire) depuis l'entrée

    int decimalResult = binaryToDecimal(binaryInput);

    if (decimalResult != -1) {
        printf("Binary to Decimal: %d\n", decimalResult);
    }

    return 0;
}