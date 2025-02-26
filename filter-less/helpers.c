#include "helpers.h"
#include <math.h>

int capped(int value);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // get the average value of the each pxl
            float avg =
                (image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue) /
                3.0;

            image[row][col].rgbtRed = round(avg);
            image[row][col].rgbtGreen = round(avg);
            image[row][col].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // get the value of the RGB
            int originalRed = image[row][col].rgbtRed;
            int originalGreen = image[row][col].rgbtGreen;
            int originalBlue = image[row][col].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // set value
            image[row][col].rgbtRed = capped(sepiaRed);
            image[row][col].rgbtGreen = capped(sepiaGreen);
            image[row][col].rgbtBlue = capped(sepiaBlue);
        }
    }
}

int capped(int value)
{
    if (value < 0)
    {
        return 0;
    }
    else if (value > 255)
    {
        return 255;
    }
    return value;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            int rightPixel = width - col - 1;

            // swap left and right
            RGBTRIPLE buffer = image[row][col];
            image[row][col] = image[row][rightPixel];
            image[row][rightPixel] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // average
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // 3X3
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if ((newRow >= 0) && (newRow < height) && (newCol >= 0) && (newCol < width))
                    {
                        sumRed += copy[newRow][newCol].rgbtRed;
                        sumGreen += copy[newRow][newCol].rgbtGreen;
                        sumBlue += copy[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            // set value
            image[row][col].rgbtRed = round((float) sumRed / count);
            image[row][col].rgbtGreen = round((float) sumGreen / count);
            image[row][col].rgbtBlue = round((float) sumBlue / count);
        }
    }

    return;
}
