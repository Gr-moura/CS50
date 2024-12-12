#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int isJPEG(BYTE *buffer)
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];

    // Find first JPEG
    do
    {
        if (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) != BLOCK_SIZE)
        {
            printf("Could not read block.\n");
            return 1;
        }
    } while (!isJPEG(buffer));

    int jpgCounter = 0;

    char filename[8] = "000.jpg";
    FILE *img = fopen(filename, "w");
    fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (!isJPEG(buffer))
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            continue;
        }

        if (isJPEG(buffer))
        {
            jpgCounter++;

            fclose(img);
            sprintf(filename, "%03i.jpg", jpgCounter);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img); // Write the buffer to the new file
        }
    }

    fclose(img);
    fclose(inptr);
    return 0;
}
