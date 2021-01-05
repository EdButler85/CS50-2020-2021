#include <cs50.h>
#include <stdio.h>

int get_height(void);

int main(void)
{
    int h = get_height();

    int c = 0;

    // Iterating through the number of rows
    for (int r = 0; r < h; r++)
    {
        // Counter keeps a track of the progress of the pyramid
        if (c != h)
        {
            // Iterating down the number of spaces at the top of the pyramid.
            for (int s = (h - 1 - c); s > 0; s--)
            {
                printf(" ");
            }

            // Iterating through the number of hash marks
            for (int has = 0; has <= c; has++)
            {
                printf("#");
            }

            printf("  ");

            for (int has = 0; has <= c; has++)
            {
                printf("#");
            }

            printf("\n");
            c++;
        }
    }
}

int get_height(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    // Keeping h between 1 and 8 inclusive
    while (h < 1 || h > 8);
    return h;
}
