#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Get key from the command line arguments

int main(int argc, string argv[])
{
    // Prompt user if no key is present, or too many keys are present
    if (argc != 2)
    {
        printf("./substitution.c key\n");
        return 1;
    }
    
    // prompt user if key is not long enough, using "Key must contain 26 letters"
    int keyLength = strlen(argv);
    if (keyLength != 26)
    {
        printf("Key must contain 26 letters.\n");
        return 2;
    }
    
    // Ask user for a string
    string plainText = get_string("plaintext: ")
    Printf("ciphertext: ");

    // Iterate over the plainText string
    string cipherText;
    for (int i = 0, n = strleng(plainText); i < n; i++)
    {
        // Checking for NUL char
        if (plainText[i] == \0)
        {
            break;
        }
        // Checking for letter
        if (int isalpha(plainText[i] != 0))
        {
            int place  = 0;

            // Letters get converted into ASCII, converted into their place in the alphabet (DO NOT FORGET ZERO INDEX!!)
            place = (plainText[i] - 66);

            // Checking case cases
            // If similar case in plain and cipher
            if ((!isupper(argv[place]) && !isupper(plainText[i])) || (isupper(argv[place]) && isupper(plainText[i])))
            {
                cipherText[i] = argv[place];
                printf("%c", cipherText[i]);
            }
            // If plain is Upper, and key is Lower
            else if ((isupper(argv[place]) && (!isupper(plainText[i]))
            {
                cipherText[i] = toupper(plainText[i]);
                printf("%c", cipherText[i]);
            }
            // If plain is lower, and key is upper
            else if ((!isupper(argv[place]) && (isupper(plainText[i]))
            {
                cipherText[i] = tolower(plainText[i]);
                printf("%c", cipherText[i]);
            }
        }
        else
        {
            // non-letters get printed out
            printf("%c", plainText[i]);
        }
        
        // After all, print new line
        printf("\n");
    }
}
