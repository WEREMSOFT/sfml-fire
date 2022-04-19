#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>

#include "utils.hpp"
// We don't use parameters for main
int main(void)
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCREEN_SIZE_MULTIPLIER, SCREEN_HEIGHT * SCREEN_SIZE_MULTIPLIER), "FIRE!!!!");
    window.setFramerateLimit(60);
    sf::Image canvasI;
    sf::Texture canvasT;
    sf::Sprite canvasS;

    canvasI.create(SCREEN_WIDTH, SCREEN_HEIGHT, {0, 255, 0});
    canvasT.loadFromImage(canvasI);
    canvasS.setTexture(canvasT);
    canvasS.scale(SCREEN_SIZE_MULTIPLIER, SCREEN_SIZE_MULTIPLIER);

    srand(time(NULL));
    generateFirePalette();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        drawFire(canvasI);
        canvasT.loadFromImage(canvasI);

        window.draw(canvasS);
        window.display();
    }

    return 0;
}