// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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

    // Create a buffer of header size 44 bytes
    uint8_t header[HEADER_SIZE];
    // Read the File with header
    fread(header, HEADER_SIZE, 1, input);
    // write the File with header
    fwrite(header, HEADER_SIZE, 1, output);

    // Create a buffer for a single sample of size 2 bytes
    int16_t buffer;

    // Read single sample from input into buffer while there are samples left to read
    // note: since the fread is statefull it would not read the 44 byte header it already read again
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // Update volume of sample
        buffer *= factor;

        // Write updated sample to new file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
