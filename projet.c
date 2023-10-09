#include <stdio.h>

int main()
{
    long long decimal;
    printf("Entrez une valeur décimale : ");
    scanf("%lld", &decimal);

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