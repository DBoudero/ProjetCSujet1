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
void binaryToDecimal(char binaryString[], int *decimalValue)
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
                return;
            }
            *decimalValue = (*decimalValue) * 2 + (binaryString[i] - '0');
            i++;
        }
        printf("En décimal : %d\n", *decimalValue); // Déplacez cette ligne ici
    }
    else
    {
        printf("Rentrer un nombre binaire sur 16 bits\n");
    }
}

// Convertisseur decimal to binaire
void convertToBinary(char str[])
{

    long long decimal = atoll(str);

    if (decimal == 0)
    {
        printf("En binaire : 0\n");
        return;
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
    }
    else
    {
        printf("Rentrer un decimal sur 16 bits, moins de 65 535\n");
    }
}

void addition(char binaryString1[16], char binaryString2[16])
{
    int i = 0;
    char result[16];
    int retenue = 0;

    while (binaryString1[i] != '\0' || binaryString2[i] != '\0')
    {

        if (retenue == 0)
        {
            // les deux sont à 1
            if (binaryString1[i] == 1 && binaryString2[i] == 1)
            {
                result[i] = 0;
                retenue = 1;
            }
            //les deux sont à 0
            else if (binaryString1[i] == 0 && binaryString2[i] == 0)
            {
                result[i] = '0';
            }
            else // un est a 1 et l'autre a 0
            {
                result[i] = '1';
            }

        }
        else
        {
            // les deux sont à 1
            if (binaryString1[i] == 1 && binaryString2[i] == 1)
            {
                result[i] = '1';
                retenue = 1;
            }
            //les deux sont à 0
            else if (binaryString1[i] == 0 && binaryString2[i] == 0)
            {
                result[i] = '1';
                retenue = 0;
            }
            else // un est a 1 et l'autre a 0
            {
                result[i] = '0';
                retenue = 1;
            }
        }
        i++;
    }

    printf("Resultat : ");
    for (int j = 0; j <= 16; j++)
    {
        printf("%d", result[j]);
    }
    printf("\n");
}

int main()
{
    char str1[16] = {0, 1, 0, 1, 0, 1, 1, 1}; // 11101010 = 234
    char str2[16] = {1, 1, 0, 0, 1, 0, 0, 1}; // 10010011 = 147
    // Resultat 234 + 147 = 381

    addition(str1, str2);

    /*
    int choix = 0;
    printf(" _________________________________ \n");
    printf("|                                 |\n");
    printf("|1 - Convertir Decimal to Binaire |\n");
    printf("|2 - Convertir Binaire to Decimal |\n");
    printf("|_________________________________|\n");
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
        convertToBinary(decimal_str);
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
        binaryToDecimal(binaire_str, &decimalValue);
    }
    */
    return 0;
}
