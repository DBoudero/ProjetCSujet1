#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vérification que le char n'a que des chiffres
int verifChiffres(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return 1;
        }
    }
    return 0;
}

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
char *decimalToBinary(char str[])
{
    long long decimal = atoll(str);

    if (decimal == 0)
    {
        return "En binaire : 0";
    }

    if (decimal <= 65535)
    {
        int binary[64];
        int i = 0;

        while (decimal > 0)
        {
            binary[i] = decimal % 2;
            decimal = decimal / 2;
            i++;
        }

        char *binaryStr = (char *)malloc((i + 13) * sizeof(char));
        snprintf(binaryStr, i + 13, "En binaire : ");
        for (int j = i - 1; j >= 0; j--)
        {
            snprintf(binaryStr + i - j + 12, 2, "%d", binary[j]);
        }
        return binaryStr;
    }
    else
    {
        return "Rentrer un decimal sur 16 bits, moins de 65 535";
    }
}

char *soustractionBinaire(char binary1[], char binary2[])
{
    int len1 = strlen(binary1);
    int len2 = strlen(binary2);

    // Si les chaînes binaires sont de longueurs différentes, renvoyer une erreur
    if (len1 != len2)
    {
        if (len1 > len2) {
            int difference = len1 - len2;

            // Allouer de la mémoire pour la nouvelle chaîne binaire
            char *nouveauBinary2 = (char *)malloc((len1 + 1) * sizeof(char));

            // Remplir la partie initiale de la nouvelle chaîne avec des zéros
            for (int i = 0; i < difference; i++) {
                nouveauBinary2[i] = '0';
            }

            // Copier le reste de la chaîne binaire d'origine
            strcpy(nouveauBinary2 + difference, binary2);

            // Affecter le pointeur du nouveau binary2 à binary2
            binary2 = nouveauBinary2;
        }
    }

    // Allouer de la mémoire pour le résultat
    char *result = (char *)malloc((len1 + 1) * sizeof(char));

    int retenue = 0;
    for (int i = len1 - 1; i >= 0; i--)
    {
        int bit1 = binary1[i] - '0';
        int bit2 = binary2[i] - '0';

        // Effectuer la soustraction en prenant en compte la retenue
        int diff = bit1 - bit2 - retenue;
        if (diff < 0)
        {
            diff += 2;
            retenue = 1;
        }
        else
        {
            retenue = 0;
        }

        // Écrire le résultat dans la chaîne de caractères
        result[i] = diff + '0';
    }

    result[len1] = '\0'; // Terminer la chaîne de caractères

    return result;
}

int main()
{
    int choix = 0;
    printf("|---------------------------------|\n");
    printf("|1 - Convertir Decimal to Binaire |\n");
    printf("|2 - Convertir Binaire to Decimal |\n");
    printf("|3 - Soustraction Binaire         |\n");
    printf("|---------------------------------|\n");
    scanf("%d", &choix);

    if (choix == 1)
    {
        char decimal_str[20];
        printf("Entrez un nombre décimal : ");
        scanf("%s", decimal_str);

        char *result = decimalToBinary(decimal_str);
        printf("%s\n", result);
        return 0;
    }
    else if (choix == 2)
    {
        char binaire_str[16];
        printf("Entrez une valeur binaire : ");
        scanf("%s", binaire_str);
        if (verifChiffres(binaire_str) == 1)
        {
            printf("L'entrée n'est pas un nombre binaire valide.\n");
            return 1;
        }
        int decimalValue;
        if (binaryToDecimal(binaire_str, &decimalValue) == -1){
            return 0;
        } else {
            printf("En décimal : %d\n", decimalValue);
        }
    }
    else if (choix == 3)
    {
        char binary_str1[16];
        char binary_str2[16];
        printf("Entrez un premier nombre binaire : ");
        scanf("%s", binary_str1);
        printf("Entrez un deuxième nombre binaire : ");
        scanf("%s", binary_str2);

        // Vérifier que les entrées sont valides
        if (verifChiffres(binary_str1) == 1 || verifChiffres(binary_str2) == 1)
        {
            printf("L'entrée n'est pas un nombre binaire valide.\n");
            return 1;
        }

        char *result = soustractionBinaire(binary_str1, binary_str2);
        printf("Résultat de la soustraction en binaire : %s\n", result);
    }

    return 0;
}
