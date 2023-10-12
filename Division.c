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

char *plusGrand(char binary1[], char binary2[])
{
    int len1 = strlen(binary1);
    int len2 = strlen(binary2);
    // Fait en sorte que si la 1er chaine de caractère est > que la 2eme alors on complète la 2eme avec des 0 devant pour que les 2 taille soit égale
    int difference = len1 - len2;                                     // Nombre de bits de différence entre les 2 chaines
    char *nouveauBinary2 = (char *)malloc((len1 + 1) * sizeof(char)); // Allouer de la mémoire pour la nouvelle chaîne binaire
    // Remplir la partie initiale de la nouvelle chaîne avec des zéros
    for (int i = 0; i < difference; i++)
    {
        nouveauBinary2[i] = '0';
    }
    strcpy(nouveauBinary2 + difference, binary2); // Copier le reste de la chaîne binaire d'origine
    binary2 = nouveauBinary2;                     // Affecter le pointeur du nouveau binary2 à binary2
    return binary2;
}

char *soustractionBinaire(char binary1[], char binary2[])
{
    // Sécurité si l'un des deux nombre binaire rentré dépasse 16 bits
    if (strlen(binary1) > 16 || strlen(binary2) > 16)
    {
        return "Entrée invalide. Veuillez entrer un nombre binaire valide.\n";
    }

    // Variable contenant la taille de chacun chaine de caractère binaire
    int len1 = strlen(binary1);
    int len2 = strlen(binary2);

    if (len1 != len2)
    {
        if(len1>len2){
            binary2 = plusGrand(binary1, binary2);
        } else {
            binary1 = plusGrand(binary2, binary1);
        }
    }

    for (int i = 0; i < strlen(binary1); i++)
    {
        if (binary1[i] != '0' && binary1[i] != '1') // On s'assure que la valeur rentrer ne contient que des 1 et des 0
        {
            return "Entrée invalide. Veuillez entrer un nombre binaire valide.\n";
        }
    }
    for (int i = 0; i < strlen(binary2); i++)
    {
        if (binary2[i] != '0' && binary2[i] != '1') // On s'assure que la valeur rentrer ne contient que des 1 et des 0
        {
            return "Entrée invalide. Veuillez entrer un nombre binaire valide.\n";
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

// Division
char *binaryDivision(char binary1[], char binary2[])
{
    // Variable contenant la taille de chaque chaîne de caractères binaires
    int len1 = strlen(binary1);
    int len2 = strlen(binary2);

    // Trouver la position du bit le plus à gauche dans binary2
    int position = 0;
    while (position < len2 && binary2[position] == '0')
    {
        position++;
    }

    // Si binary2 est égal à zéro, la division est indéfinie
    if (position == len2)
    {
        return "Division par zéro.\n";
    }

    // Allouer de la mémoire pour le résultat
    char *quotient = (char *)malloc((len1 + 1) * sizeof(char));
    char *remainder = (char *)malloc((len1 + 1) * sizeof(char));

    // Initialiser le quotient et le reste
    for (int i = 0; i < len1; i++)
    {
        quotient[i] = '0';
        remainder[i] = binary1[i];
    }
    quotient[len1] = '\0';
    remainder[len1] = '\0';

    // Effectuer la division binaire
    for (int i = 0; i < len1; i++)
    {
        // Décaler le reste vers la gauche
        for (int j = len1 - 1; j > 0; j--)
        {
            remainder[j] = remainder[j - 1];
        }
        remainder[0] = binary1[i];

        // Soustraction binaire
        char *temp = soustractionBinaire(remainder, binary2);
        
        if (temp[0] == '0')
        {
            quotient[i] = '1';
            free(remainder);
            remainder = temp;
        }
        else
        {
            quotient[i] = '0';
            free(temp);
        }
    }

    // Libérer la mémoire allouée pour le reste
    free(remainder);

    return quotient;
}


int main()
{
    char binary1[] = "1101"; // Dividende
    char binary2[] = "10";   // Diviseur

    char *result = binaryDivision(binary1, binary2);
    printf("Résultat de la division : %s\n", result);

    return 0;
}











