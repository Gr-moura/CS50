#include "helpers.h"
#include <math.h>

// Define the size of the kernel
#define KERNEL_SIZE 9

// Define a struct to hold the kernel data
typedef struct
{
    int possiblePixels[KERNEL_SIZE][2];
    int gx[KERNEL_SIZE];
    int gy[KERNEL_SIZE];
} Kernel;

// Initialize the kernel data
const Kernel kernel = {.possiblePixels = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}},
                       .gx = {-1, 0, 1, -2, 0, 2, -1, 0, 1},
                       .gy = {-1, -2, -1, 0, 0, 0, 1, 2, 1}};

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

// Check if a pixel is within image bounds
int isValidPixel(int height, int width, int row, int column)
{
    return row >= 0 && row < height && column >= 0 && column < width;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int validBorderPixels = 0;
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;

            for (int k = 0; k < KERNEL_SIZE; k++)
            {
                int curPixelRow = i + kernel.possiblePixels[k][0];
                int curPixelColumn = j + kernel.possiblePixels[k][1];

                if (isValidPixel(height, width, curPixelRow, curPixelColumn))
                {
                    validBorderPixels++;

                    redSum += image[curPixelRow][curPixelColumn].rgbtRed;
                    greenSum += image[curPixelRow][curPixelColumn].rgbtGreen;
                    blueSum += image[curPixelRow][curPixelColumn].rgbtBlue;
                }
            }

            if (validBorderPixels > 0) // Ensure no division by zero
            {
                temp[i][j].rgbtRed = round((double)redSum / validBorderPixels);
                temp[i][j].rgbtGreen = round((double)greenSum / validBorderPixels);
                temp[i][j].rgbtBlue = round((double)blueSum / validBorderPixels);
            }
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

// Function prototypes
void calculateSobelValues(int height, int width, RGBTRIPLE image[height][width], int i, int j, int *red, int *green,
                          int *blue);

// Clamp a value to the range [0, 255]
int clamp(int value)
{
    return value > 255 ? 255 : (value < 0 ? 0 : value);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Compute edges for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red, green, blue;
            calculateSobelValues(height, width, image, i, j, &red, &green, &blue);

            // Clamp values to ensure they stay within the 0-255 range
            temp[i][j].rgbtRed = clamp(red);
            temp[i][j].rgbtGreen = clamp(green);
            temp[i][j].rgbtBlue = clamp(blue);
        }
    }

    // Copy the computed values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Calculate the Sobel values for a pixel
void calculateSobelValues(int height, int width, RGBTRIPLE image[height][width], int i, int j, int *red, int *green,
                          int *blue)
{
    int redSumGX = 0, greenSumGX = 0, blueSumGX = 0;
    int redSumGY = 0, greenSumGY = 0, blueSumGY = 0;

    // Iterate through the kernel
    for (int k = 0; k < KERNEL_SIZE; k++)
    {
        int curPixelRow = i + kernel.possiblePixels[k][0];
        int curPixelColumn = j + kernel.possiblePixels[k][1];

        if (isValidPixel(height, width, curPixelRow, curPixelColumn))
        {
            redSumGX += image[curPixelRow][curPixelColumn].rgbtRed * kernel.gx[k];
            greenSumGX += image[curPixelRow][curPixelColumn].rgbtGreen * kernel.gx[k];
            blueSumGX += image[curPixelRow][curPixelColumn].rgbtBlue * kernel.gx[k];

            redSumGY += image[curPixelRow][curPixelColumn].rgbtRed * kernel.gy[k];
            greenSumGY += image[curPixelRow][curPixelColumn].rgbtGreen * kernel.gy[k];
            blueSumGY += image[curPixelRow][curPixelColumn].rgbtBlue * kernel.gy[k];
        }
    }

    // Calculate Sobel magnitude
    *red = round(sqrt(redSumGX * redSumGX + redSumGY * redSumGY));
    *green = round(sqrt(greenSumGX * greenSumGX + greenSumGY * greenSumGY));
    *blue = round(sqrt(blueSumGX * blueSumGX + blueSumGY * blueSumGY));
}
