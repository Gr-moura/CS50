#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);

int main(void)
{
    // Solicitar ao usuário duas palavras
    char *P1 = get_string("Player 1: ");
    char *P2 = get_string("Player 2: ");

    // Calcular os pontos de cada palavra
    int scoreUm = compute_score(P1);
    int scoreDois = compute_score(P2);

    // Imprimir o vencedor
    if (scoreUm == scoreDois)
    {
        printf("Tie!\n");
        return 0;
    }

    if (scoreUm > scoreDois)
    {
        printf("Player 1 wins!");
        return 0;
    }

    printf("Player 2 wins");
}

int compute_score(string word)
{
    int sum = 0;

    // Computa e devolve os pontos de cada palavra
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        word[i] = tolower(word[i]);

        if (word[i] >= 'a' && word[i] <= 'z')
            sum += POINTS[word[i] - 'a'];
    }

    return sum;
}
