#include "cs50.h"
#include <stdio.h>

int main()
{
    long long numero = get_long("Número: ");

    int somaDigitosPares2x = 0;
    int somaImpares = 0;
    int doisPrimeiros = 0;

    int tamanho = 0;

    while (numero > 0)
    {
        tamanho++;

        if (tamanho % 2 == 0)
        {
            int testeAtual = 2 * (numero % 10);

            somaDigitosPares2x += testeAtual / 10 + testeAtual % 10;
        }
        else
        {
            somaImpares += numero % 10;
        }

        if (numero < 100 && numero > 9)
        {
            doisPrimeiros = numero;
        }

        numero /= 10;
    }

    bool ehValido = (somaDigitosPares2x + somaImpares) % 10 == 0;

    if (!ehValido)
    {
        printf("INVALID\n");
        return 0;
    }

    if ((doisPrimeiros <= 55 && doisPrimeiros >= 51) && tamanho == 16)
    {
        printf("MASTERCARD\n");
        return 0;
    }

    if ((doisPrimeiros == 37 || doisPrimeiros == 34) && tamanho == 15)
    {
        printf("AMEX\n");
        return 0;
    }

    if ((doisPrimeiros >= 40 && doisPrimeiros <= 49) && (tamanho == 13 || tamanho == 16))
    {
        printf("VISA\n");
        return 0;
    }

    printf("INVALID\n");
}
