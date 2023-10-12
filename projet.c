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

// Convertisseur binaire en decimal
int binaryToDecimal(const char binaryString[], int *decimalValue)
{
    *decimalValue = 0;
    int i = 0;
    if (strlen(binaryString) <= 16) // On s'assure que la valeur binaire rentrer est de 16 bits maximum
    {
        while (binaryString[i] != '\0')
        {
            if (binaryString[i] != '0' && binaryString[i] != '1') // On s'assure que la valeur rentrer ne contient que des 1 et des 0
            {
                printf("Entrée invalide. Veuillez entrer un nombre binaire valide.\n");
                return -1;
            }
            // Conversion du binaire en décimal en multipliant la valeur décimale actuelle par 2 et en ajoutant la valeur binaire du caractère actuel
            *decimalValue = (*decimalValue) * 2 + (binaryString[i] - '0');
            i++;
        }
        return *decimalValue;
    }
    else
    {
        printf("Rentrer un nombre binaire sur 16 bits\n"); // Si la valeur rentrer est de plus de 16 bits
        return 0;
    }
}

// Convertisseur decimal to binaire
char *decimalToBinary(char str[])
{
    //Verification que la valeur rentrer est bien composé de chiffre
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return "Veuillez rentrer un nombre valide";
        }
    }

    long long decimal = atoll(str); // convertie la valeur rentrer en nombre décimal de type long long

    // Si le décimal est 0
    if (decimal == 0)
    {
        return "En binaire : 0";
    }

    if (decimal <= 65535) // Verification que la valeur rentrer est inférieur ou égale à 65535 soit 16 bits
    {
        int binary[64];
        int i = 0;

        // Convertie en binaire en effectuant des divisions succéssif par 2
        while (decimal > 0)
        {
            binary[i] = decimal % 2;
            decimal = decimal / 2;
            i++;
        }

        char *binaryStr = (char *)malloc((i + 13) * sizeof(char)); // Alloue de la mémoire pour chaîne de caractères pour stocker représentation binaire.
        snprintf(binaryStr, i + 13, "En binaire : ");              // Prépare l'affichage avec "En binaire :"
        // Ajoute à binaryStr, chaque bit calculé précédemment
        for (int j = i - 1; j >= 0; j--)
        {
            snprintf(binaryStr + i - j + 12, 2, "%d", binary[j]);
        }
        return binaryStr;
    }
    else
    {
        // Si la valeur décimal dépasse 65535, soit 16 bits
        return "Rentrer un decimal sur 16 bits, moins de 65 535";
    }
}

char *additionBinaire(char binary1[16], char binary2[16])
{
    // Création de la retenue (ex 1+1 = 10 donc on doit savoir que le prochain bit aura 1 de plus)
    char retenue = '0';
    // Création du résultat
    char *result = (char *)malloc(17); // Alloue 17 caractères pour 16 bits + 1 pour le caractère nul '\0'

    int len1 = strlen(binary1);
    int len2 = strlen(binary2);
    // Si les chaînes binaires ne sont pas de longueurs différentes
    if (len1 != len2)
    {
        if(len1>len2){
            binary2 = plusGrand(binary1, binary2);
        } else {
            binary1 = plusGrand(binary2, binary1);
        }
    }

    // On lit le bit à l'endroit donc plus on va vers la gauche et plus le bit sera grand
    for (int i = strlen(binary2) - 1; i >= 0; i--)
    {
        char bit = '0';

        // On ajout 1 à la variable bit lorsque un 1 fait partie de l'addition
        if (binary1[i] == '1')
            bit++;
        if (binary2[i] == '1')
            bit++;
        // On prendra aussi en compte la retenue
        if (retenue == '1')
            bit++;

        // Stocke le bit de résultat dans le tableau (si l'addition est 0 ou 2 le bit sera à 0 sinon le bit sera à 1)
        if (bit == '0' || bit == '2')
            result[i] = '0';
        else
            result[i] = '1';

        // Calcule la retenue pour la prochaine addition
        if (bit == '3' || bit == '2')
            retenue = '1';
        else
            retenue = '0';
    }

    return result;
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

char *divisionBinaire(const char binaryNum1[], const char binaryNum2[])
{
    // Conversion
    int decimalNum1, decimalNum2;
    binaryToDecimal(binaryNum1, &decimalNum1);
    binaryToDecimal(binaryNum2, &decimalNum2);

    // Division
    if (decimalNum2 == 0)
    {
        return "Division par zéro impossible";
    }
    else
    {
        int quotient = decimalNum1 / decimalNum2;

        // On vérifie si le quotient est un nombre à virgule
        if (decimalNum1 % decimalNum2 != 0)
        {
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

int main()
{
    // Menu de séléction des options
    int choix = 0;
    printf(" _________________________________ \n");
    printf("|                                 |\n");
    printf("|1 - Convertir Decimal to Binaire |\n");
    printf("|2 - Convertir Binaire to Decimal |\n");
    printf("|3 - Soustraction Binaire         |\n");
    printf("|4 - Division Binaire             |\n");
    printf("|5 - Addition Binaire             |\n");
    printf("|_________________________________|\n");
    scanf("%d", &choix);

    if (choix == 1)
    {
        char decimal_str[16];
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
        if (binaryToDecimal(binaire_str, &decimalValue) == -1)
        {
            return 0;
        }
        else
        {
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

        char *result = soustractionBinaire(binary_str1, binary_str2);
        printf("Résultat de la soustraction en binaire : %s\n", result);
    }
    else if (choix == 4)
    {
        char binary1[16];
        char binary2[16];
        printf("Entrez un premier nombre binaire : ");
        scanf("%s", binary1);
        printf("Entrez un deuxième nombre binaire : ");
        scanf("%s", binary2);

        char *result = divisionBinaire(binary1, binary2);
        printf("Résultat de la division : %s\n", result);
    }
    else if (choix == 5)
    {
        char binary1[16];
        char binary2[16];
        printf("Entrez un premier nombre binaire : ");
        scanf("%s", binary1);
        printf("Entrez un deuxième nombre binaire : ");
        scanf("%s", binary2);

        char *result = additionBinaire(binary1, binary2);
        printf("Résultat de l'addition' : %s\n", result);
    }
    return 0;
}
