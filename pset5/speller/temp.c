// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int LETTERS = 26;
const unsigned int SYMBOLS = 28; // empty space + letters + apostrophe

// Hash table
node *table[LETTERS * SYMBOLS * SYMBOLS] = {NULL}; // Initialize hash table to NULL

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashValue = hash(word);

    node *curNode = table[hashValue];
    while (curNode != NULL)
    {
        if (strcasecmp(curNode->word, word) == 0)
        {
            return true;
        }

        curNode = curNode->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Words can be LETTERS, SYMBOLS or SYMBOLS

    int beforeFirstLetter = (toupper(word[0]) - 'A') * SYMBOLS * SYMBOLS;
    int beforeSecondLetter = 0;
    int beforeThirdLetter = 0;

    if (strlen(word) == 1)
        return beforeFirstLetter;

    if (isalpha(word[1]))
        beforeSecondLetter = (1 + toupper(word[1]) - 'A') * LETTERS;

    if (word[1] == '\'') // apostrophe
        beforeSecondLetter = (1 + LETTERS) * SYMBOLS;

    if (strlen(word) == 2)
        return beforeFirstLetter + beforeSecondLetter;

    if (isalpha(word[2]))
        beforeThirdLetter = 1 + toupper(word[2]) - 'A';

    if (word[2] == '\'')
    {
        beforeThirdLetter = 1 + LETTERS;
    }

    return beforeFirstLetter + beforeSecondLetter + beforeThirdLetter;
}

unsigned int words = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    char buffer[LENGTH + 5];

    while (fgets(buffer, sizeof(buffer), file))
    {
        // Remove the newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        char *word = buffer;

        int hashValue = hash(word);
        node *newNode = calloc(1, sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }

        strcpy(newNode->word, word);
        newNode->next = table[hashValue];
        table[hashValue] = newNode;

        words++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < LETTERS * SYMBOLS * SYMBOLS; i++)
    {
        node *curNode = table[i];
        while (curNode != NULL)
        {
            node *tmp = curNode;
            curNode = curNode->next;
            free(tmp);
        }
    }

    return true;
}
