// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Define BYTE as a byte
typedef uint8_t BYTE;

// Define SAMPLE as a 16-bit (2-byte) sample
typedef int16_t SAMPLE;

void copyHeader(FILE *input, FILE *output);
void adjustVolume(FILE *input, FILE *output, float factor);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    copyHeader(input, output);

    // TODO: Read samples from input file and write updated data to output file
    adjustVolume(input, output, factor);

    // Close files
    fclose(input);
    fclose(output);
}

void copyHeader(FILE *input, FILE *output)
{
    // Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
}

void adjustVolume(FILE *input, FILE *output, float factor)
{
    // Read samples from input file and write updated data to output file
    SAMPLE buffer;
    while (fread(&buffer, sizeof(SAMPLE), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }
}