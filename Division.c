#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convertisseur binaire to decimal
int binaryToDecimal(const char binaryString[], int *decimalValue)
{
    *decimalValue = 0;
    int i = 0;
    if (strlen(binaryString) <= 16)
    {
        while (binaryString[i] != '\0')
        {
            if (binaryString[i] != '0' && binaryString[i] != '1')
            {
                printf("Entrée invalide. Veuillez entrer un nombre binaire valide.\n");
                return -1;
            }
            *decimalValue = (*decimalValue) * 2 + (binaryString[i] - '0');
            i++;
        }
        return *decimalValue;
    }
    else
    {
        printf("Rentrer un nombre binaire sur 16 bits\n");
        return 0;
    }
}


// Convertisseur decimal to binaire
char *decimalToBinary(char str[]){
    long long decimal = atoll(str);

    if (decimal == 0){
        return "En binaire : 0";
    }

    if (decimal <= 65535){
        int binary[64];
        int i = 0;

        while (decimal > 0){
            binary[i] = decimal % 2;
            decimal = decimal / 2;
            i++;
        }

        char *binaryStr = (char *)malloc((i + 13) * sizeof(char));
        snprintf(binaryStr, i + 13, "En binaire : ");

        for (int j = i - 1; j >= 0; j--){
            snprintf(binaryStr + i - j + 12, 2, "%d", binary[j]);
        }
        return binaryStr;
    }
    else{
        return "Rentrer un decimal sur 16 bits, moins de 65 535";
    }
}

char *binaryDivision(const char binaryNum1[], const char binaryNum2[]) {
    // Conversion
    int decimalNum1, decimalNum2;
    binaryToDecimal(binaryNum1, &decimalNum1);
    binaryToDecimal(binaryNum2, &decimalNum2);

    // Division
    if (decimalNum2 == 0) {
        return "Division par zéro impossible";
    } else {
        int quotient = decimalNum1 / decimalNum2;

        // On vérifie si le quotient est un nombre à virgule
        if (decimalNum1 % decimalNum2 != 0) {
            return "Résultat non entier, impossible de le représenter en binaire";
        }

        // Convertir le quotient en une chaîne de caractères pour conversion
        char quotientStr[64];
        snprintf(quotientStr, sizeof(quotientStr), "%d", quotient);

        // Convertir le quotient en binaire
        char *resultBinary = decimalToBinary(quotientStr);

        return resultBinary;
    }
}

int main() {
    const char binary1[] = "1100";
    const char binary2[] = "10";

    char *result = binaryDivision(binary1, binary2);
    printf("Résultat de la division : %s\n", result);

    return 0;
}

