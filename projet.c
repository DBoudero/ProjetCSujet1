#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction qui prend en entrée un tableau de char et qui vérifie que le char n'a que des chiffres
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

// Fonction qui prend en entrée un tableau de char et qui vérifie que le char n'a que des 1 et 0
int verifBinaire(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '0' && str[i] != '1')
        {
            printf("Entrée invalide. Veuillez entrer un nombre binaire valide.\n");
            return 1;
        }
    }
    return 0;
}

// Fonction qui prend en entrée deux tableaux de char et qui vérifie si le deuxieme tableau a moins de chiffres que le premier, si c'est le cas
// il renvoit le deuxieme tableau en complétant avec autant 0 qu'il faut pour être au meme nombre de chiffres que le premier
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

// Fonction qui permet de formater les chaines avec "_"
char *format(char binval[]) {
    int len = strlen(binval);
    char *formatted = (char *)malloc(len + 1);

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (binval[i] != '_') {
            formatted[j] = binval[i];
            j++;
        }
    }
    formatted[j] = '\0';

    return formatted;
}


// Fonction qui prend en entrée un tableau de char d'un nombre binaire et une variable int vide, et qui va traduire le nombre binaire et le retourner dans cette variable
int binaryToDecimal(char binaryString[], int *decimalValue)
{
    *decimalValue = 0;
    int i = 0;
    if (strlen(binaryString) <= 16) // On s'assure que la valeur binaire rentrer est de 16 bits maximum
    {
        if (verifBinaire(binaryString) == 0)
        {
            while (binaryString[i] != '\0')
            {
                // Conversion du binaire en décimal en multipliant la valeur décimale actuelle par 2 et en ajoutant la valeur binaire du caractère actuel
                *decimalValue = (*decimalValue) * 2 + (binaryString[i] - '0');
                i++;
            }
        }
        return *decimalValue;
    }
    else
    {
        printf("Rentrer un nombre binaire sur 16 bits\n"); // Si la valeur rentrer est de plus de 16 bits
        return 0;
    }
}

// Fonction qui prend en entrée un tableau de char d'une valeur décimale et qui le retourne sous la forme binaire
char *decimalToBinary(char str[])
{
    // Verification que la valeur rentrer est bien composé de chiffre
    if (verifChiffres(str)==1)
    {
        return "Veuillez rentrer un nombre valide";
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

// Fonction qui prend en entrée deux tableaux de char et qui retourne le resultat de leur addition
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
        if (len1 > len2)
        {
            binary2 = plusGrand(binary1, binary2);
        }
        else
        {
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

// Fonction qui prend en entrée deux tableaux de char et qui retourne le resultat de leur soustraction
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
        if (len1 > len2)
        {
            binary2 = plusGrand(binary1, binary2);
        }
        else
        {
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


// Fonction pour supprimer les underscores d'une chaîne
void supprimerUnderscores(char* chaine) {
    int i, j;
    for (i = 0, j = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] != '_') {
            chaine[j++] = chaine[i];
        }
    }
    chaine[j] = '\0';
}

// Fonction pour multiplier deux nombres binaires
char* multiplierBinaire(const char* binaire1, const char* binaire2) {
    // Supprimer les underscores des entrées
    char binaire1SansUnderscores[19];
    char binaire2SansUnderscores[19];
    
    strncpy(binaire1SansUnderscores, binaire1, sizeof(binaire1SansUnderscores));
    supprimerUnderscores(binaire1SansUnderscores);

    strncpy(binaire2SansUnderscores, binaire2, sizeof(binaire2SansUnderscores));
    supprimerUnderscores(binaire2SansUnderscores);

    int longueur1 = strlen(binaire1SansUnderscores); // Utiliser la version sans underscores
    int longueur2 = strlen(binaire2SansUnderscores);
    int longueurResultat = longueur1 + longueur2;
    char* resultat = (char*)malloc(longueurResultat + 1);
    
    for (int i = 0; i < longueurResultat; i++) {
        resultat[i] = '0';
    }
    resultat[longueurResultat] = '\0';
    
    for (int i = longueur1 - 1; i >= 0; i--) {
        if (binaire1SansUnderscores[i] == '1') {
            int retenue = 0;
            for (int j = longueur2 - 1; j >= 0; j--) {
                int produit = (binaire2SansUnderscores[j] - '0') * (binaire1SansUnderscores[i] - '0') + (resultat[i + j + 1] - '0') + retenue;
                retenue = produit / 2;
                resultat[i + j + 1] = (produit % 2) + '0';
            }
            resultat[i] = retenue + '0';
        }
    }
    
    return resultat;
}

// Fonction pour formater le résultat avec des zéros à gauche et des underscores tous les 4 bits
char* formaterResultat(char* resultat) {
    int debut = 0;
    while (resultat[debut] == '0' && resultat[debut + 1] != '\0') {
        debut++;
    }

    int resultatLength = strlen(&resultat[debut]);

    // Calculer le nombre de zéros à gauche nécessaires pour avoir une longueur de 16 bits
    int zerosToPad = 16 - resultatLength;

    // Créer une nouvelle chaîne avec des zéros ajoutés à gauche
    char resultat16Bits[resultatLength + zerosToPad + 1];  // 16 bits + caractère nul
    memset(resultat16Bits, '0', zerosToPad);
    strcpy(resultat16Bits + zerosToPad, &resultat[debut]);

    // Calculer le nombre d'underscores nécessaires
    int numUnderscores = (16 - 1) / 4;

    // Longueur totale du résultat avec les underscores
    int resultatLengthWithUnderscores = 16 + numUnderscores;

    char resultatAvecUnderscores[resultatLengthWithUnderscores + 1];  // +1 pour le caractère nul
    int i = 0;
    int j = 0;

    // Ajouter les underscores tous les 4 bits
    while (i < resultatLengthWithUnderscores) {
        if ((i % 5) == 4) {
            resultatAvecUnderscores[i] = '_';
        } else {
            resultatAvecUnderscores[i] = resultat16Bits[j];
            j++;
        }
        i++;
    }
    resultatAvecUnderscores[i] = '\0';

    return strdup(resultatAvecUnderscores);
}


// Fonction qui prend en entrée deux tableaux de char et qui retourne le resultat de leur division
char *binaryDivision(char dividend[], char divisor[]) {
    int dividendLength = strlen(dividend);
    int divisorLength = strlen(divisor);

    // tableau avec bonne taille
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
    // Initialiser le quotient
    for (int i = 0; i < 16; i++)
    {
        quotient[i] = '0';
    }
    quotient[16] = '\0';

    char tempDividend[33];  // 16 bits + 16 bits (poids faibles) + 1 pour le caractère nul
    strcpy(tempDividend, dividend);

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
    printf("|6 - Multiplication Binaire       |\n");
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
        char binaire_str[19];
        printf("Entrez une valeur binaire : ");
        scanf("%s", binaire_str);
        // if (verifChiffres(binaire_str) == 1)
        // {
        //     printf("L'entrée n'est pas un nombre binaire valide.\n");
        //     return 1;
        // }
        int decimalValue;
        if (binaryToDecimal(format(binaire_str), &decimalValue) == -1)
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
        char binary_str1[19];
        char binary_str2[19];
        printf("Entrez un premier nombre binaire : ");
        scanf("%s", binary_str1);
        printf("Entrez un deuxième nombre binaire : ");
        scanf("%s", binary_str2);

        char *result = soustractionBinaire(format(binary_str1), format(binary_str2));
        printf("Résultat de la soustraction en binaire : %s\n", result);
    }
    else if (choix == 4)
    {
         char dividend[19];
         char divisor[19];
         printf("Entrez un premier nombre binaire : ");
         scanf("%s", dividend);
         printf("Entrez un deuxième nombre binaire : ");
         scanf("%s", divisor);
         char *res = binaryDivision(format(dividend), format(divisor));
         printf("Résultat de la division : %s\n", res);
    }
    else if (choix == 5)
    {
        char binary1[19];
        char binary2[19];
        printf("Entrez un premier nombre binaire : ");
        scanf("%s", binary1);
        printf("Entrez un deuxième nombre binaire : ");
        scanf("%s", binary2);

        char *result = additionBinaire(format(binary1), format(binary2));
        printf("Résultat de l'addition' : %s\n", result);
    }
    else if (choix == 6)
    {
    char binaire1[19];  // Vous pouvez ajuster la taille si nécessaire
    char binaire2[19];

    printf("Entrez le premier nombre binaire : ");
    scanf("%s", binaire1);

    printf("Entrez le deuxième nombre binaire : ");
    scanf("%s", binaire2);

    char* resultat = multiplierBinaire(binaire1, binaire2);
    char* resultatFormate = formaterResultat(resultat);

    printf("Le résultat de la multiplication est : %s\n", resultatFormate);

    free(resultat);
    free(resultatFormate);

    return 0;
}
}
