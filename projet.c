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

// Verification si tableau dépasse 16 bits
int verifTableau16Bits(int tableau[16])
{
    for (int i = 0; i < 32; i++)
    {
        if (tableau[i] != 0) // Le tableau dépasse 16 bits si le reste n'est pas 0
        {
            //return 1;
        }
        printf("%d",tableau[i]);
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

void addition(int binary1[16], int binary2[16], int result[16])
{
    int retenue = 0;

    for (int i = 0; i < 16; i++)
    {
        int sum = binary1[i] + binary2[i] + retenue;
        result[i] = sum % 2; // Stocke le bit de résultat dans le tableau

        // Calcule la retenue pour la prochaine itération
        retenue = sum / 2;
    }

    //Verif si le resultat est superieur dépasse 16 bits
    if (!verifTableau16Bits(result))
    {
        printf("Résultat trop grand pour 16 bits\n");
        // Sortir de la fonction dès que le dépassement est détecté
    }
}

int main()
{
    int str1[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
    int str2[16] = {1};
    
    int resultat[16] = {};

    addition(str1, str2, resultat);

    printf("Résultat : ");
    for (int j = 0; j < 16; j++)
    {
        printf("%d", resultat[j]);
    }
    printf("\n");

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
        printf("Entrez un nombre décimal : ");
        scanf("%s", decimal_str);

        char **(result) = decimalToBinary(decimal_str);
        printf("%s\n", *(result));

        free(*(result));
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
        }
    }
    */
    return 0;
}
