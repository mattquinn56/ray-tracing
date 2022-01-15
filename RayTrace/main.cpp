// Matthew Quinn
#include <iostream>
#include <time.h>
#include "environment.h"

int main() {
    // Select which scene to view. 0 is debug, 1 is run.
    int selectscene = 1;
    // Select whether to use clock. 0 is no, 1 is yes
    int useclk = 1;

    
    // Resolution of image, and scale. Window size is resolution * scale.
    const int xres = 800;
    const int yres = 450;
    const int scale = 2;

    // Start clock
    clock_t t;
    if (useclk) {
        t = clock();
    }
    arma::mat A(4, 5, arma::fill::randu);
    arma::mat B(4, 5, arma::fill::randu);
    std::cout << A * B.t() << std::endl;

    // Get array of pixels based on what is selected
    sf::Uint8* px;
    if (selectscene == 0) {
        px = testImg(xres, yres);
    }
    else {
        px = getImg(xres, yres);
    }

    if (useclk) {
        t = clock() - t;
        std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;
    }

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