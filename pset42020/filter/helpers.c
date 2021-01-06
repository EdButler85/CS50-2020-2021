#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            float total = red + green + blue;

            int average = round(total / 3);


            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Local variables for the RGB Sepia Levels
            int sepRed = 0;
            int sepGreen = 0;
            int sepBlue = 0;

            // Sepia RGB Calculations
            sepRed = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189));
            sepGreen = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168));
            sepBlue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131));

            // Checking Sepia levels do not run over 255
            if (sepRed > 255)
            {
                sepRed = 255;
            }
            if (sepGreen > 255)
            {
                sepGreen = 255;
            }
            if (sepBlue > 255)
            {
                sepBlue = 255;
            }

            // Assigning the correct colour levels
            image[i][j].rgbtRed = sepRed;
            image[i][j].rgbtGreen = sepGreen;
            image[i][j].rgbtBlue = sepBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // | /  |J-1 | J  |J+1 |
    // |_/__|____|____|____|
    // |I-1 |I-1 |I-1 |I-1 |
    // |____|J-1_|J___|J+1_|
    // | I  |I   | IJ |I   |
    // |____|J-1_|____|J+1_|
    // |I+1 |I+1 |I+1 |I+1 |
    // |____|J-1_|J___|J+1_|
    
    // Temporary image file
    RGBTRIPLE temporary[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Local variables to calculate average colour levels
            float pix_count = 0.0;
            float tot_red = 0.0;
            float tot_green = 0.0;
            float tot_blue = 0.0;

            // These used for ease of syntax in qualifying statemtns
            int h = height - 1;
            int w = width - 1;

            // Top left pixel
            // Checking edge cases
            // Correct
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                tot_red = tot_red + temporary[i - 1][j - 1].rgbtRed;
                tot_green = tot_green + temporary[i - 1][j - 1].rgbtGreen;
                tot_blue = tot_blue + temporary[i - 1][j - 1].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Top middle pixel
            // Correct
            if (i - 1 >= 0)
            {
                tot_red = tot_red + temporary[i - 1][j].rgbtRed;
                tot_green = tot_green + temporary[i - 1][j].rgbtGreen;
                tot_blue = tot_blue + temporary[i - 1][j].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Top right pixel
            // Correct
            if (i - 1 >= 0 && j + 1 <= w)
            {
                tot_red = tot_red + temporary[i - 1][j + 1].rgbtRed;
                tot_green = tot_green + temporary[i - 1][j + 1].rgbtGreen;
                tot_blue = tot_blue + temporary[i - 1][j + 1].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Middle left pixel
            // Correct
            if (j - 1 >= 0)
            {
                tot_red = tot_red + temporary[i][j - 1].rgbtRed;
                tot_green = tot_green + temporary[i][j - 1].rgbtGreen;
                tot_blue = tot_blue + temporary[i][j - 1].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Middle pixel
            // Correct
            tot_red = tot_red + temporary[i][j].rgbtRed;
            tot_green = tot_green + temporary[i][j].rgbtGreen;
            tot_blue = tot_blue + temporary[i][j].rgbtBlue;
            pix_count = pix_count + 1;

            // Middle right pixel
            // Correct
            if (j + 1 <= w)
            {
                tot_red = tot_red + temporary[i][j + 1].rgbtRed;
                tot_green = tot_green + temporary[i][j + 1].rgbtGreen;
                tot_blue = tot_blue + temporary[i][j + 1].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Bottom right pixel
            // Correct
            if (i + 1 <= h && j - 1 >= 0)
            {
                tot_red = tot_red + temporary[i + 1][j - 1].rgbtRed;
                tot_green = tot_green + temporary[i + 1][j - 1].rgbtGreen;
                tot_blue = tot_blue + temporary[i + 1][j - 1].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Bottom middle pixel
            // Correct
            if (i + 1 <= h)
            {
                tot_red = tot_red + temporary[i + 1][j].rgbtRed;
                tot_green = tot_green + temporary[i + 1][j].rgbtGreen;
                tot_blue = tot_blue + temporary[i + 1][j].rgbtBlue;
                pix_count = pix_count + 1;
            }

            // Bottom right pixel
            //
            if (i + 1 <= h && j + 1 <= w)
            {
                tot_red = tot_red + temporary[i + 1][j + 1].rgbtRed;
                tot_green = tot_green + temporary[i + 1][j + 1].rgbtGreen;
                tot_blue = tot_blue + temporary[i + 1][j + 1].rgbtBlue;
                pix_count = pix_count + 1;
            }
            // Averaging the colour levels
            float av_red = round(tot_red / pix_count);
            float av_green = round(tot_green / pix_count);
            float av_blue = round(tot_blue / pix_count);

            // Assigning back to central pixel
            image[i][j].rgbtRed = av_red;
            image[i][j].rgbtGreen = av_green;
            image[i][j].rgbtBlue = av_blue;
        }
    }

    return;
}
