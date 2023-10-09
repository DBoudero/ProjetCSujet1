#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char decimal_str[20]; // Augmentez la taille si nécessaire
    printf("Entrez une valeur décimale : ");
    scanf("%s", decimal_str);

    // Vérification de la validité de l'entrée
    for (int i = 0; i < strlen(decimal_str); i++) {
        if (decimal_str[i] < '0' || decimal_str[i] > '9') {
            printf("L'entrée n'est pas un nombre décimal valide.\n");
            return 1; // Quitte le programme en cas d'entrée invalide
        }
    }

    long long decimal = atoll(decimal_str);

    printf("En binaire : ");
    int binary[64];
    int i = 0;

    if (decimal == 0)
    {
        printf("%s", "0");
    }

    while (decimal > 0)
    {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binary[j]);
    }
    printf("\n");

    return 0;
}