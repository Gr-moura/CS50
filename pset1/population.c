#include "cs50.h"
#include <stdio.h>

int main()
{
    // TODO: Solicite o valor inicial ao usuário
    int start;
    do
    {
        start = get_int("Start size: ");
    } while (start < 9);

    // TODO: Solicite o valor final ao usuário
    int end;
    do
    {
        end = get_int("End size: ");
    } while (end < start);

    // TODO: Calcule o número de anos até o limite
    int years = 0;
    while (start < end)
    {
        years++;

        int temp = start;
        start += temp / 3;
        start -= temp / 4;
    }

    // TODO: Imprima o número de anos
    printf("Years: %d\n", years);
    return 0;
}
