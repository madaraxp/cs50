#include "helpers.h"
#include "math.h"

int average_rgb(RGBTRIPLE);
int calculate_square_root(int, int);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int result = average_rgb(image[row][col]);
            image[row][col].rgbtGreen = result;
            image[row][col].rgbtRed = result;
            image[row][col].rgbtBlue = result;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            temp = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            for (int row_shift = -1; row_shift <= 1; row_shift++)
            {
                for (int col_shift = -1; col_shift <= 1; col_shift++)
                {
                    int neighborRow = row + row_shift;
                    int neighborCol = col + col_shift;

                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width)
                    {
                        sumRed += image[neighborRow][neighborCol].rgbtRed;
                        sumGreen += image[neighborRow][neighborCol].rgbtGreen;
                        sumBlue += image[neighborRow][neighborCol].rgbtBlue;
                        count++;
                    }
                }
            }

            temp[row][col].rgbtRed = round((float) sumRed / count);
            temp[row][col].rgbtGreen = round((float) sumGreen / count);
            temp[row][col].rgbtBlue = round((float) sumBlue / count);
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = temp[row][col];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // applying the Sobel operator to the image two "kernels" GX and GY
    int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int gxRed = 0;
            int gyRed = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxBlue = 0;
            int gyBlue = 0;
            for (int row_shift = -1; row_shift <= 1; row_shift++)
            {
                for (int col_shift = -1; col_shift <= 1; col_shift++)
                {
                    int neighborRow = row + row_shift;
                    int neighborCol = col + col_shift;
                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width)
                    {
                        gxRed += image[neighborRow][neighborCol].rgbtRed * GX[row_shift + 1][col_shift + 1];
                        gyRed += image[neighborRow][neighborCol].rgbtRed * GY[row_shift + 1][col_shift + 1];
                        gxGreen += image[neighborRow][neighborCol].rgbtGreen * GX[row_shift + 1][col_shift + 1];
                        gyGreen += image[neighborRow][neighborCol].rgbtGreen * GY[row_shift + 1][col_shift + 1];
                        gxBlue += image[neighborRow][neighborCol].rgbtBlue * GX[row_shift + 1][col_shift + 1];
                        gyBlue += image[neighborRow][neighborCol].rgbtBlue * GY[row_shift + 1][col_shift + 1];
                    };
                };
            };
            temp[row][col].rgbtRed = calculate_square_root(gxRed, gyRed);
            temp[row][col].rgbtGreen = calculate_square_root(gxGreen, gyGreen);
            temp[row][col].rgbtBlue = calculate_square_root(gxBlue, gyBlue);
        };
    };
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = temp[row][col];
        }
    }
    return;
}

int average_rgb(RGBTRIPLE bit)
{
    double average = (bit.rgbtGreen + bit.rgbtRed + bit.rgbtBlue) / 3.0;
    return round(average);
}

int calculate_square_root(int gx, int gy)
{
    double result = sqrt(pow(gx, 2) + pow(gy, 2));
    if (result > 255)
    {
        result = 255;
    }
    return round(result);
}
