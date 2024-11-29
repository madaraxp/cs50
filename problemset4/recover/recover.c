#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

bool validate_signature(uint8_t *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    };

    FILE *card = fopen(argv[1], "r");
    FILE *image = NULL;
    uint8_t buffer[BLOCK_SIZE];

    char file_name[8];
    int file_number = 0;

    while (fread(&buffer, BLOCK_SIZE, 1, card))
    {
        if (validate_signature(buffer))
        {
            if (image != NULL)
            {
                fclose(image);
            }
            sprintf(file_name, "%03i.jpg", file_number);
            image = fopen(file_name, "w");
            file_number++;
        }
        if (image != NULL)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, image);
        }
    }
    fclose(card);
    fclose(image);
    return 0;
}

bool validate_signature(uint8_t *buffer)
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0));
}
