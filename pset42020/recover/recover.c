#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

#define BLK_SZ 512
#define F_SIZE 8

bool start(BYTE buff[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // Printing error message if command line argument is missing
        printf("Missing command line argument.\nPlease provide file name **.raw.\n");
        return 1;
    }
    // Opening file in command line
    FILE *card = fopen(argv[1], "r");

    // Checking file is readable
    if (card == NULL)
    {
        fprintf(stderr, "Unable to read file. Please check file format.\n");
        return 1;
    }

    BYTE buff[BLK_SZ];

    // Creating an output file for the image
    FILE *image;

    // tracking the number of JPEG files
    int j_peg = 0;
    // Tracking Variables
    bool found = false;

    while (fread(buff, BLK_SZ, 1, card))
    {
        if (start(buff) == true)
        {
            if (found == false)
            {
                found = true;
            }
            else
            {
                fclose(image);
            }
        
            char filename[F_SIZE];
            
            // Incrementing the file name 000 - 001 - 002 etc.
            sprintf(filename, "%03i.jpg", j_peg);
            
            // Increment in the count of JPEGs for the next itteration of file name
            j_peg++;
            
            image = fopen(filename, "w");
            // Checking if the new file is NULL
            if (image == NULL)
            {
                return 1;
            }
            fwrite(buff, BLK_SZ, 1, image);
        }
        else if (found == true)
        {
            // Writing the full 512 block to the image file
            fwrite(buff, BLK_SZ, 1, image);
        }
        
    }
    fclose(image);
    fclose(card);
}


bool start(BYTE buff[])
{
    if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}
