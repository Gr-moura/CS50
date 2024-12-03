#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int checkKey(char *key);
void encypherText(char *plainText, int key);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (checkKey(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    char *plainText = get_string("plaintext: ");

    encypherText(plainText, key);
    printf("ciphertext: %s\n", plainText);

    return 0;
}

void encypherText(char *plainText, int key)
{
    for (int i = 0; plainText[i] != '\0'; i++)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            plainText[i] = (plainText[i] - 'A' + key % 26) % 26 + 'A';
            continue;
        }

        if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            plainText[i] = (plainText[i] - 'a' + key % 26) % 26 + 'a';
            continue;
        }
    }
}

int checkKey(char *key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!(key[i] >= '0' && key[i] <= '9'))
        {
            return 1;
        }
    }

    return 0;
}
