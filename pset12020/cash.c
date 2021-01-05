#include <stdio.h>
#include <cs50.h>
#include <math.h>

//If only it was as easy as typing "get cash" over 300 times.
//But no, we have to work for a living. (Attemped humour in case anyone reads this)

int main(void)
{

    //initialising float;
    float c = 0.0;
    //initalising variables
    int i = 0; //Quarters
    int j = 0; //Dimes
    int k = 0; //Nickles
    int l = 0; //Pennies
    int s = 0; //s for Shrapnal (UK slang for change in coins)
    {
        //Prompting for a float and repeating the propt if it exceeds parameters.
        do
        {

            c = get_float("Change Required: ");
        }

        while (c <= 0.0);
    }

    //Converting the change (c) required into amount(a) and rounding
    int a = round(c * 100);

    //calculating number of quarters
    i = a / 25;
    //calculating number of dimes
    j = (a - (i * 25)) / 10;
    //calculating number of nickles
    k = (a - ((i * 25) + (j * 10))) / 5;
    //calculating number of pennies
    l = (a - ((i * 25) + (j * 10) + (k * 5)));
    //totalling numer of coins
    s = i + j + k + l;

    printf("Number of coins: %i\n", s);
}
