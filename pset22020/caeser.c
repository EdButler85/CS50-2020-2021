#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Function declaration to check for a valid key
bool chk_key(string q);


int main(int argc, string argv[])
{
    // Checking that there are 2 item in the array, and that the key is valid.
    if (argc != 2 || !chk_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        
        // Kicks the program out if the incorrect command line argument is provided
        return 1;
    }
    
    // Changes the string text into an integer
    int key = atoi(argv[1]);

    string pt = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(pt); i++)
    {
        char p = pt[i];
        if (isalpha(p))
        {
            char K = 'a';
            if (isupper(p))
            {
                // added this argument, as the ASCII for A-Z is not 0 indexed
                K = 'A';
            }
            // Shifts the letters along the Cipher. 
            printf("%c", (((p - K) + key) % 26) + K);
            
        }
        else
        {
            printf("%c", p);
        }
    }
    printf("\n");
}

bool chk_key(string q)
{
    // Checking that each item in the command line argument [1] is a digit. 
    for (int j = 0; j < strlen(q); j++)
        if (!isdigit(q[j]))
        {
            return false;
        }
    return true;
}
