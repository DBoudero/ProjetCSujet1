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

char *soustraction(const char binaryStr1[], const char binaryStr2[])
{
    int len1 = strlen(binaryStr1);
    int len2 = strlen(binaryStr2);

    // Vérification que les entrées sont de même longueur
    if (len1 != len2)
    {
        return "Les nombres binaires doivent avoir la même longueur pour la soustraction.";
    }

    // Créer un tampon pour le résultat de la soustraction
    char *result = (char *)malloc((len1 + 1) * sizeof(char));
    result[len1] = '\0'; // Terminer la chaîne avec un caractère nul

    int carry = 0; // Retenue initiale
    for (int i = len1 - 1; i >= 0; i--)
    {
        int bit1 = binaryStr1[i] - '0';
        int bit2 = binaryStr2[i] - '0';

        // Effectuer la soustraction avec la retenue
        int diff = bit1 - bit2 - carry;

        // Si le résultat est négatif, ajouter 2 au résultat et définir la retenue
        if (diff < 0)
        {
            diff += 2;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        // Convertir le résultat en caractère '0' ou '1' et le stocker dans le tampon de résultat
        result[i] = diff + '0';
    }

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

        free(result);
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
        if (binaryToDecimal(binaire_str, &decimalValue) != 0)
        {
            printf("En décimal : %d\n", decimalValue); // Déplacez cette ligne ici
        } else { return 0; }
    }

    return 0;
}
