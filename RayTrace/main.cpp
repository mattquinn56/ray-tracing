// Matthew Quinn
#include <stdio.h>
#include "environment.h"

int main() {

    // Resolution of image, and scale. Window size is resolution * scale.
    const int xres = 256;
    const int yres = 144;
    const int scale = 3;

    // Get array of sptires
    int iter = 720;

    //sf::Sprite* sprites = getAllSprites(xres, yres, iter, scale);
    double xeye;
    double yeye;
    sf::Image* allImages = new sf::Image[iter];
    sf::Texture* allTexts = new sf::Texture[iter];
    sf::Sprite* allSprites = new sf::Sprite[iter];
    for (int t = 0; t < iter; ++t) {

        // Find parametric coordinates
        xeye = 5 * cos(0.0174533 * t);
        yeye = 5 * sin(0.0174533 * t);
        printf("%i: (%f, %f)\n", t, xeye, yeye);

        // Grab image, add this to the spritelist
        allImages[t].create(xres, yres, getImg(xres, yres, xeye, yeye));
        allTexts[t].loadFromImage(allImages[t]);
        allSprites[t].setTexture(allTexts[t]);
        allSprites[t].setScale(scale, scale);
    }

    // Window handling
    sf::RenderWindow window(sf::VideoMode(xres * scale, yres * scale), "Ray tracing!");
    window.setFramerateLimit(120);
    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(allSprites[i]);
        window.display();
        i++;
        if (i == iter) {
            i = 0;
        }
    }

    return 0;
}

/*
// Start clock
clock_t t = clock();
// Finish clock
printf("%f", ((float)(clock() - t)) / CLOCKS_PER_SEC);
*/