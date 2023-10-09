#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vérification que le char n'a que des chiffres
int verifChiffres(char str[]){
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
    }
    return 0;
}

// Convertisseur 
int * convertToBinary(char str[]){

    long long decimal = atoll(str);

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

    return binary;
}

int main()
{
    char decimal_str[20];
    printf("Entrez une valeur décimale : ");
    scanf("%s", decimal_str);

    if (verifChiffres(decimal_str) == 1){
            printf("L'entrée n'est pas un nombre décimal valide.\n");
    };

    int * tabChar;
    tabChar = convertToBinary(decimal_str);

    printf("En binaire : ");
    for (int j = 64; j >= 0; j--)
    {
        printf("%d", tabChar[j]);
    }
    printf("\n");

    return 0;
}