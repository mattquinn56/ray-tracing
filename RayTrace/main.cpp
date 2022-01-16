// Matthew Quinn
#include <stdio.h>
#include "environment.h"

int main() {

    // Resolution of image, and scale. Window size is resolution * scale.
    const int xres = 2000;
    const int yres = 1125;
    const int scale = 1;


    // Get array of pixels based on what is selected
    sf::Uint8* px = getImg(xres, yres);

    // Turn array of pixels into sprite
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    image.create(xres, yres, px);
    delete[] px;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);

    // Window handling
    sf::RenderWindow window(sf::VideoMode(xres * scale, yres * scale), "Ray tracing!");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

/*
// Start clock
clock_t t = clock();
// Finish clock
printf("%f", ((float)(clock() - t)) / CLOCKS_PER_SEC);
*/