#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <cs50.h>

int countLetters(char *text);
int countSentences(char *text);
int countWords(char *text);

double ColemanLiauIndex(int letters, int sentences, int words);

int main()
{
    string text = get_string("Text: ");

    int letters = countLetters(text);
    int sentences = countSentences(text);
    int words = countWords(text);

    double grade = ColemanLiauIndex(letters, sentences, words);

    if (grade < 0.5)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    if (grade > 16.5)
    {
        printf("Grade 16+\n");
        return 0;
    }

    printf("Grade %d\n", (int)round(grade));
}

int countLetters(char *text)
{
    int ret = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalnum(text[i]))
            ret++;
    }

    return ret;
}

int countSentences(char *text)
{
    int ret = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
            ret++;
    }

    return ret;
}

int countWords(char *text)
{
    int ret = 1;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]))
            ret++;
    }

    return ret;
}

double ColemanLiauIndex(int letters, int sentences, int words)
{
    double avgNumLettersPer100 = (double)letters / words * 100;
    double avgNumSentencesPer100 = (double)sentences / words * 100;

    return 0.0588 * avgNumLettersPer100 - 0.296 * avgNumSentencesPer100 - 15.8;
}
