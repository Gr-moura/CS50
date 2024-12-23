#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *a = calloc(1, sizeof(char));

    printf("%d 123", strcmp(a, "\0"));
    free(a);
    return 0;
}