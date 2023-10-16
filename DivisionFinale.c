#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *binaryDivision(char dividend[], char divisor[]) {
    int dividendLength = strlen(dividend);
    int divisorLength = strlen(divisor);

    // Assurez-vous que les tableaux de caractères ont la bonne longueur
    if (dividendLength != 32) {
        int numZerosToAdd = 32 - dividendLength;
        char *temp = (char *)malloc((32 + 1) * sizeof(char));
        
        for (int i = 0; i < numZerosToAdd; i++) {
            temp[i] = '0';
        }
        strcpy(temp + numZerosToAdd, dividend);
        temp[32] = '\0';
        
        dividend = temp; // Mettre à jour dividend avec la nouvelle valeur
    }

    if (divisorLength != 16) {
        int numZerosToAdd = 16 - divisorLength;
        char *temp = (char *)malloc((16 + 1) * sizeof(char));
        
        for (int i = 0; i < numZerosToAdd; i++) {
            temp[i] = '0';
        }
        strcpy(temp + numZerosToAdd, divisor);
        temp[16] = '\0';
        
        divisor = temp; // Mettre à jour divisor avec la nouvelle valeur
    }

    // Allouer de la mémoire pour le résultat
    char *quotient = (char *)malloc((16 + 1) * sizeof(char));
    // Initialiser le quotient et le reste
    for (int i = 0; i < 16; i++)
    {
        quotient[i] = '0';
    }
    quotient[16] = '\0';

    char tempDividend[33];  // 16 bits + 16 bits (poids faibles) + 1 pour le caractère nul
    strcpy(tempDividend, dividend);
    //printf("%s\n",tempDividend);
    for (int i = 0; i < 16; i++) {
        // Décalage à gauche du Dividende et du Quotient
        for (int j = 0; j < 31; j++) {
            tempDividend[j] = tempDividend[j + 1];
        }
        tempDividend[31] = '0';
        for (int j = 0; j < 16; j++) {
            quotient[j] = quotient[j + 1];
        }
        quotient[15] = '0';
        
        // Comparaison du Dividende (poids forts) et du Diviseur
        int compareResult = strcmp(tempDividend, divisor);

        // Si Dividende >= Diviseur, effectuer la soustraction
        if (compareResult >= 0) {
            quotient[15] = '1';
            for (int j = 0; j < 16; j++) {
                if (tempDividend[j] == divisor[j]) {
                    tempDividend[j] = '0';
                } else {
                    tempDividend[j] = '1';
                }
            }
        }
    }

    // Supprimer les 0 inutiles à gauche
    int firstNonZeroPos = -1;
    for (int i = 0; i < 16; i++) {
        if (quotient[i] == '1') {
            firstNonZeroPos = i;
            break;
        }
    }
    if (firstNonZeroPos == -1) {
        // Le quotient est zéro, renvoyer simplement "0"
        char *result = (char *)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        free(quotient);
        return result;
    }

    int newQuotientLength = 16 - firstNonZeroPos;
    char *newQuotient = (char *)malloc((newQuotientLength + 1) * sizeof(char));

    for (int i = 0; i < newQuotientLength; i++) {
        newQuotient[i] = quotient[firstNonZeroPos + i];
    }
    newQuotient[newQuotientLength] = '\0';

    free(quotient);
    return newQuotient;

}

int main() {
    char dividend[] = "1100";
    char divisor[] = "0110";
    char *res = binaryDivision(dividend, divisor);

    printf("Résultat de la division : %s\n", res);

    return 0;
}
