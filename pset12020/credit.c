#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int calcLength(long);

int main(void)
{
    // Card Number variable that will not be changed
    long cardNumber = 0;
    
    // Getting a card number form the user
    do
    {
        cardNumber = get_long("Number: ");
    }
    // Checking for numerical input
    while (cardNumber < 0);
    
    // Creating a card number to work with
    long working = cardNumber;
    
    // Initialising local variables
    int cardNumberLength = 0;
    int checkSum = 0;


    //
    while (working != 0)
    {
        // Local variables initialised here as they need to be cleared after each iteration.
        int currentDigit = 0;
        int oddProduct = 0;
        int oddTens = 0;
        int oddSingles = 0;

        currentDigit = (working % 10);

        cardNumberLength++;
        if (currentDigit % 2 == 0)
        {
            // Adding 'even' placed numbers to Check sum
            checkSum = checkSum + currentDigit;
        }
        else
        {
            // Multiplying 'odd placed' digits by 2, separating the digits nd tens and feeding them to check sum
            oddProduct = currentDigit * 2;
            oddTens = oddProduct / 10;
            oddSingles = oddProduct % 10;

            checkSum = checkSum + oddTens + oddSingles;
        }

        // Checking the check sum ends in a 0.
        if (checkSum % 10 == 0)
        {
            // Visa Uses 13 digit numbers
            if (cardNumberLength == 13)
            {
                int firstDigit = (cardNumber / 1000000000000) % 10;
                // VISA's first digit is always 4
                if (firstDigit == 4)
                {
                    printf("VISA\n");
                }
                printf("INVALID\n");
            }
            // Amex uses 15 digit numbers
            else if (cardNumberLength == 15)
            {
                int firstDigit = ((cardNumber / 100000000000000) % 10);
                // AMEX first digit is 3
                if (firstDigit == 3)
                {
                    // Amex second digit is 4 or 7
                    int secondDigit = ((cardNumber / 10000000000000) % 10);
                    if (secondDigit == 4 || secondDigit == 7)
                    {
                        printf("AMEX\n");
                    }
                    printf("INVALID\n");
                }
                // Visa and Mastercard both use 16 digit numbers
                else if (cardNumberLength == 16)
                {
                    // First Digit of Visa is aleways 4
                    firstDigit = (cardNumber / 1000000000000000) % 10;
                    if (firstDigit == 4)
                    {
                        printf("VISA\n");
                    }
                    // First Digit of Mastercard is always 5
                    else if (firstDigit == 5)
                    {
                        int secondDigit = (cardNumber / 100000000000000) % 10;
                        // Second Digit of Mastercard is either 1, 2, 3, 4 or 5
                        if (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)
                        {
                            printf("MASTERCARD\n");
                        }
                        printf("INVALID\n");
                    }
                    printf("INVALID\n");
                }
            }
        }
    }
}
