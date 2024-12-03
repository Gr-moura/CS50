#include <cs50.h>
#include <stdio.h>
int main()
{
    double f;
    int n;
    char c;
    int res;

    do
    {
        printf("Troca devida: ");

        res = scanf("%lf", &f);

        if (res == 0)
        {
            while (getchar() != '\n')
                ;
        }

        n = 100 * f;
    } while (n < 0 || res == 0);

    int ans = 0;

    ans += n / 25;
    n %= 25;
    ans += n / 10;
    n %= 10;
    ans += n / 5;
    n %= 5;
    ans += n;

    printf("%d\n", ans);

    return 0;
}
