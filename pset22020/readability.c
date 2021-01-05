#include <stdio.h>
#include <cs50.h>
#include <math.h> //For Rounding function
#include <ctype.h> //For isalpha and related functions
#include <string.h> //For strlen

//decalring fuctions
string get_text(void);  //getting a string


int main(void)
{
    //string varible declaration, recalling function to get text
    string str = get_text();

    //integer variable declarations
    float c = 0;  //number of characters
    float w = 1;  //number of words
    float s = 0;  //number of sentences

    for (int i = 0; i < strlen(str); i++)
    {
        if
        (isalpha(str[i]))
        {
            c++;
        }
    }

    for (int j = 0; j < strlen(str); j++)
    {
        if
        (isspace(str[j]))
        {
            w++;
        }
    }

    for (int k = 0; k < strlen(str); k++)
    {
        if
        (str[k] == '.' || str[k] == '!' || str[k] == '?')

        {
            s++;
        }
    }

    float L = (c / w) * 100;    //Calculating average number of letters per 100 words.
    float S = (s / w) * 100;    //Calculating average number of sentences per 100 words.
    float CLI = ((0.0588 * L) - (0.296 * S) - 15.8);


    if (round(CLI) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        if (round(CLI) >= 1 && round(CLI) <= 16)
        {
            printf("Grade %.0f\n", round(CLI));
        }
        else
        {
            printf("Grade 16+\n");
        }
    }
}

//Getting the text input
string get_text(void)
{
    //Prompting for a string of text
    string text = get_string("Text: ");
    return text;
}
