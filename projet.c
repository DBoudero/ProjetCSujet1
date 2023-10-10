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
                *decimalValue = -1; // Sortie en cas d'erreur
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
int decimalToBinary(char str[])
{
    long long decimal = atoll(str);

    if (decimal == 0)
    {
        printf("En binaire : 0\n");
    }

    int binary[64];
    int i = 0;

    if (decimal <= 65535)
    {
        while (decimal > 0)
        {
            binary[i] = decimal % 2;
            decimal = decimal / 2;
            i++;
        }

        printf("En binaire : ");
        for (int j = i - 1; j >= 0; j--)
        {
            printf("%d", binary[j]);
        }
        printf("\n");

        // Retourne la valeur binaire calculée sous forme d'entier
        int binaryValue = 0;
        for (int j = i - 1, k = 0; j >= 0; j--, k++)
        {
            binaryValue += binary[j] * (1 << k);
        }
        return binaryValue;
    }
    else
    {
        printf("Rentrer un decimal sur 16 bits, moins de 65 535\n");
        return -1; // Retourner une valeur d'erreur
    }
}

int main()
{
    int choix = 0;
    printf("|---------------------------------|\n");
    printf("|1 - Convertir Decimal to Binaire |\n");
    printf("|2 - Convertir Binaire to Decimal |\n");
    printf("|---------------------------------|\n");
    scanf("%d", &choix);

    if (choix == 1)
    {
        char decimal_str[20];
        printf("Entrez une valeur décimale : ");
        scanf("%s", decimal_str);
        if (verifChiffres(decimal_str) == 1)
        {
            printf("L'entrée n'est pas un nombre décimal valide.\n");
            return 1; // Quitter avec une erreur
        }
        decimalToBinary(decimal_str);
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
        if (binaryToDecimal(binaire_str, &decimalValue) != 0 ) {
            printf("En décimal : %d\n", decimalValue); // Déplacez cette ligne ici
        }
    }
    
    return 0;
}
