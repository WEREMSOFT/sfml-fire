#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h> // yes, I prefer the C standar library instead of C++

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_SIZE_MULTIPLIER 2

static sf::Color firePalette[255];
static int fireScreenIndexBuffer[2][SCREEN_WIDTH][SCREEN_HEIGHT]; // this is to have colors from the palette, we need two buffers
static int currentBuffer = 0;
static int lastBuffer = 1;

void generateFirePalette(void)
{
    int greenComponent = 255;
    int redComponent = 255;
    for (int i = 0; i < 255; i++)
    {
        if (i > 128)
            redComponent -= 2;

        if (redComponent < 0)
            redComponent = 0;

        if (greenComponent > 0)
            greenComponent -= 2;

        if (greenComponent < 0)
            greenComponent = 0;

        firePalette[255 - i].r = redComponent;
        firePalette[255 - i].g = greenComponent;
    }
}

void drawPalette(sf::Image &canvas)
{
    for (int i = 0; i < 255; i++)
        canvas.setPixel(i, 0, firePalette[i]);
}

void drawRandomBase()
{
    for (int y = 235; y < SCREEN_HEIGHT - 4; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x += 10)
        {
            int colorIndex = 200 + rand() % 50;
            for (int i = x; i < x + 10; i++)
                for (int j = y; j < y + 4; j++)
                    fireScreenIndexBuffer[lastBuffer][i][j] = (unsigned char)colorIndex;
        }
    }
}

void drawFramebufferIntoCanvas(sf::Image &canvas)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            // somebody said indirection ;)
            auto colorIndex = fireScreenIndexBuffer[lastBuffer][x][y];
            canvas.setPixel(x, y, firePalette[colorIndex]);
        }
}

// WTF THE FIRE GOES TO THE RIGHT?!??!?!?
void drawFire(sf::Image &canvas)
{
    drawRandomBase();

    for (int y = 0; y < SCREEN_HEIGHT - 1; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            // I have no idea what I'm doing!!!!
            auto colorIndex = (fireScreenIndexBuffer[lastBuffer][x][y + 1] +
                               fireScreenIndexBuffer[lastBuffer][x][y + 2] +
                               fireScreenIndexBuffer[lastBuffer][x - 1 % SCREEN_WIDTH][y + 1] +
                               fireScreenIndexBuffer[lastBuffer][x + 1 % SCREEN_WIDTH][y + 1]) /
                                  4 -
                              1;
            colorIndex = colorIndex < 0 ? 0 : colorIndex;
            fireScreenIndexBuffer[currentBuffer][x][y] = colorIndex;
        }

    drawFramebufferIntoCanvas(canvas);
    lastBuffer = currentBuffer;
    currentBuffer = currentBuffer == 0 ? 1 : 0;
}