// librarys
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Pyramid height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Rows
    for (int row = 0; row < height; row++)
    {
        
        for (int col = height - 1; col >= 0; col--)
        {
            if (col > row)
            {
                // Spaces
                printf(" ");
            }
            else
            {
                // Bricks
                printf("#");
            }
        }
        // Gap
        printf("  ");

        for (int col = 0; col <= row; col++)
        {
            // Bricks
            printf("#");
        }

        printf("\n");
    }
}