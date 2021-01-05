#include <stdio.h>
#include <cs50.h>

// setting up a formula
int get_height(void);


int main(void)
{
    // running script for getting height
    int h = get_height();

// setting up the column numer i
    for (int i = 0; i < h; i++)
    {
        // setting up the row numer j
        for (int j = 0; j < h; j++)
        {
            
            // if row + column is less than Height - 1, print #
            if (i + j < h - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

// formula programming
int get_height(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    // Keeping i betwwen 1 and 8 inclusive
    while (h > 8 || h < 1);
    return h;
}
