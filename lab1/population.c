#include <stdio.h>
#include <cs50.h>
#include <math.h> // for floor()

int main(void)
{
    int start_pop = 0;
    int end_pop = 0;
    int years = 0;

    // Prompt user for the starting population size, keeping it as a minimum of 9
    do
    {
        start_pop = get_int("Start Size : ");
    }
    while (start_pop < 9);

    // Prompting user for the final required population, keeping it in parameters
    do
    {
        end_pop = get_int("End Size : ");
    }
    while (end_pop < start_pop);

    // Checking if start and end population figures are the same
    if (start_pop == end_pop)
    {
        printf("Years: %i", years);
        return 0;
    }

    else
    {
        do
        {
            // Rounding down to avoid fractional births and deaths
            int births = floor(start_pop / 3);
            int deaths = floor(start_pop / 4);

            start_pop = start_pop + births - deaths;

            // Incrementing the year counter per loop
            years++;
        }
        // Ending the loop, lest it continue forever
        while (start_pop < end_pop);

        // Returning the result
        printf("Years: %i", years);
    }
