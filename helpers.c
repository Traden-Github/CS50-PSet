#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            int average = round(sum / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid;
    if (width % 2 == 0)
    {
        mid = width / 2 - 1;
    }
    else
    {
        mid = (width - 1) / 2;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= mid; j++)
        {
            if (!(width % 2 == 1 && j == mid))
            {
                RGBTRIPLE hold = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = hold;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image array
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pos_X, pos_Y;
            int sumB, sumG, sumR;
            sumB = sumG = sumR = 0;
            float counter = 0.0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    pos_X = i + x;
                    pos_Y = j + y;
                    if (pos_X < 0 || pos_X > height - 1 || pos_Y < 0 || pos_Y > width - 1)
                    {
                        continue;
                    }
                    sumB += image[pos_X][pos_Y].rgbtBlue;
                    sumG += image[pos_X][pos_Y].rgbtGreen;
                    sumR += image[pos_X][pos_Y].rgbtRed;
                    counter++;
                }
            }
            image_copy[i][j].rgbtBlue = round(sumB / counter);
            image_copy[i][j].rgbtGreen = round(sumG / counter);
            image_copy[i][j].rgbtRed = round(sumR / counter);
        }
    }

    // Paste image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image array
    RGBTRIPLE image_cp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_cp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = -1; i < height - 1; i++)
    {
        for (int j = -1; j < width - 1; j++)
        {
            int pos_X = i + 1, pos_Y = j + 1;
            int xB, xG, xR, yB, yG, yR;
            xB = xG = xR = yB = yG = yR = 0;
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int TrueX = i + x;
                    int TrueY = j + y;
                    if (TrueX < 0 || TrueX > height - 1 || TrueY < 0 || TrueY > width - 1)
                    {
                        continue;
                    }

                    xB += image[TrueX][TrueY].rgbtBlue * Gx[x][y];
                    xG += image[TrueX][TrueY].rgbtGreen * Gx[x][y];
                    xR += image[TrueX][TrueY].rgbtRed * Gx[x][y];
                    yB += image[TrueX][TrueY].rgbtBlue * Gy[x][y];
                    yG += image[TrueX][TrueY].rgbtGreen * Gy[x][y];
                    yR += image[TrueX][TrueY].rgbtRed * Gy[x][y];
                }
            }
            int B, G, R;
            B = round(pow(xB * xB + yB * yB, 0.5));
            G = round(pow(xG * xG + yG * yG, 0.5));
            R = round(pow(xR * xR + yR * yR, 0.5));
            if (B > 255)
            {
                B = 255;
            }
            if (G > 255)
            {
                G = 255;
            }
            if (R > 255)
            {
                R = 255;
            }
            image_cp[pos_X][pos_Y].rgbtBlue = B;
            image_cp[pos_X][pos_Y].rgbtGreen = G;
            image_cp[pos_X][pos_Y].rgbtRed = R;
        }
    }

    // Paste back image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = image_cp[m][n];
        }
    }

    return;
}
