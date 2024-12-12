#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int media = round((double)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;
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
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;

            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }

    return;
}

int isValidPixel(int height, int width, int row, int column)
{
    return row >= 0 && row < height && column >= 0 && column < width;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int possiblePixels[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int validBorderPixels = 0;
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;

            for (int k = 0; k < 9; k++)
            {
                int curPixelRow = i + possiblePixels[k][0];
                int curPixelColumn = j + possiblePixels[k][1];

                if (isValidPixel(height, width, curPixelRow, curPixelColumn))
                {
                    validBorderPixels++;

                    redSum += image[curPixelRow][curPixelColumn].rgbtRed;
                    greenSum += image[curPixelRow][curPixelColumn].rgbtGreen;
                    blueSum += image[curPixelRow][curPixelColumn].rgbtBlue;
                }
            }

            temp[i][j].rgbtRed = round((double)redSum / validBorderPixels);
            temp[i][j].rgbtGreen = round((double)greenSum / validBorderPixels);
            temp[i][j].rgbtBlue = round((double)blueSum / validBorderPixels);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
