// Matthew Quinn
#include <iostream>
#include "environment.h"

int main() {
    // Select scene switch. 0 is debug, 1 is run.
    int select = 1;
    
    // Resolution
    const int xres = 1600;
    const int yres = 900;

    // Get array of pixels based on what is selected
    sf::Uint8* px;
    if (select == 0) {
        px = testImg(xres, yres);
    }
    else {
        px = getImg(xres, yres);
    }

    // Turn array of pixels into sprite
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    image.create(xres, yres, px);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    delete[] px;

    // Window handling
    sf::RenderWindow window(sf::VideoMode(xres, yres), "Ray tracing!");
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
//Clock stuff
#include <time.h>
#include <iostream>

//Begin CLK
clock_t t = clock(); ///////////////

//End and print CLK
t = clock() - t;
std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl; ///////////////
*/