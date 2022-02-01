/*  Author: Matthew Quinn
*   January 2022
*   Based on CS 4620 Assignment 4 by Abe Davis
*/
#include <stdio.h>
#include <iostream>
#include "environment.h"

int main() {

    // Selecting scene
    printf("Select the scene to render.\n");
    printf("1) Shiny Marbles\n");
    printf("2) Orange vs Blue\n");
    printf("3) Criss-Cross Rainbow\n");
    printf("4) Snowman\n");
    printf("5) Pyramid\n>>> ");
    int sel;
    std::cin >> sel;
    while (!std::cin || sel < 1 || sel > 5) {
        printf("Input must be an integer from 1 to 5.\n>>> ");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> sel;
    }

    // Selecting resolution
    printf("Select the resolution.\n");
    printf("1) 256 x 144\n");
    printf("2) 800 x 450\n");
    printf("3) 1280 x 720\n");
    printf("4) 1920 x 1080\n");
    printf("5) Custom\n>>> ");
    int inp1;
    std::cin >> inp1;
    while(!std::cin || inp1 < 1 || inp1 > 5) {
        printf("Input must be an integer from 1 to 5.\n>>> ");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> inp1;
    }

    // Handling resolution
    int xres;
    int yres;
    switch (inp1) {
    case 1:
        xres = 256;
        yres = 144;
        break;
    case 2:
        xres = 800;
        yres = 450;
        break;
    case 3:
        xres = 1280;
        yres = 720;
        break;
    case 4:
        xres = 1920;
        yres = 1080;
        break;
    case 5:
        printf("Enter the x dimension.\n>>> ");
        std::cin >> xres;
        while (!std::cin || xres < 1 || xres > 10000) {
            printf("X dimension must be an integer from 1 to 10000.\n>>> ");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> xres;
        }
        printf("Enter the y dimension.\n>>> ");
        std::cin >> yres;
        while (!std::cin || yres < 1 || yres > 10000) {
            printf("Y dimension must be an integer from 1 to 10000.\n>>> ");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> yres;
        }
        break;
    }

    // Selecting scale
    float scale;
    printf("Enter the scale.\n");
    printf("For example, a 256x144 resolution with a scale of 2 would be shown in a 512x288 window.\n>>> ");
    std::cin >> scale;
    while (!std::cin || scale < 1 || scale > 100) {
        printf("Scale must be a number from 1 to 100.\n>>> ");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> scale;
    }

    // Get array of pixels based on what is selected
    printf("Computing...\n");
    sf::Uint8* px = getImg(xres, yres, sel);

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
