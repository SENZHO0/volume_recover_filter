#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef int16_t SAMPLE;

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if(argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
            return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");

    if(input == NULL || output == NULL)
    {
        printf("Error opening files.\n");
        return 2;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Change volume for every sample
    SAMPLE sample;
    while(fread(&sample, sizeof(SAMPLE), 1, input))
    {
        // Update volume of sample
        sample *= factor;

        // Write updated sample to new file
        fwrite(&sample, sizeof(SAMPLE), 1, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}
